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
Returns a new struct PCB* with those field values:
pages_max = max_pages
PC_page = 0
PC_offset = 0
pageTable[i] = -1 (For 0 to page_max-1)
*/
PCB* makePCB(int max_pages);

/*
Passes a pointer to a PCB and a framenumber.
Returns 0 if that framenumber is in the PCB pageTable
Return -1 if framenumber is not present in the PCB pageTable
*/
int isAPageOf(PCB* pcb, int frameNumber);