#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"interpreter.h"

/*
This functions passes an int errorCode and command string and display the 
appropriate error message for that errorCode
ERRORCODE -1 : RAN OUT OF SHELL MEMORY
ERRORCODE -2 : INSUFFICIENT NUMBER OF ARGUMENTS
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -4 : UNKNOWN COMMAND.
*/
void displayCode(int errorCode, char * command){
    switch (errorCode)
    {
    case -1:
        printf("ERRORCODE -1 : RAN OUT OF SHELL MEMORY\n");
        break;
    case -2:
        printf("ERRORCODE -2 : '%s' INSUFFICIENT NUMBER OF ARGUMENTS. TRY 'help'\n", command);
        break;
    case -3:
        printf("ERRORCODE -3 : SCRIPT NOT FOUND\n");
        break;
    case -4:
        printf("ERRORCODE -4 : '%s' IS AN UNKNOWN COMMAND. TRY 'help'\n", command);
        break;
    }

    return;
}

int parse(char ui[]){
    //printf("In Parser: '%s'",ui);
    char tmp[200]; int a,b;
    char *words[10]; int w=0; // wordsIdx
    for (int i=0; i<10; i++){
        words[i] = "_NONE_";
    }
    for(a=0; ui[a]==' ' && a<1000; a++); // skip white spaces
    while(ui[a] != '\0' && ui[a]!='\n' && a<1000) {
        for(b=0; ui[a]!='\0' && ui[a]!='\n' && ui[a]!='\r' && ui[a]!=' ' && a<1000; a++, b++)
            tmp[b] = ui[a]; // extract a word
        tmp[b] = '\0';
        words[w] = strdup(tmp);
        if (ui[a]=='\0' || ui[a]=='\n' || ui[a]=='\r' ) break;
        for(;ui[a]==' ' && a<1000; a++); // skip white spaces
        w++;
    }
    return (interpreter(words));
    //free(words);
}

/*
This is the main loop where 
users gets to use the shell.
*/
int main(int argc, char const *argv[])
{
    printf(
    "\n----------------------------------\nWelcome to the Ridwan shell!\nVersion 1.0 Created January 2020\n----------------------------------\n");
    char prompt[15] = {'$','\0'};
    char userinput[1000];
    int errorCode;

    while (1)
    {
        // prints prompt
        printf("%s",prompt);
        //gets user input
        fgets(userinput,999,stdin);
        // parses and interprets the command
        errorCode = parse(userinput);
        //If the user entered the "quit" command
        if ( errorCode == 1 ) {
            printf("----------------------------------\nExiting Ridwan Shell. Farewell...\n----------------------------------\n");
            break;
        //else if an error occurred, display what that error is
        } else if ( errorCode != 0 ) {
            //removing the extra carriage return
            userinput[strlen(userinput)-1]='\0';
            displayCode(errorCode, userinput);
        }
    }
    return 0;
}

