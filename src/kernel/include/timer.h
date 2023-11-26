#pragma once

#include"stdio.h"
#include"isr.h"
#include"ports.h"

//moments past.
uint32_t tick = 0;

//function to obtain a random number given the maximum value.
int random(int numLimit) {
    static int randSeed, needsInit = 1;
    if (needsInit) {
        randSeed = tick;
        needsInit = 0;
    }
    randSeed = (randSeed * 32719 + 3) % 32749;
    return (randSeed % numLimit) + 1;
}

//clock management function.
static void timer_callback(registers_t regs) {
	tick++;
}

//clock initialization function.
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