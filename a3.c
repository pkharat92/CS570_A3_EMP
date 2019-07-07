/*
  Authors: Alex Gonzalez, Pierre Kharat
  User: cssc0816, cs0844
  Class: CS 570, Summer 2019
  Assignment 3, EMP
  a3.c
*/

#include "a3.h"

pthread_t SIGNAL_CATCHER, COUNTDOWN_TIMER, PRINT_INTERVAL, ALARM;

time_t rawtime;
time_t endingtime;
struct tm *timeinfo;
struct tm *endinginfo;

long count;
int print_time;
long alarm_time;

int signum = 1;
bool alarm_sig = false;
bool stop_sig = false;

/*
  This is the main function of the program. The program creates four
  threads. One is the signal handler, and the others are worker threads. 
  Each worker thread will call a different function, countdown_timer(), 
  wall_clock(), and alarm() respectively. If no argument is entered by 
  the user, the program will use the default values: 32, 1, 17.
*/

int main(int argc, char* argv[]){
	// Register signal SIGINT and signal handler
	signal(SIGINT, *signal_handler);
		
	time(&rawtime);
	timeinfo = localtime(&rawtime);
		
    // Use default (32, 1, 17) if no argument
     if(argc == 1){
		count = DEFAULT_COUNT;
		print_time = DEFAULT_PRINT;
		alarm_time = DEFAULT_ALARM;
    } // End if
    else if (argc > 1){
		switch(argc) {
			case 2: 
				count = strtol(argv[1], NULL,10 );
				print_time = DEFAULT_PRINT;
				alarm_time = DEFAULT_ALARM;
				break;
			case 3: 
				count = strtol(argv[1], NULL, 10);
				print_time = strtol(argv[2], NULL, 10);
				alarm_time = DEFAULT_ALARM;
				break;
			case 4:
				count = strtol(argv[1], NULL, 10);
				print_time = strtol(argv[2], NULL, 10);
				alarm_time = strtol(argv[3], NULL, 10);
				break;
			default:
				printf("\nInvalid number of parameters. Goodbye!\n");
				return 0;
		} // End switch
			
		// Error check - first parameter
		if(count == 0) {
			printf("\nInvalid first parameter. Goodbye!\n");
			return 0;
		} // End if
		
		// Error check - second parameter
		if(print_time != 1 && print_time != 60) {	
			printf("\nInvalid second parameter. Goodbye!\n");
			return 0;
		}
			
		// Error check - third parameter
		if(alarm_time == 0 || alarm_time > count) {
			printf("\nInvalid third parameter. Goodbye!\n");
			return 0;
		} // End if
    } // End else if
		
	endingtime = mktime(timeinfo) + count;
	endinginfo = localtime(&endingtime);
		
	pthread_create(&SIGNAL_CATCHER, NULL, (void*) &signal_handler, NULL);
	pthread_create(&COUNTDOWN_TIMER, NULL, &countdown_timer, NULL);
	pthread_create(&PRINT_INTERVAL, NULL, &wall_clock, NULL);
	pthread_create(&ALARM, NULL, &alarm_funct, NULL);
		
	pthread_join(SIGNAL_CATCHER, NULL);
	pthread_join(COUNTDOWN_TIMER, NULL);
	pthread_join(PRINT_INTERVAL, NULL);
	pthread_join(ALARM, NULL);
		
	printf("\nProcess finished. Goodbye!\n");
		
    return 0;
} // End main

/*
 * Handles all signals
 */
void signal_handler() {
	// Sends signal to output alarm message
	while(signum != 2);
	alarm_sig = true;
	
	// Sends signal to close all threads
	while(signum != 3);
	stop_sig = true;
	pthread_exit(NULL);
} // End *signal_handler()

/*
 * Busy waits until the desired time is reached, then sends a 
 * signal to end the program
 */
void *countdown_timer(void *i){
	
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	// Sleep until time to output alarm message
	sleep(alarm_time);
	signum++;	

	// Sleep until countdown is reached
	sleep(count - alarm_time);
	signum++;
	
	pthread_exit(NULL);
} // End *countdown_timer()

/*
 * Prints the time of day in hour, minute, and second format
 */
void *wall_clock(void *i){
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	while(!stop_sig) {
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		printf("%s", asctime(timeinfo));
		sleep(print_time); // will print either every second or minute
	} // End while
	
	pthread_exit(NULL);
} // End *wall_clock()

/*
 * Prints an alarm message to the terminal when the user-specified
 * or default value is reached
 */ 
void *alarm_funct(void *i){
	// Busy waits until alarm signal is sent
	while(!alarm_sig);
	printf("==========Alarm==========\n");
	pthread_exit(NULL);
} // End *alarm_funct()
