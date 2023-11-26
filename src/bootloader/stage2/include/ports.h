#pragma once

#include<stdint.h>

//output function of an octet to an input and output port.
static inline void outb(uint16_t port, uint8_t value) {
	asm("outb %0, %1" : : "a"(value), "Nd"(port));
	return;
}

//input function of an octet to an input and output port.
static inline uint8_t inb(uint16_t port) {
	uint8_t value;
	asm("inb %1, %0" : "=a"(value) : "Nd"(port));
	return value;
}

//output function of two octets to one input and output port.
static inline void outw(uint16_t port, uint16_t value) {
	asm("out %%ax, %%dx" : : "a"(value), "d"(port));
	return;
}

//input function of two octets to an input and output port.
static inline uint16_t inw(uint16_t port) {
	uint16_t value;
	asm("in %%dx, %%ax" : "=a"(value) : "d"(port));
	return value;
}

//output function of four octets to one input and output port.
static inline void outd(uint32_t port, uint32_t value) {
	asm("outl %%eax, %%dx" : : "a"(value), "d"(port));
}

//input function of four octets to an input and output port.
static inline uint32_t ind(uint32_t port) {
	uint32_t value;
	asm("inl %%dx, %%eax" : "=a"(value) : "d"(port));
	return value;
}