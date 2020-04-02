#!/bin/bash

#Compile the o files
gcc -c kernel.c cpu.c ram.c shell.c shellmemory.c interpreter.c pcb.c 
#Compile the executable mykernel
gcc -o mykernel kernel.o cpu.o ram.o shell.o shellmemory.o interpreter.o pcb.o
#remove all .o files
rm *.o
exit