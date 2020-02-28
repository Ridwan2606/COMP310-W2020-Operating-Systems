#include<stdio.h>
#include"pcb.h"

struct PCB_Node {
    PCB PCB;
    PCB* next;
} ReadyQueue;