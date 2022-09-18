#pragma once

#include"fs.h"
#include<stdint.h>
#include<stdbool.h>

//struttura dell'entrata dei dati.
struct file_entry {
	//nome dei dati.
	uint8_t name[11];
	//attributi.
	uint8_t attributes;
	//riservato.
	uint8_t reserved;
	//data di creazione.
	uint8_t created_time_tenths;
	uint16_t created_time;
	uint16_t created_date;
	//data dell'ultimo accesso.
	uint16_t accessed_time;
	//primo gruppo parte alta.
	uint16_t first_cluster_high;
	//data dell'ultima modifica.
	uint16_t modified_time;
	uint16_t modified_date;
	//primo gruppo parte bassa.
	uint16_t first_cluster_low;
	//grandezza dei dati.
	uint32_t size;
} __attribute((packed));

//legge dei dati dal disco all'indirizzo di memoria specificato.
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
	//se il contatore e` arrivato all'indirizzo 0x00050000 significa che l'entrata non e` stata trovata.
	if((uint8_t*)mem == (uint8_t*)0x00050000)
		return false;
	//calcola il blocco di indirizzo logico.
	uint32_t lba = ((bpb->BPB_RESERVED_SECTORS + bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT + (bpb->BPB_DIR_ENTRIES_NUMBER * 32 + bpb-> BPB_BYTES_PER_SECTOR -1) / bpb->BPB_BYTES_PER_SECTOR)) + (file->first_cluster_low - 2) * bpb-> BPB_SECTORS_PER_CLUSTER;
	//leggi i settori contenenti i dati richiesti.
	read_sectors(address, lba, (file->size / bpb->BPB_BYTES_PER_SECTOR + 1));
	return true;
}