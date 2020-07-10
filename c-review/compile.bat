@echo off
set arg1=%1

gcc -c func.c
gcc -c main.c
gcc -o a.exe main.c func.c