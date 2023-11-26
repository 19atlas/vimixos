#pragma once

#include"stdio.h"
#include"system.h"
#include"pic.h"
#include"ports.h"

char mouse_cycle = 0;
signed char mouse_byte[3];

int mouse_x = 100;
int mouse_y = 100;

void mouse_wait(uint8_t a_type) {
	uint32_t _time_out=100000;
	if(a_type==0) {
		while(_time_out--) {
			if((inb(0x64) & 1)==1)
			{
				return;
			}
		}
		return;
	}
	else {
		while(_time_out--) {
			if((inb(0x64) & 2)==0) {
				return;
			}
		}
		return;
	}
}

void mouse_write(uint8_t a_write) {
	mouse_wait(1);
	outb(0x64, 0xD4);
	mouse_wait(1);
	outb(0x60, a_write);
}

uint8_t mouse_read() {
	mouse_wait(0);
	return inb(0x60);
}

void mouse_handler(registers_t regs) {
	switch(mouse_cycle) {
		case 0:
			mouse_byte[0]=inb(0x60);
			mouse_cycle++;
			break;
		case 1:
			mouse_byte[1]=inb(0x60);
			mouse_cycle++;
			break;
		case 2:
			mouse_byte[2]=inb(0x60);
			mouse_x += mouse_byte[1];
			mouse_y -= mouse_byte[2];
			mouse_cycle=0;
			break;
	}
	outb(0xA0, 0x20);
}

void initialize_mouse(){
	uint8_t _status;
	mouse_wait(1);
	outb(0x64, 0xA8);
	mouse_wait(1);
	outb(0x64, 0x20);
	mouse_wait(0);
	_status=(inb(0x60) | 2);
	mouse_wait(1);
	outb(0x64, 0x60);
	mouse_wait(1);
	outb(0x60, _status);
	mouse_write(0xF6);
	mouse_read();
	mouse_write(0xF4);
	mouse_read();
	IRQ_clear_mask(12);
	register_interrupt_handler(IRQ12, &mouse_handler);
}