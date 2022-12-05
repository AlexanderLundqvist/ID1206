#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

/**************************************************************************************
ID1206: Lab 3
Written by Max Dern and Alexander Lundqvist
Fall 2022

This program translates logical to physical addresses for a virtual address space 
of size 65536 bytes. The program reads the addresses from a text file and uses a 
TLB (Translation look-aside buffer) and a page table to calculate each logical address 
to its corresponding physical address and output the value of the byte stored at the 
translated physical address.

To use in terminal:
1. gcc AddressTranslator.c -o run
2. ./run ./data/addresses.txt
**************************************************************************************/

/* * * * * * * * * * * * * * * * * INSTRUCTIONS * * * * * * * * * * * * * * * * * * * *
First, write a simple program that extracts the page number and offset 
(an 8-bit page number and 8-bit page offset) from the following integer numbers:
1, 256, 32768, 32769, 128, 65534, 33153
Perhaps the easiest way to do this is by using the operators for bit-masking and
bit-shifting. Once you can correctly establish the page number and offset from
an integer number, you are ready to begin.
Once you can correctly establish the page number and offset from an integer number, 
you are ready to begin. 
Initially, we suggest that you bypass the TLB and use only a page table. 
You can integrate the TLB once your page table is working properly. 
Remember, address translation can work without a TLB; the TLB just makes it faster.
When you are ready to implement the TLB, recall that it has only 16 entries, so you 
will need to use a replacement strategy when you update a full TLB. 
You can use FIFO for updating your TLB.
* * * * * * * * * * * * * * * * * INSTRUCTIONS * * * * * * * * * * * * * * * * * * * */

#define BUFFER_SIZE 1024

/* 
This function extracts the offset from a logical address.
*/
int extractOffset(int logicalAddress) {
    return 0;
}

/*
This function extracts the page number from a logical address.
*/
int extractPageNumber(int logicalAddress) {
    return 0;
}

/*
Controlls the main program flow.
*/
int main(int argc, char *argv[]) {
    // Open the file specified in argv
    FILE *file_handle = fopen(argv[1], "r");
    if(file_handle == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    // Parse the text file and call the extractors
    char buffer[BUFFER_SIZE]; 
    while(fgets(buffer, BUFFER_SIZE - 1, file_handle) != NULL) 
    {
        printf("%s\n", buffer);
    }
    fclose(file_handle);

	return 0;
}
