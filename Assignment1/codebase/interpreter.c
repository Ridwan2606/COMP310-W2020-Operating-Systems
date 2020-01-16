#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "shellmemory.h"

/*
This functions takes a variable name and value.
It assigns the value argument to the environment variable varName in the shell memory array.
Return ERRORCODE -1 if out of memory else 0
*/
int set(char * varName, char* value ){
    int errorCode = setVariable(varName,value);
    return errorCode;
}

/*
This function takes a variable name as argument.
It will print the value associated with that variable if it exists.
Else it will print an appropriate message.
Return 0 if successful.
*/
int print(char* varName){
    char* value = getValue(varName);

    if (strcmp(value,"NONE")==0) {
        // If no variable with such name exists, display this message
        printf ("Variable does not exist\n");
    } else {
        // else display the variable's value
        printf("%s\n",value);
    }
    return 0;
}

int interpreter(char* words[]){

    //default errorCode if no error occurred AND user did not enter the "quit" command
    int errorCode = 0;

    //At this point, we are checking for each possible commands entered
    if ( strcmp(words[0],"help") ==0 ) {

        // if it's the "help" command, we display the description of every commands
        printf("COMMANDS\t\t\tDESCRIPTIONS\n\n");
        printf("quit\t\t\t\tTerminates the shell\n");
        printf("set VAR STRING\t\t\tAssigns the value STRING to the shell memory variable VAR\n");
        printf("print VAR\t\t\tDisplays the STRING value assigned to the shell memory variable VAR\n");
        printf("run SCRIPT.TXT\t\t\tExecutes the file SCRIPT.txt\n");

    } else if ( strcmp(words[0],"quit") == 0) {

        // if it's the "quit" command
        //errorCode is 1 when user voluntarily wants to quit the program.
        errorCode = 1;
        printf("Bye!\n");

    } else if ( strcmp(words[0],"set") == 0 ) {
        // if it's the "set VAR STRING" command
        // check for the presence or 2 more arguments
        // If one argument missing, return ERRORCODE -2 for invalid number of arguments
        if ( ( strcmp(words[1],"_NONE_") == 0 ) || ( strcmp(words[1],"_NONE_") == 0 ) ) {
            return -2;
        } else {
            // ERRORCODE -1 : Out of Memory might occur
            errorCode = set(words[1],words[2]);
        }
    }  else if ( strcmp(words[0],"print") == 0 ) {
        // if it's the "print VAR" command
        // if there's no second argument, return ERRORCODE -2 for invalid number of arguments
        if ( strcmp(words[1],"_NONE_") == 0 ) return -2;

        // Call the print function
        errorCode = print(words[1]);

    } else if ( strcmp(words[0],"run") == 0 ) {
        /////////////////
        // TO COMPLETE //
        /////////////////
    }
}

int main() {
    char* words[3] = {"quit","X","10"};
    interpreter(words);
}
/*
COMMAND DESCRIPTION
help            Displays all the commands
quit            Exits / terminates the shell with “Bye!”
set VAR STRING  Assigns a value to shell memory
print VAR       Displays the STRING assigned to VAR
run SCRIPT.TXT  Executes the file SCRIPT.TXT
There are no other commands (for now).
If the user inputs an unsupported command the shell displays “Unknown command”.

The command set VAR STRING first checks to see if VAR already exists. If it does exist,
STRING overwrites the previous value assigned to VAR. If VAR does not exist, then a new entry is
added to the shell memory where the variable name is VAR and the contents of the variable is
STRING. For example: set x 10 creates a new variable x and assigns to it the string 10.
Another example: set name Bob creates a new variable called name with string value Bob.
Another example: set x Mary, replaced the value 10 with Mary. 

Implement the shell memory as an array of struct, not as a linked list. Struct MEM { char *var; char *value; };

The command print VAR first checks to see if VAR exists. If it does not exist, then it displays
the error “Variable does not exist”. If VAR does exist, then it displays the STRING. For example:
print x from the above example will display Mary.

The command run SCRIPT.TXT assumes that a text file exists with the provided file name. It
opens that text file and then sends each line one at a time to the interpreter (as seen in class).
The interpreter treats each line of text as a command. Each line affects the shell and the UI. At
the end of the script, the file is closed, and the command line prompt is displayed once more.
While the script executes the command line prompt is not displayed. For example: run
test.txt will begin by opening the file test.txt. If that fails, then an error message is
displayed: “Script not found”. If the file is opened, then each line of the file is interpreted. At the
end, the file is closed, and the command line prompt is displayed. If an error occurs while
executing the script due a command syntax error, then the error is displayed and the script
stops executing.
*/