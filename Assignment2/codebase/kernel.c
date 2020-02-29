#include<stdio.h>
#include"shell.h"
#include"pcb.h"
#include"ram.h"
#include"cpu.h"
#include"interpreter.h"

/*
This is a node in the Ready Queue implemented as 
a linked list.
A node holds a PCB pointer and a pointer to the next node.
PCB: PCB
next: next node
*/
typedef struct ReadyQueueNode {
    PCB*  PCB;
    ReadyQueueNode* next;
} ReadyQueueNode;

ReadyQueueNode* head = NULL;
ReadyQueueNode* tail = NULL;
int sizeOfQueue = 0;

int main(int argc, char const *argv[])
{
    //Calls shellUI
    //instantiate all kernel data structure.
    shellUI();
}
/*
Adds a pcb to the tail of the linked list
*/
void addToReady(struct PCB* pcb) {
    ReadyQueueNode* newNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNode->PCB = pcb;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    sizeOfQueue++;
}

/*
Returns the size of the queue
*/
int size(){
    return sizeOfQueue;
}

/*
Pops the pcb at the head of the linked list.
pop will cause an error if linkedlist is empty.
Always check size of queue using size()
*/
struct PCB* pop(){
    PCB* topNode = head->PCB;
    if (head == tail){
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
    }
    sizeOfQueue--;
    return topNode;
}

/*
Passes a filename
Opens the file, copies the content in the RAM.
Creates a PCB for that program.
Adds the PCB on the ready queue.
Return an errorCode:
ERRORCODE 0 : NO ERROR
ERRORCODE -3 : SCRIPT NOT FOUND
ERRORCODE -5 : NOT ENOUGH RAM (EXEC)
*/
int myinit(char* filename){
    // Open the filename to get FILE *
    // call addToRam on that File *
    // If error (check via start/end variable), return that error
    // Else create pcb using MakePCB
    // Then add it to the ReadyQueue
    FILE * fp = fopen(filename,"r");
    if (fp == NULL) return -3;
    int start;
    int end;
    addToRAM(fp,&start,&end);
    if (start == -1) return -5;
    PCB* pcb = makePCB(start,end);
    addToReady(pcb);
    return 0;
}

int scheduler(){
    // set CPU quanta to default, IP to -1, IR = NULL
    CPU.quanta = DEFAULT_QUANTA;
    CPU.IP = -1;
    while (size() != 0){
        //pop head of queue
        PCB* pcb = pop();
        //copy PC of PCB to IP of CPU
        CPU.IP = pcb->PC;

        int isOver = FALSE;
        int remaining = (pcb->end) - (pcb->PC) + 1;
        int quanta = DEFAULT_QUANTA;

        if (DEFAULT_QUANTA >= remaining) {
            isOver = TRUE;
            quanta = remaining;
        }

        int errorCode = run(quanta);

        if ( errorCode<0 || isOver ){
            removeFromRam(pcb->start,pcb->end);
            free(pcb);
        } else {
            pcb->PC += DEFAULT_QUANTA;
            addToReady(pcb);
        }
    }
    // reset RAM
    resetRAM();
    return 0;
}
/*
a. It checks to see if the CPU is available.  
This means that the quanta is finished or nothing is currently assigned to the CPU 
b. It copies the PC from the PCB into the IP of the CPU 
c. It calls the run(quanta) function within cpu.c to run the script 
by copying quanta lines of code from ram[] using IP into the IR, 
which then calls: interpreter(IR) 
d. This executes quanta instructions from the script or until the script file is at end. 
e. If the program is not at the end, then the PCB PC pointer is updated
 with the IP value and the PCB is placed at the tail of the ready queue. 
 f. If the program is at the end, then the PCB terminates (as described previously / above) 

When the Ready queue is empty, this means that all the programs have terminated.  
At this point the exec() function ends, and the user sees the shell command line prompt. 
*/


