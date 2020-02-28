#include<stdio.h>

int nextFree = 0;
char *ram[1000]; 

/*
This function will add the content of a file to the local ram array variable
p : file pointer
start : pointer to variable which will store the index of first line of file in ram
end : pointer to variable which will store the index of last line of file in ram
*/
void addToRAM (FILE *p, int *start, int *end){
    *start = nextFree;
    int i = *start;
    char buffer[1000];
    while (!feof(p)){
        fgets(buffer,999,p);
        ram[i]= strdup(buffer);
        i++;
    }
    nextFree=i;
    *end=i-1;

    // throws an error if not enough memory??? but void
}

/*
This function will delete the content in ram between the 2 indices parameters (inclusive)
start : pointer to variable which will store the index of first line of file in ram
end : pointer to variable which will store the index of last line of file in ram
*/
void removeFromRam (int start, int end){
    for (int i = start; i <= end; i++)
    {
        ram[i] = NULL;
    }
}

/*
Reset the pointer to the free cell back to index 0
*/
void reset(){
    nextFree = 0;
}


