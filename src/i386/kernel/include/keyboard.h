#pragma once

#include"stdio.h"
#include"isr.h"
#include"system.h"
#include"rtc.h"
#include"fat12.h"

#include<stdint.h>

//lista dei tasti minuscoli.
const char sc_table[] ={
	0x00, 0x00, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0x00, 0x00,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', '[', ']',
	0x00, 0x00, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';',
	'\'', '`', 0x00, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '/', 0x00, '*',
	0x00, ' '
};

//lista dei tasti maiuscoli.
const char sc_tableC[] ={
	0x00, 0x00, '!', '@',
	'#', '$', '%', '^',
	'&', '*', '(', ')',
	'_', '+', 0x00, 0x00,
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
	//ricava il tasto premuto.
	uint8_t k = inb(0x60);
	uint8_t c = 0x00;
	//traduci il codice tastiera in una lettera carattere.
	if(k < 0x3A)
		c = sc_table[k];
	//se la lettera premuta e` un carattere.
	if(c != 0x00){
		//controlla se i tasti maiuscolo sono premuti.
		switch(lshift | rshift){
			case 0x01: //maiuscolo.
				buffer[_buf] = sc_tableC[k];
				putc(sc_tableC[k]);
				_buf++;
				buffer[_buf] = 0x00;
				break;
			case 0x00: //minuscolo.
				buffer[_buf] = c;
				putc(c);
				_buf++;
				buffer[_buf] = 0x00;
				break;
		}
	} else {
		//se il tasto premuto ha zero come valore controlla il codice.
		switch(k){
			//tasto cancella indietro.
			case 0x0E:
				if(_buf!=0x00) {
				_buf--;
				buffer[_buf] = 0x00;
				putcback();
				}
				break;
			//tasto maiuscolo sinistro premuto.
			case 0x2A:
				lshift = 0x01;
				break;
			//tasto maiuscolo sinistro rilasciato.
			case 0xAA:
				lshift = 0x00;
				rshift = 0x00;
				break;
			//tasto maiuscolo destro premuto.
			case 0x36:
				rshift = 0x01;
				break;
			//tasto maiuscolo destro rilasciato.
			case 0xb6:
				lshift = 0x00;
				rshift = 0x00;
				break;
			//blocco maiuscolo premuto.
			case 0x3A:
				if(lshift == 0x00)
					lshift = 0x01;
				else lshift = 0x00;
				break;
			//invio premuto.
			case 0x1C:
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
				} else {
					printf("Invalid command. Type help for a list of available commands.\n");
				}
				clear_string(buffer);
				_buf = 0;
				printf("C:>");
				break;
		}
	}
}

//funzione di inizializzazione della tastiera.
void initialize_keyboard(){
	//inizializza l'interruttore della tastiera.
	register_interrupt_handler(IRQ1, &keyboard_handler);
	*buffer = 0;
}
