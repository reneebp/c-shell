/**
 * @file myShell.c
 * @author Renee Palmer 
 * @brief Assignment 1: implement a UNIX shell program
 * Email: rpalme05@uoguleph.ca
 * Student number: 1043935
 */
#include "rshFunctions.h"

void readLine(){
    char *user;
    int status;
    user = (char*)malloc(sizeof(char) * BUFFER_SIZE);

    do{
        printf(">");
        fgets(user, BUFFER_SIZE, stdin);
        if(*(user + 0) != '\n'){
            argu_rsh(user);
        }
        if(*(user + 0) == '\n'){
            readLine();
        }
    }while(1);

    free(user);
}

int main(int argc, char **argv){
    //run command line
    readLine();

    return 0;
}
