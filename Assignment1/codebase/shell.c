#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int parse(char ui[]){
}

/*
This functions passes an int errorCode and display the 
appropriate error message for that errorCode
ERRORCODE -1 : RAN OUT OF SHELL MEMORY
ERRORCODE -2 : INSUFFICIENT NUMBER OF ARGUMENTS
ERRORCODE -3 : FILE DOES NOT EXIST
ERRORCODE -4 : UNKNOWN COMMAND. TYPE "help" FOR A MANUAL OF EVERY AVAILABLE COMMANDS
*/
void displayCode(int errorCode){
    switch (errorCode)
    {
    case -1:
        printf("ERRORCODE -1 : RAN OUT OF SHELL MEMORY\n");
        break;
    case -2:
        printf("ERRORCODE -2 : INSUFFICIENT NUMBER OF ARGUMENTS\n");
        break;
    case -3:
        printf("ERRORCODE -3 : FILE DOES NOT EXIST\n");
        break;
    case -4:
        printf("ERRORCODE -4 : UNKNOWN COMMAND. TYPE 'help' FOR A MANUAL OF EVERY AVAILABLE COMMANDS\n");
        break;
    }

    return;
}