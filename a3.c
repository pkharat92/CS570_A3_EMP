/*
Authors: Alex Gonzalez, Pierre Kharat
User: cssc0816, cs0844
Class: CS 570, Summer 2019
Assignment 3, EMP
a3.c
*/

#include "a3.h"

using namespace std;

/*
  This is the main function of the program. The program is in charge of
  creating three threads. Each thread will call a different function, countdown_Timer, wall_Clock()
  and alarm() respectively. If no argument entered by the user the
  program will use (75 1 45).
*/

int main(int argc, char* argv[]){

        // Use default (32 1 17) if no argument
        if(argc == 1){

        }

        else if (argc > 1){

        }

        return 0;
} // End main

/*
  This function will busy wait until the desired time is reached.
*/

void *countdown_Timer(void *i){

} // End *countdown_Timer()

/*
void *wall_Clock(void *i){
} // End *wall_Clock()
void *alarm(void *i){
} // End *alarm()