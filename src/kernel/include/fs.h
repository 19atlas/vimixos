#pragma once

#include"stdio.h"
#include"string.h"
#include"ata.h"
#include<stdint.h>

//structure of the parameter block of the SIEB.
struct bios_parameter_block {
	uint8_t NOP[0x03];  //short jump and nop.
	uint8_t BPB_OEM[0x08];  //original equipment manufacturer code.
	uint16_t BPB_BYTES_PER_SECTOR;  //number of octets per sector.
	uint8_t BPB_SECTORS_PER_CLUSTER;  //number of sectors per group.
	uint16_t BPB_RESERVED_SECTORS;  //number of reserved sectors.
	uint8_t BPB_FAT_NUMBER;  //number of data allocation tables.
	uint16_t BPB_DIR_ENTRIES_NUMBER;  //number of entries in the root path.
	uint16_t BPB_TOTAL_SECTORS;  //total number of sectors.
	uint8_t BPB_MEDIA_DESCRIPTOR_TYPE;  //memory device type code.
	uint16_t BPB_SECTORS_PER_FAT;  //number of sectors per data allocation table.
	uint16_t BPB_SECTORS_PER_TRACK;  //number of sectors per track.
	uint16_t BPB_HEAD_NUMBER;   //number of heads.
	uint32_t BPB_HIDDEN_SECTORS;   //number of hidden sectors.
	uint32_t BPB_LARGE_SECTOR_NUMBER;   //number of wide sectors.
} __attribute((packed));

//extended boot track structure.
struct extended_boot_record {
	uint8_t EBR_DRIVE_NUMBER;//identification number of the storage device.
	uint8_t EBR_RESERVED;
	uint8_t EBR_SIGNATURE; //signature.
	uint32_t EBR_VOLUME_ID; //volume identification number
	uint8_t EBR_VOLUME_LABEL[0x0B]; //volume name
	uint8_t EBR_SYSTEM_ID; //disk structure type identification string.
} __attribute((packed));

//declares a pointer to the structure of the SIEB's parameter block.
bios_parameter_block* bpb;
//declares a pointer to the extended boot trace structure.
extended_boot_record* ebr;

//function of reading the data allocation table.
void read_fat() {
	//read the data allocation table.
	read_sectors(0x20000, bpb->BPB_RESERVED_SECTORS, bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT);
	return;
}

//function of reading the root path.
void read_root_dir() {
	//read the root path.
	read_sectors(0x30000, bpb->BPB_RESERVED_SECTORS + bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT,
	(bpb->BPB_DIR_ENTRIES_NUMBER * 32 + bpb-> BPB_BYTES_PER_SECTOR -1) / bpb->BPB_BYTES_PER_SECTOR);
	return;
}

//disk structure initialization function.
void initialize_fs() {
	bpb = (bios_parameter_block*)0x00007C00;
	ebr = (extended_boot_record*)0x00007C24;
	read_fat();
	read_root_dir();
	return;
}