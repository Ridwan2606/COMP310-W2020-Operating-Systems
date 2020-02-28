#include<stdio.h>
#include"shell.h"
#include"pcb.h"

typedef struct ReadyQueueNode {
    PCB PCB;
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
void addToReady(PCB * pcb) {
    ReadyQueueNode* newNode = (ReadyQueueNode *)malloc(sizeof(ReadyQueueNode));
    newNode->PCB = *pcb;
    newNode->next = NULL;
    if (head == NULL){
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
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
PCB pop(){
    PCB topNode = head->PCB;
    if (head == tail){
        head = NULL;
        tail = NULL;
    } else {
        head = head->next;
    }
    sizeOfQueue--;
    return topNode;
}


