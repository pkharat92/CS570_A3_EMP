#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <pthread.h>
#include <signal.h>

#define DEFAULT_COUNT 32
#define DEFAULT_PRINT 1
#define DEFAULT_ALARM 17

void *signal_handler(void *i)
void *countdown_timer(void *i);
void *wall_clock(void *i);
void *alarm(void *i);