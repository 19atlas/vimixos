#pragma once

#include"stdio.h"
#include"string.h"
#include"ata.h"
#include<stdint.h>

//struttura del blocco dei parametri del SIEB.
struct bios_parameter_block {
	//salto corto e nop.
	uint8_t NOP[0x03];
	//codice del produttore di apparecchiature originali.
	uint8_t BPB_OEM[0x08];
	//numero di octeti per settore.
	uint16_t BPB_BYTES_PER_SECTOR;
	//numero di settori per gruppo.
	uint8_t BPB_SECTORS_PER_CLUSTER;
	//numero di settori riservati.
	uint16_t BPB_RESERVED_SECTORS;
	//numero di tavole di allocazione dei dati.
	uint8_t BPB_FAT_NUMBER;
	//numero di entrate nel percorso radice.
	uint16_t BPB_DIR_ENTRIES_NUMBER;
	//numero di settori totale.
	uint16_t BPB_TOTAL_SECTORS;
	//codice del tipo di dispositivo di memoria.
	uint8_t BPB_MEDIA_DESCRIPTOR_TYPE;
	//numero di settori per tavola di allocazione dei dati.
	uint16_t BPB_SECTORS_PER_FAT;
	//numero di settori per traccia.
	uint16_t BPB_SECTORS_PER_TRACK;
	//numero di testine.
	uint16_t BPB_HEAD_NUMBER;
	//numero di settori nascosti.
	uint32_t BPB_HIDDEN_SECTORS;
	//numero di settori larghi.
	uint32_t BPB_LARGE_SECTOR_NUMBER;
} __attribute((packed));

//struttura della traccia d'avvio estesa.
struct extended_boot_record {
	//numero di identificazione del dispositivo di memoria.
	uint8_t EBR_DRIVE_NUMBER;
	//riservato.
	uint8_t EBR_RESERVED;
	//firma.
	uint8_t EBR_SIGNATURE;
	//numero di identificazione del volume.
	uint32_t EBR_VOLUME_ID;
	//nome del volume.
	uint8_t EBR_VOLUME_LABEL[0x0B];
	//stringa di identificazione del tipo di struttura del disco.
	uint8_t EBR_SYSTEM_ID;
} __attribute((packed));

//dichiara un puntatore alla struttura del blocco dei parametri del SIEB.
bios_parameter_block* bpb;
//dichiara un puntatore alla struttura della traccia d'avvio estesa.
extended_boot_record* ebr;

//funzione della lettura della tavola di allocazione dei dati.
void read_fat() {
	//leggi la tavola di allocazione dei dati.
	read_sectors(0x20000, bpb->BPB_RESERVED_SECTORS, bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT);
	return;
}

//funzione della lettura del percorso radice.
void read_root_dir() {
	//leggi il percorso radice.
	read_sectors(0x30000, bpb->BPB_RESERVED_SECTORS + bpb->BPB_FAT_NUMBER * bpb->BPB_SECTORS_PER_FAT,
	(bpb->BPB_DIR_ENTRIES_NUMBER * 32 + bpb-> BPB_BYTES_PER_SECTOR -1) / bpb->BPB_BYTES_PER_SECTOR);
	return;
}

//funzione di inizializzazione della struttura del disco.
void initialize_fs() {
	bpb = (bios_parameter_block*)0x00007C00;
	ebr = (extended_boot_record*)0x00007C24;
	read_fat();
	read_root_dir();
	return;
}