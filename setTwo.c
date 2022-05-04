#include "rshFunctions.h"

void fileArg(char *cmd, int background){
    //split cmd into array
    int ofile = '>';
    int ifile = '<';
    int pipe = '|';
    char delimit[]=" "; 
    int i = 0, j = 0, status = 0;
    char *string[BUFFER_SIZE];
    char *command;
    command = (char*)malloc(sizeof(char) * BUFFER_SIZE);
    strcpy(command, cmd);
    
    if(cmd != NULL){
        string[i] = strtok(cmd,delimit); 
        while(string[i]!=NULL){
            i++;
            string[i]=strtok(NULL,delimit);
        }
    }
    //make seperate array for just command line arguments (not including ">" or file name)
    int delimitIndex = 0;
    for(int k = 0; k < i; k++){
        if(strcmp(string[k], ">") == 0 || strcmp(string[k], "<") == 0 || strcmp(string[k], "|") == 0){
            delimitIndex = k;
        }
    }
    char *newcmd[BUFFER_SIZE]; 
    int index = 0;
    for(int r = 0; r < delimitIndex; r++){
        newcmd[r] = string[r];
        index++;
    }
    newcmd[index] = NULL;

    if(strchr(command, ofile) != NULL){
        output2file(newcmd, string, background, delimitIndex);
    }
    if(strchr(command, ifile) != NULL){
        inputFromFile(newcmd, string, background, delimitIndex);
    }
    if(strchr(command, pipe) != NULL){
        char *rightCmd[BUFFER_SIZE]; 
        int c = 0;
        for(int r = delimitIndex + 1; r < i; r++){
            rightCmd[c] = string[r];
            c++;
        }
        rightCmd[c] = NULL;
        pipeCmd(newcmd, rightCmd);
    }
}

void output2file(char *newcmd[], char *string[], int background, int delimitIndex){
    FILE *file;
    char *filename = string[delimitIndex + 1];
    // duplicate output 
    int output = dup(1);
    //redirect output to stdout
    file = fopen(filename, "a+");
    dup2(fileno(file), 1);
    processCreation(newcmd, newcmd[0], background);

    //redirect output back to stdout
    fflush(stdout);
    fclose(file);
    dup2(output, 1);
    close(output);
}

void inputFromFile(char *newcmd[], char *string[], int background, int delimitIndex){ 
    FILE *file;
    char *filename = string[delimitIndex + 1];
    //duplicate input 
    int input = dup(0);
    //error check file
    if((file = fopen(filename, "r")) == NULL){
        perror("rsh ");
        exit_rsh(1, getpid());
    }
    //input redirectedfrom a file
    dup2(fileno(file), 0);
    processCreation(newcmd, newcmd[0], background);

    //redirect input back to stdin
    fflush(stdin);
    fclose(file);
    dup2(input, 0);
    close(input);
}

void pipeCmd(char *leftcmd[], char *rightcmd[]){
    int p[2];//create pipe
    if(pipe(p) < 0){
       perror("rsh ");
       exit_rsh(1, getpid()); 
    }
    int status = 0;
    pid_t p1, p2;

    p1 = fork(); //process 1
    if(p1 < 0){ //fork failed
        status = p1;
        perror("rsh ");
        exit_rsh(status, getpid());
    }
    if(p1 == 0){//child process (left hand of pipe)
        dup2(p[1], 1);//duplicate stdout
        close(p[0]);
        close(p[1]);
        status = execvp(leftcmd[0], leftcmd);
        if( status != 0){ //error in command execution
            perror("rsh ");
            exit_rsh(status, getpid());
        }
    }
    p2 = fork(); //process 2
    if(p2 < 0){ //fork failed
        status = p2;
        perror("rsh ");
        exit_rsh(status, getpid());
    }
    if(p2 == 0){//child process (right hand of pipe)
        dup2(p[0], 0);//duplicate stdin
        close(p[0]);
        close(p[1]);
        status = execvp(rightcmd[0], rightcmd);
        if( status != 0){ //error in command execution
            perror("rsh ");
            exit_rsh(status, getpid());
        }
    }
    close(p[0]);
    close(p[1]);
    
    waitpid(p1, NULL, 0);//wait for p1
    waitpid(p2, NULL, 0);//wait for p2
}



