/*
This functions passes an int errorCode and display the 
appropriate error message for that errorCode
ERRORCODE -1 : RAN OUT OF SHELL MEMORY
ERRORCODE -2 : INSUFFICIENT NUMBER OF ARGUMENTS
ERRORCODE -3 : FILE DOES NOT EXIST
ERRORCODE -4 : UNKNOWN COMMAND. TYPE "help" FOR A MANUAL OF EVERY AVAILABLE COMMANDS
*/
void displayCode(int errorCode);

int parse(char ui[]);

