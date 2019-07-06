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
int print;
long alarm_time;

bool sig = true;
bool alarm_sig = true;

/*
  This is the main function of the program. The program creates four
  threads. One is the signal handler, and the others are worker threads. 
  Each worker thread will call a different function, countdown_timer(), 
  wall_clock(), and alarm() respectively. If no argument is entered by 
  the user, the program will use the default values: 32, 1, 17.
*/

int main(int argc, char* argv[]){
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		
        // Use default (32, 1, 17) if no argument
        if(argc == 1){
			count = DEFAULT_COUNT;
			print = DEFAULT_PRINT;
			alarm_time = DEFAULT_ALARM;
        } // End if
        else if (argc > 1){
			switch(argc) {
				case 2: 
					count = atoi(argv[1]);
					print = DEFAULT_PRINT;
					alarm_time = DEFAULT_ALARM;
					break;
				case 3: 
					count = atoi(argv[1]);
					print = atoi(argv[2]);
					alarm_time = DEFAULT_ALARM;
					break;
				case 4:
					count = atoi(argv[1]);
					print = atoi(argv[2]);
					alarm_time = atoi(argv[3]);
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
			if(print != 1 || print != 60) {
				printf("\nInvalid second parameter. Goodbye!\n");
				return 0;
			} // End if
			
			// Error check - third parameter
			if(alarm_time == 0 || alarm_time > count) {
				printf("\nInvalid third parameter. Goodbye!\n");
				return 0;
			} // End if
        } // End else if
		
		endingtime = mktime(timeinfo) + count;
		endinginfo = localtime(&endingtime);
		
		pthread_create(&SIGNAL_CATCHER, NULL, &signal_handler, NULL);
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
void *signal_handler(void *i) {
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
	alarm_sig = false;
	
	// Sleep until countdown is reached
	sleep(count - alarm_time);
	sig = false;
	
	pthread_exit(NULL);
} // End *countdown_timer()

/*
 * Prints the time of day in hour, minute, and second format
 */
void *wall_clock(void *i){
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	
	while(sig) {
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		printf("%s", asctime(timeinfo));
		sleep(print); // will print either every second or minute
	} // End while
	
	pthread_exit(NULL);
} // End *wall_clock()

/*
 * Prints an alarm message to the terminal when the user-specified
 * or default value is reached
 */ 
void *alarm_funct(void *i){
	// Busy waits until alarm signal is sent
	while(alarm_sig);
	printf("\n====Alarm====\n");
} // End *alarm_funct()
