#pragma once

#include"ports.h"
#include<stdint.h>

#define STATUS_BUSY 0x80
#define STATUS_READY 0x40
#define STATUS_DRQ 0x08
#define STATUS_DF 0x20
#define STATUS_ERR 0x01

static void ATA_wait_BSY() {
	while(inb(0x01F7) & STATUS_BUSY);
}

static void ATA_wait_DRQ() {
	while(!inb(0x01F7) & STATUS_READY);
}

//disk reading function.
void read_sectors(uint32_t address, uint32_t lba, uint8_t sector_count) {
	//wait for the disk to be ready and free to read.
	ATA_wait_BSY();
	//set the reading parameters.
	outb(0x01F6, 0xE0 | ((lba >> 0x18) & 0x0F));
	outb(0x01F2, sector_count);
	outb(0x01F3, (uint8_t)lba);
	outb(0x01F4, (uint8_t)(lba >> 8));
	outb(0x01F5, (uint8_t)(lba >> 16));
	//sends the read signal.
	outb(0x01F7, 0x20);
	uint16_t* target = (uint16_t*)address;
	for(uint32_t i = 0x00; i < sector_count; i++) {
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(uint32_t j = 0x00; j < 0x0100; j++)
			//copy data to MAC memory.
			target[j] = inw(0x01F0);
		target += 0x0100;
	}
	return;
}

//disk writing
void write_sectors(uint32_t lba, uint8_t sector_count, uint32_t* bytes) {
	//wait for the disk to be ready and free to read.
	ATA_wait_BSY();
	//set the reading parameters.
	outb(0x01F6, 0xE0 | ((lba >> 0x18) & 0x0F));
	outb(0x01F2, sector_count);
	outb(0x01F3, (uint8_t)lba);
	outb(0x01F4, (uint8_t)(lba >> 8));
	outb(0x01F5, (uint8_t)(lba >> 16));
	//sends write signal.
	outb(0x01F7, 0x30);
	for(uint32_t i = 0x00; i < sector_count; i++) {
		ATA_wait_BSY();
		ATA_wait_DRQ();
		for(uint32_t j = 0x00; j < 0x0100; j++)
			//copy the data to the storage device.
			outd(0x01F0, bytes[i]);
	}
	return;
}
