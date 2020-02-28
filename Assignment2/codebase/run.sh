#!/bin/bash

gcc -c shell.c interpreter.c shellmemory.c kernel.c
gcc -o mykernel shell.o interpreter.o shellmemory.c kernel.o
./mykernel
rm shell.o interpreter.o shellmemory.o kernel.o
exit