#!/bin/bash

gcc -c shell.c interpreter.c shellmemory.c
gcc -o shell shell.o interpreter.o shellmemory.c
./shell
rm shell shell.o interpreter.o shellmemory.o
exit