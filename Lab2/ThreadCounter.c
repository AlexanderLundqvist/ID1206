#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/*
Task description:
"In this assignment, you will write a program that creates three threads.
These threads access a shared integer, called buffer, one at a time. 
The buffer will initially be set to 0. 
Each thread should print its thread ID, process ID, and the buffer's current value in one statement, then increment the buffer by one.
Use a mutex to ensure this whole process is not interrupted. 
Have the threads modify the buffer 15 times. 
When each thread is done, it should return the number of times it modified the buffer to the main thread."

Code written by Max Dern & Alexander Lundqvist
*/

int buffer = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *thread_function() {
	void *access_count = 0;

	/*
	Locks the buffer while the thread performs its critical section, then release the buffer
	inbetween so other threads can access it.
	*/	
	while(buffer < 15 || pthread_mutex_lock(&mutex)) {
		printf("TID: %lu, PID: %d, Buffer: %d\n", pthread_self(), getpid(), buffer++);
		access_count++;
		pthread_mutex_unlock(&mutex);
		sleep(0.0001); // Without this the access distribution gets very skewed
	}	
	pthread_mutex_unlock(&mutex);
	return (void*)access_count;

}

/* 
We recognize that most of this implementation could've been done with loops but we chose a 
more blunt approach to better understand what is happening. 
*/
int main() {
	/* Declare the thread variables. */
	pthread_t thread_1, thread_2, thread_3;

	/*
	Create the actual threads by calling phtread_create.
	Passing in the adress to thread variables and the thread function.
	*/
	pthread_create(&thread_1, NULL, thread_function, NULL);
	pthread_create(&thread_2, NULL, thread_function, NULL);
	pthread_create(&thread_3, NULL, thread_function, NULL);	

	/* 
	Join the threads to block main until the threads have finished their execution.
	*/
	int threadresult_1, threadresult_2, threadresult_3;

	pthread_join(thread_1, (void**)&threadresult_1);
	pthread_join(thread_2, (void**)&threadresult_2);
	pthread_join(thread_3, (void**)&threadresult_3);

	/* Print amount of buffer accesses for each thread */
	printf("TID %lu worked on the buffer %d times\n", thread_1, threadresult_1);
	printf("TID %lu worked on the buffer %d times\n", thread_2, threadresult_2);
	printf("TID %lu worked on the buffer %d times\n", thread_3, threadresult_3);

	/* Print total amount of accesses */
	printf("Total buffer accesses: %d\n", buffer);

	return 0;

}
