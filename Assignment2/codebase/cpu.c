#include<string.h>
#include"ram.h"
#include"interpreter.h"

struct CPU { 
    int IP; 
    char IR[1000]; 
    int quanta; 
} CPU;


int run(int quanta){
    CPU.quanta = quanta;
    for (int i = 0; i < CPU.quanta; i++)
    {
        strcpy(CPU.IR,ram[CPU.IP]);
        int errorCode = interpreter(CPU.IR);
        // Do error checking and if error, return error
        CPU.IP ++;
    }
}
