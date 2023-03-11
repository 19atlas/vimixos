#pragma once

#include"fs.h"
#include<stdint.h>
#include<stdbool.h>

//data entry structure.
struct file_entry {
	//data name.
	uint8_t name[11];
	//attributes.
	uint8_t attributes;
	//reserved.
	uint8_t reserved;
	//creation date.
	uint8_t created_time_tenths;
	uint16_t created_time;
	uint16_t created_date;
	//last access date.
	uint16_t accessed_time;
	//first group upper part.
	uint16_t first_cluster_high;
	//date of last modification.
	uint16_t modified_time;
	uint16_t modified_date;
	//lower first group.
	uint16_t first_cluster_low;
	//data size.
	uint32_t size;
} __attribute((packed));

//reads data from disk to the specified memory address.
bool fread(const char* filename, uint32_t address) {
	file_entry* file;
	char* mem = (char*)0x30000;
    while ((char*)mem < (char*)0x50000) {
		if(compare_strings(filename, mem)==true) {
			file = (file_entry*)mem;
			break;
		}
		mem+=32;
	}
	//if the counter has arrived at the address 0x00050000 it means that the entry has not been found.
	if((uint8_t*)mem == (uint8_t*)0x00050000)
		return false;
	//calculates the block of logical address.
	uint32_t lba = ((bpb->BPB_RESERVED_SECTORS + bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT + (bpb->BPB_DIR_ENTRIES_NUMBER * 32 + bpb-> BPB_BYTES_PER_SECTOR -1) / bpb->BPB_BYTES_PER_SECTOR)) + (file->first_cluster_low - 2) * bpb-> BPB_SECTORS_PER_CLUSTER;
	//read the sectors containing the requested data.
	read_sectors(address, lba, (file->size / bpb->BPB_BYTES_PER_SECTOR + 1));
	return true;
}