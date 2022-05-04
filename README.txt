 * @file myShell.c
 * @author Renee Palmer 
 * @brief Assignment 1: implement a UNIX shell program
 * Email: rpalme05@uoguleph.ca
 * Student number: 1043935

Functions in rshFunctions:
In setOne.c:
    void argu_rsh(char *arg);
        - I used this function to handle the input/commands that were inputed by the user and split 
          the string into commands the shell would understand 
        - this function splits the string and handles any special characters (ex. '>') and sends the 
          string to the correct function
        - I tested this by inputing strings into the command line to see if they were split properly 

    void exit_rsh(int stat, int id);
        - this function exits the shell using the exit() and kill() functions
        - this function takes the status that is passed in and first kills any children and then 
          exits according to the status
        - this function was tested by inputing "exit" in two case scenerios 
            - 1) with no children (ex. at startup)
            - 2) after a processCreation()

    void processCreation(char *argv[], char *cmd, int background);
        - this function creates a process using fork   
        - the funciton takes in the argument array and command string and creates a process as well 
          as executing the command passed in
        - this funciton will also send a process to the background if flag "background" is true (1)
In setTwo.c:
    void fileArg(char *cmd, int background);
        - this function was used to split the arguments from cmd for redirection purposes 
          (input redirection, output redirection, pipping).
        - it uses the same methods as argu_rsh() to split the commands but splits the command according 
          to the special characters in the string (ex. ">", "<", "|")
        - the function will also send the arguments to the appropriate function according to the special character
        - I tested this by inputing strings into the command line to see if they were split properly

    void output2file(char *newcmd[], char *string[], int background, int delimitIndex);
        - this function is used for output redirection to a file
        - this funciton creates a file (string[]) and uses dup() to hold stdout as well as redirect stdout to the file 
        - processCreation is called to execute the commands (cmd)
        - this function was tested using various instructions with the ">" character
    
    void inputFromFile(char *newcmd[], char *string[], int background, int delimitIndex)
        - this function has the same process as output2file but instead of creating a file this function reads from
          a file (string[]) and redirects stdin
        - this function was tested using various instructions with the "<" character

    void pipeCmd(char *leftcmd[], char *rightcmd[])
        - this function mimics a the pipe command
        - this function is a combination of processCreation() and output2file()  
            - this function creates a one level pipe and creates two processes (one for each instruction)
            - per a process, stdout (for left ahnd command) and stdin (for right hand command) are redirected to the pipe
              using dup()
        - this function was tested using various instructions with the pipe (|) command 

Limitations:
Unfortunately, I did not implement the set 3 instructions of the assignment, therefore myShell is very limited in functionality
compared to an actual shell.


