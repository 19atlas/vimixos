#pragma once

#include<stdint.h>

//funzione di uscita di un octeto ad una porta di ingresso ed uscita.
static inline void outb(uint16_t port, uint8_t value) {
	asm("outb %0, %1" : : "a"(value), "Nd"(port));
	return;
}

//funzione di entrata di un octeto ad una porta di ingresso ed uscita.
static inline uint8_t inb(uint16_t port) {
	uint8_t value;
	asm("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

//funzione di uscita di due octeti ad una porta di ingresso ed uscita.
static inline void outw(uint16_t port, uint16_t value) {
	asm("out %%ax, %%dx" : : "a"(value), "d"(port));
	return;
}

//funzione di entrata di due octeti ad una porta di ingresso ed uscita.
static inline uint16_t inw(uint16_t port) {
	uint16_t value;
	asm("in %%dx, %%ax" : "=a"(value) : "d"(port));
	return value;
}

//funzione di uscita di quattro octeti ad una porta di ingresso ed uscita.
static inline void outd(uint32_t port, uint32_t value) {
	asm("outl %%eax, %%dx" : : "a"(value), "d"(port));
}

//funzione di entrata di quattro octeti ad una porta di ingresso ed uscita.
static inline uint32_t ind(uint32_t port) {
	uint32_t value;
	asm("inl %%dx, %%eax" : "=a"(value) : "d"(port));
	return value;
}