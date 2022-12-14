#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <time.h>
#include <math.h>

/**************************************************************************************
ID1206: Lab 4
Written by Max Dern and Alexander Lundqvist
Fall 2022

This program performs benchmark on different disk scheduling algorithms by simulating 
a disk with 5000 cylinders and reports the total amount of head movement required by each 
algorithm. The program generates 1000 random cylinder requests and applies it for each 
algorithm with the disk head being a command line argument. 
The algorithms that are implemented are FCFS, SSTF, SCAN, C-SCAN, Look and C-Look.

To use in terminal:
1. gcc DiskScheduling.c -o run
2. ./run 1337 (Or some other number between 0 and 4999)
**************************************************************************************/

#define DISK_SIZE 5000
#define AMOUNT_OF_REQUESTS 1000

/* Function prototypes */
int FCFS(int *requests, int initial_position);
int SSTF(int *requests, int initial_position);
int SCAN(int *requests, int initial_position);
int CSCAN(int *requests, int initial_position);
int Look(int *requests, int initial_position);
int CLook(int *requests, int initial_position);
int parseCmdArg(char *arg);

/* Simulated disk */
int disk[DISK_SIZE];

/* Array that holds the specified amount of requests*/
int requests[AMOUNT_OF_REQUESTS];

/*
Controlls the main program flow. Assumes that the argument is a valid integer number.
*/
int main(int argc, char *argv[]) {
    int takenIntegers[DISK_SIZE]; // Used for control when generating random numbers

    // Attempt with parsing the argument to set the initial head position.
    int initial_position;
    if (argc > 2) {
        printf("Error: Too many arguments!\n");
        exit(EXIT_FAILURE);              
    }
    else if (argc == 2) {
        initial_position = parseCmdArg(argv[1]);
        printf("Initial disk head position is set to: %d\n", initial_position);
    }
    else {
        printf("Error: Missing argument!\n");
        exit(EXIT_FAILURE);
    }

    // Populate the disk with the actual index values. This makes for easier testing.
    // Also use it to set the control array.
    for (int i = 0; i < DISK_SIZE; i++) {
        disk[i] = i;
        takenIntegers[i] = 0;
    }

    // Populate the requests array with unique random requests ranging from 0-4999.
    srand(time(NULL));
    int counter = 0;
    while (counter < AMOUNT_OF_REQUESTS) {
        int random_number = rand() % DISK_SIZE; // Random number between 0 and 4999
        if (takenIntegers[random_number] == 0) {
            requests[counter] = random_number;
            takenIntegers[random_number] = 1; // Mark the number as taken
            counter++;
        }
        // Else the number was already taken
    }

    // Call the algorithms then display the result.
    printf("\nUsing FCFS\n");
    printf("Total head movement: %d\n", FCFS(requests, initial_position));

    printf("\nUsing SSTF\n");
    printf("Total head movement: %d\n", SSTF(requests, initial_position));

    printf("\nUsing SCAN\n");
    printf("Total head movement: %d\n", SCAN(requests, initial_position));

    printf("\nUsing C-SCAN\n");
    printf("Total head movement: %d\n", CSCAN(requests, initial_position));

    printf("\nUsing Look\n");
    printf("Total head movement: %d\n", Look(requests, initial_position));

    printf("\nUsing C-Look\n");
    printf("Total head movement: %d\n\n", CLook(requests, initial_position));

    return 0;
}

/*
TBD
*/
int FCFS() {
    return 0;
}

/*
TBD
*/
int SSTF() {
    return 0;
}

/*
TBD
*/
int SCAN() {
    return 0;
}

/*
TBD
*/
int CSCAN() {
    return 0;
}

/*
TBD
*/
int Look() {
    return 0;
}

/*
TBD
*/
int CLook() {
    return 0;
}

/*
Checks if the string is a valid positive integer in the range of 0-4999. 
*/
int parseCmdArg(char *arg) {
    int errno_backup = errno;
    errno = 0; 
    char *endptr;
    long parsed_argument = strtol(arg, &endptr, 10);

    // Check for general parsing errors
    if (errno != 0) {
        printf("Error: Could not parse the argument!\n");
        exit(EXIT_FAILURE);
    }

    // Check if it is even a number
    if (*endptr != 0) {
        printf("Error: Malformed argument!\n");
        exit(EXIT_FAILURE);
    }

    // Check if argument is in range
    if (parsed_argument < 0 || parsed_argument > 4999) {
        printf("Error: Argument out of range [0, 4999]!\n");
        exit(EXIT_FAILURE); 
    }

    errno = errno_backup;
    return (int) parsed_argument;
}
