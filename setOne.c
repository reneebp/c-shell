#include "rshFunctions.h"

void argu_rsh(char *cmd){
    int i, status = 0;
    int counter = 0;
    int bg = '&';
    int background = 0;
    int ofile = '>';
    int ifile = '<';
    int pipe = '|';
    char *argv[BUFFER_SIZE];

    cmd[strlen(cmd) - 1] = '\0';

    if(strcmp(cmd, "exit") == 0){ //exit -no children
        printf("rsh terminating…\n");
        printf("[Process completed]\n");
        exit(0);
    }
    if(strchr(cmd, bg) != NULL){
        background = 1;
    }

    if(strchr(cmd, ofile) != NULL || strchr(cmd, ifile) != NULL || strchr(cmd, pipe) != NULL){
        fileArg(cmd, background);
        return;
    }

    //if string has a contains arguments ("-" and/or whitespce is present) split the string
    argv[0] = strtok(cmd," ");
    for(int i = 1; i < strlen(cmd); i++){
        argv[i] = strtok(NULL," ");
        counter = i++;
    }
    argv[counter] = NULL;
    processCreation(argv, cmd, background);
}

void processCreation(char *argv[], char *cmd, int background){
    int status = 0, counter = 0;
    pid_t p1, wait_p1;

    p1 = fork(); //new process
    if(p1 >= 0){ //fork success
        if(p1 == 0){//child process
            status = execvp(cmd, argv);
            if( status != 0){ //error in command execution
                perror("rsh ");
                exit_rsh(status, getpid());
            }
        }
        else{ //parent process
            if(background == 1){ //in background, stop process
                counter++;
                printf("[%d] %d\n",counter, p1);
                kill(p1, SIGSTOP);
            }
            else{ //wait for child
                do{
                    wait_p1 = waitpid(p1, &status, WUNTRACED);
                }while(!WIFEXITED(status) && !WIFSIGNALED(status));
            }
        }
    }
    else{ //fork failed
        status = p1;
        perror("rsh ");
        exit_rsh(status, getpid());
    }
}

void exit_rsh(int stat, int id){
    //exit rsh and kill children
    kill(id, SIGKILL);
    printf("rsh terminating…\n");
    printf("[Process completed]\n");
    exit(stat);
}
