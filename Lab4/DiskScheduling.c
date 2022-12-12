#include <stdio.h>
#include <stdlib.h>

/**************************************************************************************
ID1206: Lab 4
Written by Max Dern and Alexander Lundqvist
Fall 2022

This program performs benchmark on different disk scheduling algorithms by simulating 
a disk with 5000 cylinders and reports the total amount of head movement required by each 
algorithm. The program generates 1000 random cylinder requests and applies it for each 
algorithm with the disk head being a command line argument (If omitted, a default value is used). 
The algorithms that are implemented are FCFS, SSTF, SCAN, C-SCAN, Look and C-Look.

To use in terminal:
1. gcc DiskScheduling.c -o run
2. ./run 1337 (Or some other number between 0 and 4999)
**************************************************************************************/

#define DISK_SIZE 5000
#define REQUESTS_SIZE 1000
#define DEFAULT 2500

/*
TBD
*/
int FCFS() {

}

/*
TBD
*/
int SSTF() {

}

/*
TBD
*/
int SCAN() {

}

/*
TBD
*/
int CSCAN() {

}

/*
TBD
*/
int Look() {

}

/*
TBD
*/
int CLook() {

}



/*
Controlls the main program flow. Assumes that the argument is a valid integer number.
*/
int main(int argc, char *argv[]) {
    int initial_position;
    if (argc == 1) {
        initial_position = DEFAULT;
        printf("No argument supplied, disk head position is set to default: %d\n", DEFAULT);
    }
    else {
        initial_position = atoi(argv[1]);
        printf("Initial disk head position is set to: %d\n", initial_position);
    }
    
    // Generate random array

    // Call functions with copies of array?

    printf("I am a work in progress!");
    return 0;
}
