#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int buffer = 0;

/* Here we increment the buffer and print out TID, PID, and buffer value*/
void *runner(void *args) {
	//do some locking with mutex
	
	/*Write a loop here that increments the buffer until 15
	and prints out which thread is modifying it*/
	printf("TID: %d, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer);
	//unlock
	return ;//some stuff 
}
/* Here we create/close the threads and print out
   how many times each thread worked on the buffer*/
int main() {
	
	//Array of threads to be joined upon
	pthread_t runners[2];
	
	//pthread_create() loop that creates 3 threads
	
	/*Write a loop here that both printout how many times
	each thread worked on the buffer and close each thread
	with pthread_join*/
	printf("TID %d worked on the buffer %d times\n",);
	return 0;

}
