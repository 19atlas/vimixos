#pragma once

#include"ports.h"

typedef struct {
	char second;
	char minute;
	char hour;
	char day_of_week;
	char day_of_month;
	char month;
	char year;
} time_t;

time_t time;
bool bcd;

//funzione per scrivere nei registri dell'orologio del tempo reale.
char read_register(unsigned char reg) {
	outb(0x70, reg);
	return inb(0x71);
}

//funzione per leggere dai registri dell'orologio del tempo reale.
void write_register(unsigned char reg, unsigned char value) {
	outb(0x70, reg);
	outb(0x71, value);
}
 
char bcd2bin(unsigned char bcd) {
	return ((bcd >> 4) * 10) + (bcd & 0x0F);
}
 
void gettime(time_t *time) {
	memcpy_sse(time, &time, sizeof(time_t));
}

//funzione della gestione dell'orologio del tempo reale.
void rtc_handler(registers_t regs) {
	if(read_register(0x0C) & 0x10){
		if(bcd){
			time.second = bcd2bin(read_register(0x00));
			time.minute = bcd2bin(read_register(0x02));
			time.hour   = bcd2bin(read_register(0x04));
			time.month  = bcd2bin(read_register(0x08));
			time.year   = bcd2bin(read_register(0x09));
			time.day_of_week  = bcd2bin(read_register(0x06));
			time.day_of_month = bcd2bin(read_register(0x07));
		}else {
			time.second = read_register(0x00);
			time.minute = read_register(0x02);
			time.hour   = read_register(0x04);
			time.month  = read_register(0x08);
			time.year   = read_register(0x09);
			time.day_of_week  = read_register(0x06);
			time.day_of_month = read_register(0x07);
		}
	}
}

//funzione dell'inizializzazione dell'orologio del tempo reale.
void initialize_rtc() {
	unsigned char status; 
	status = read_register(0x0B);
	status |=  0x02;
	status |=  0x10;
	status &= ~0x20;
	status &= ~0x40;
	bcd  =  !(status & 0x04);
	write_register(0x0B, status);
	read_register(0x0C);
	register_interrupt_handler(IRQ8, &rtc_handler);
}