#!/bin/bash

gcc -c shell.c interpreter.c shellmemory.c
gcc -o mysh shell.o interpreter.o shellmemory.c
./mysh
rm shell.o interpreter.o shellmemory.o
exit