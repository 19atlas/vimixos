#pragma once

#include"stdio.h"
#include"isr.h"
#include"ports.h"

//attimi passati.
uint32_t tick = 0;

//funzione per ottenere un numero casuale dato il valore massimo.
int random (int numLimit) {
    static int randSeed, needsInit = 1;
    if (needsInit) {
        randSeed = tick;
        needsInit = 0;
    }
    randSeed = (randSeed * 32719 + 3) % 32749;
    return (randSeed % numLimit) + 1;
}

//funzione di gestione dell'orologio.
static void timer_callback(registers_t regs) {
	tick++;
}

//funzione di inizializzazione dell'orologio.
void initialize_timer(uint32_t frequency) {
	register_interrupt_handler(IRQ0, &timer_callback);
	uint32_t divisor = 1193180 / frequency;
	outb(0x43, 0x36);
	uint8_t l = (uint8_t)(divisor & 0xFF);
	uint8_t h = (uint8_t)((divisor>>8) & 0xff);
	outb(0x40, l);
	outb(0x40, h);
	return;
}