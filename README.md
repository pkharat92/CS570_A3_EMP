Author: Alex Gonzalez, Pierre Kharat
User: cssc0816, cssc0844
Class: CS 570, Summer 2019
Assignment 3, EMP
Filename: README.txt

*********************************************************************************************

File manifest:

A3.c >>> Source code for main
A3.h >>> Header file
Makefile >>> Tool for compiling program

After compiling using Makefile:
emp >>> Executable file

*********************************************************************************************

Compile instructions:
Inside ~/a3 folder, type 'make' command and Makefile will compile the code automatically.

*********************************************************************************************

Operating instructions:
Implements an event management program with four threads (One main and four worker threads).
Main thread handles the signals and decides which task is performed first.
One worker thread manages a countdown timer.
Another thread implements a wall clock.
The last thread manages an alarm.

After compiling code with 'make' command an executable file named "emp" will be created.

Type 'emp' followed by desired parameters and the program will run.

The user may run the program with three parameters to be used by the threads:
First parameter: Time in seconds for countdown timer.
Second parameter: Either 1 or 60. 1 prints time evry second; 60 prints out time every minute.
Any other values will result in an error and the program will exit gracefully.
Third parameter: Time in seconds from start of program to print an alarm message.

When no parameters are entered by the user, dafault values will be used (32, 1, 17).

After all threads are done, program will print out a friendly message and exit.

*********************************************************************************************


