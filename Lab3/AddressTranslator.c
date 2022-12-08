#include <stdio.h>
#include <stdlib.h>

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
2. ./run ./data/addresses.txt (Or whatever other location the file is stored at)
**************************************************************************************/

#define BUFFER_SIZE 1024
#define FILE_SIZE 1000
#define PAGES 256
#define PAGE_SIZE 256
#define FRAMES 256
#define FRAME_SIZE 256
#define TLB_SIZE 16



/*
The struct makes it easier to hold multiple data for each address.
*/
struct address_components {
    int logical_address;
    int page_number;
    int offset;
    int physical_address;
};
struct address_components addresses[FILE_SIZE];

/*

*/
int page_table[PAGES];

/* 
Simulated main memory (RAM). pm_head is a pointer for the main memory. 
*/
int physical_memory[FRAMES][FRAME_SIZE];
int pm_head;

/*
Holds up to 16 {page number, frame number} touples. tlb_head is a pointer for the TLB.
*/
int tlb[TLB_SIZE][2];
int tlb_head;

/*
The percentage of address references that resulted in page faults and the 
percentage of address references that were resolved in the TLB.
*/
int page_fault_count;
int tlb_hit_count;

/* 
This function extracts the offset from a logical address.
*/
int extractOffset(int logical_address) {
    int offset = (logical_address) & 0xFF; 
    return offset;
}

/*
This function extracts the page number from a logical address.
*/
int extractPageNumber(int logical_address) {
    int page_number = (logical_address >> 8) & 0xFF;
    return page_number;
}

/*
Reads required bytes from the BACKING_STORE.bin file and returns the appropriate frame. This
emulates the disk storage.
*/
int readBin(int page_number) {
    FILE *bin_handle = fopen("./data/BACKING_STORE.bin", "rb");
    if(bin_handle == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    unsigned char buffer[FRAME_SIZE];
    fseek(bin_handle, (page_number * 256), SEEK_SET); // Set the pointer to the location of the page
    // Now, read the bytes from the disk and copy it to main memory
    fread(buffer, 1, 256, bin_handle);
    for(int i = 0; i < 256; i++){
        physical_memory[pm_head][i] = buffer[i];
    }
    page_table[page_number] = pm_head;
    pm_head++;
    fclose(bin_handle);
    return page_table[page_number];
}
/*
int updateTLB() {
    return 0;
}
*/
int consultTLB() {
    //updateTLB();
    return 0;
}



/*
Attempts to find the physical address with the TLB. If the address is not found then we consult
the page table. In the case of page fault then we would read from the disk storage. 
*/
int findPhysicalAddress(int page_number) {
    int frame;

    // Check if in TLB WIP
    if(consultTLB() != 0) {
        //tlb_hit_count++;
        //frame = tlb[]
    }
    else {
        // Check the page table
        if (page_table[page_number] != -1) {
            frame = page_table[page_number];
        } 
        else {
            page_fault_count++;
            // Load in frame from bin
            frame = readBin(page_number);
            page_table[page_number] = frame;
        }
    }
    

    // Concatenate frame number and offset to create the physical address
    int physical_address = (frame << 8) & 0xFF00| addresses[page_number].offset & 0x00FF;
    
    // int temp = (frame << 8);
    //printf("Frame: %d\n", temp);
    printf("Physical address: %d\n", physical_address);

    return physical_address;
}

/*
Controlls the main program flow.
*/
int main(int argc, char *argv[]) {
    // Open the file specified in argv
    FILE *file_handle = fopen(argv[1], "r");
    if(file_handle == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    } 
    pm_head = 0;
    page_fault_count = 0;
    tlb_hit_count = 0;
    tlb_head = 0;

    // Initialize the page table with "false" values 
    for (int i = 0; i < 256; i++) {
        page_table[i] = -1;
    }
        
    // Parse the text file and call the extractors to fill our struct array
    char buffer[BUFFER_SIZE];
    int i = 0;
    int number; 
    while(fgets(buffer, BUFFER_SIZE - 1, file_handle) != NULL) {
        number = atoi(buffer);
        addresses[i].logical_address = number;
        addresses[i].page_number = extractPageNumber(number);
        addresses[i].offset = extractOffset(number);
        i++;
    }
    fclose(file_handle);

    // Start the physical address conversion process
    for(int j = 0; j < FILE_SIZE; j++) {
        addresses[j].physical_address = findPhysicalAddress(addresses[j].page_number);
    }

    // Final print
    for(int k = 0; k < FILE_SIZE; k++) {
       //printf("Virtual address: %d Physical address: %d Value: TBD Offset: %d\n", addresses[k].logical_address, addresses[k].physical_address, addresses[k].offset);
    }

    printf("Page-fault rate: %f\n", page_fault_count / 1000.0);
    printf("TLB hit rate: %f\n", tlb_hit_count / 1000.0);
	return 0;
}
