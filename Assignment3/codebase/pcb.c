#include <stdio.h>
#include <stdlib.h>
/*
PCB has 3 fields
PC : Points to the the current line (in RAM) reached for that program
pageTable[10]: Index of that array is the pagenumber and the content of the cell maps to the frame number
PC_page: current page the program is at currently
PC_offset: current offset from beginning of frame program is currently at
pages_max: total number of pages of that program
*/
typedef struct PCB
{
    int PC;
    int pageTable[10];
    int PC_page;
    int PC_offset;
    int pages_max;
}PCB;

/*
Returns a new struct PCB* with those values:
pages_max = argument passed
PC_page = 0
PC_offset = 0
pageTable[i] = -1 (For 0 to page_max-1)
*/
PCB* makePCB(int max_pages){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->pages_max = max_pages;
    for (int i = max_pages; i < max_pages; i++)
    {
        pcb->pageTable[i]=-1;
    }
    pcb->PC_page=0;
    pcb->PC_offset=0;
    return pcb;
}

/*
Passes 2 parameters (start , end)
This method creates a PCB with fields set as this:
PC = start
start = start
end = end
PCB* makePCB(int start, int end){
    PCB* pcb = (PCB*)malloc(sizeof(PCB));
    pcb->PC = start;
    pcb->start = start;
    pcb->end = end;
    return pcb;
}
*/



/*
Passes a pointer to a PCB and a framenumber.
Returns 0 if that framenumber is in the PCB pageTable
Return -1 if framenumber is not present in the PCB pageTable
*/
int isAPageOf(PCB* pcb, int frameNumber){
    for (int i = 0; i < pcb->pages_max; i++)
    {
        if ( pcb->pageTable[i] == frameNumber ) return 0;
    }
    return -1;
}


