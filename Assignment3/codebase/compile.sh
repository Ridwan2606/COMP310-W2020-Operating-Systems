#!/bin/bash

#Compile the o files
echo "Compiling into .o files"
gcc -c kernel.c cpu.c ram.c shell.c shellmemory.c interpreter.c pcb.c
#Compile the executable mykernel
echo "Compiling into mykernel"
gcc -o mykernel shellmemory.o kernel.o cpu.o ram.o shell.o interpreter.o pcb.o
#remove all .o files
#rm *.o
exit