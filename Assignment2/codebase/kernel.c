#include"shell.h"


int main(int argc, char const *argv[])
{
    //Calls shellUI
    //instantiate all kernel data structure.
    shellUI();
}
/*
1. It calls void addToRAM(FILE *p, int *start, int *end) from ram.c 
to add the source code to the next available cells in ram[]. 
2. It calls PCB* makePCB(int start, int end) from pcb.c to create a PCB instance 
using malloc. 
3. It calls void addToReady(PCB *) from kernel.c to add the PCB to the 
tail of the Ready Queue 
*/
