#pragma once

#include"stdio.h"
#include"isr.h"
#include"system.h"
#include"rtc.h"
#include"fat12.h"
#include<stdint.h>
//#include"vga.h"

//lowercase key list. (trq)
const char sc_table[] ={
	0x00, 0x00, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0x00, 0x00,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', 'g', 'u',
	0x00, 0x00, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', 's',
	'i', ',', 0x00, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', 'o',
	'c', '.', 0x00, '*',
	0x00, ' '
};

//shift key list.
const char sc_tableC[] ={
	0x00, 0x00, '!', '@',
	'^', '+', '%', '&',
	'/', '(', ')', '=',
	'?', '_', 0x00, 0x00,
	'Q', 'W', 'E', 'R',
	'T', 'Y', 'U', 'I',
	'O', 'P', '{', '}',
	0x00, 0x00, 'A', 'S',
	'D', 'F', 'G', 'H',
	'J', 'K', 'L', ':',
	'"', '~', 0x00, '|',
	'Z', 'X', 'C', 'V',
	'B', 'N', 'M', '<',
	'>', '?', 0x00, '*',
	0x00, ' '
};

int lshift = 0x00;
int rshift = 0x00;

void keyboard_handler(registers_t regs){
	//gets the key pressed.
	uint8_t k = inb(0x60);
	uint8_t c = 0x00;
	//translate the keyboard code into a letter character.
	if(k < 0x3A)
		c = sc_table[k];
	//if the pressed letter is a character.
	if(c != 0x00){
		//check if the shift keys are pressed.
		switch(lshift | rshift){
			case 0x01: //uppercase.
				buffer[_buf] = sc_tableC[k];
				putc(sc_tableC[k]);
				_buf++;
				buffer[_buf] = 0x00;
				break;
			case 0x00: //lowercase.
				buffer[_buf] = c;
				putc(c);
				_buf++;
				buffer[_buf] = 0x00;
				break;
		}
	} else {
		//if the key pressed has zero as a value check the code.
		switch(k){
			case 0x0E:  //clear back key.
				if(_buf!=0x00) {
					_buf--;
					buffer[_buf] = 0x00;
					putcback();
				}
				break;
			
			case 0x2A:  //left shift key pressed.
				lshift = 0x01;
				break;
			
			case 0xAA:  //left shift key released.
				lshift = 0x00;
				rshift = 0x00;
				break;
			
			case 0x36:  //right shift key pressed.
				rshift = 0x01;
				break;
			
			case 0xb6:  //right shift key released.
				lshift = 0x00;
				rshift = 0x00;
				break;
			
			case 0x3A:  //caps lock pressed.
				if(lshift == 0x00){
					lshift = 0x01;
				}
				else {
					lshift = 0x00;
				}
				break;
			
			case 0x1C:  //enter pressed.
				printf("\n");
				if(compare_strings_ws("help", buffer) == true){
					printf("help    - prints a list of available commands.\n");
					printf("dir     - prints the contents of the root directory.\n");
					printf("time    - prints the current time.\n");
				} else if(compare_strings_ws("dir", buffer) == true) {
					file_entry* file;
					char* mem = (char*)0x30000;
					while ((char*)mem < (char*)0x50000) {
						file = (file_entry*)mem;
						if(file->size == 0)
							break;
						printf("%s %d bytes.\n", mem, file->size);
						mem += 32;
					}
				} else if(compare_strings_ws("time", buffer) == true) {
					printf("%d/%d/%d - %d:%d:%d\n", time.day_of_month, time.month, time.year, time.hour, time.minute, time.second);
				} else if(fread(buffer, 0x150000)){
					void (*app)(void) = (void (*)())0x150000;
					app();
				} else if(compare_strings_ws("echo", buffer) == true){
					printf("echo\n");
				} else if(compare_strings_ws("clear", buffer) == true){
					//clear function
					int i=0;
	
					// empty text with white text.
					signed char blankCell = string_size(" ");
	
					for (i = 0; i < 25; i++){
    				  for (int j = 0; j < 80; j++) {
        		    	video_memory[2 * (80 * i + j)] = '\0';
        				video_memory[2 * (80 * i + j) + 1] = 0x0B;
      				}
    				}
    				//initialize_keyboard();
					//update_cursor_pos(0x00,0x00);
				} else {
					printf("Invalid command. Type help for a list of available commands.\n");
				}
				clear_string(buffer);
				_buf = 0;
				printf(">_");
				break;
		}
	}
}

//keyboard initialization function.
void initialize_keyboard(){
	//initialize the keyboard switch.
	register_interrupt_handler(IRQ1, &keyboard_handler);
	*buffer = 0;
}