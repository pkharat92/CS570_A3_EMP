/*
  Authors: Alex Gonzalez, Pierre Kharat
  User: cssc0816, cs0844
  Class: CS 570, Summer 2019
  Assignment 3, EMP
  a3.h
*/

#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#define DEFAULT_COUNT 32
#define DEFAULT_PRINT 1
#define DEFAULT_ALARM 17

void *signal_handler(void *i)
void *countdown_timer(void *i);
void *wall_clock(void *i);
void *alarm_funct(void *i);
