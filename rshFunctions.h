#include <stdio.h>       
#include <stdlib.h>      
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <unistd.h>      
#include <sys/types.h>   
#include <sys/wait.h>
#include <errno.h>  
#include <fcntl.h>    

#define BUFFER_SIZE 256

void argu_rsh(char *arg);
void exit_rsh(int stat, int id);
void processCreation(char *argv[], char *cmd, int background);
void fileArg(char *cmd, int background);
void output2file(char *newcmd[], char *string[], int background, int delimitIndex);
void inputFromFile(char *newcmd[], char *string[], int background, int delimitIndex);
void pipeCmd(char *leftcmd[], char *rightcmd[]);

