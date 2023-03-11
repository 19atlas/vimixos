#pragma once

#include"string.h"
#include"ports.h"
#include<stdint.h>
#include<stdarg.h>

//imleç konumu.
uint16_t x_pos = 0x0000, y_pos = 0x0000;
//metin rengi.
uint8_t color = 0x07;
//metin arka plan rengi.
uint8_t bg_color = 0x00;

//metin modu bellek adresi 0x03.
uint32_t* video_memory = (uint32_t*)0x000B8000;

//metnin rengini ayarlayın.
void set_color(uint8_t new_color) {
	color = new_color;
	return;
}

//metnin arka plan rengini ayarlar.
void set_bg_color(uint8_t new_color) {
	bg_color = new_color;
	return;
}

//metni bir satır aşağı kaydırır.
void scroll() {
	uint8_t attribute = (0x00 << 0x04) | (0x0F & 0x0F);
	uint16_t blank = 0x0020 | (attribute << 0x0008);
	if(y_pos >= 0x0019) {
		for(uint32_t i = 0x00000000 * 0x00000050; i < 0x00000018 * 0x00000050; i++)
			video_memory[i] = video_memory[i + 0x00000050];
		for(uint32_t i = 0x00000018 * 0x00000050; i < 0x00000019 * 0x00000050; i++)
			video_memory[i] = blank;
		y_pos = 0x0018;
	}
	return;
}

//imlecin ekrandaki konumunu günceller.
void update_cursor_pos(uint16_t x, uint16_t y) {
	uint16_t cursor_pos = y * 0x0050 + x;
	outb(0x03D4, 0x0F);
	outb(0x03D5, (uint8_t)(cursor_pos & 0xFF));
	outb(0x03D4, 0x0E);
	outb(0x03D5, (uint8_t)((cursor_pos >> 0x08) & 0xFF));
	return;
}

//imleç konumunu ilerleterek ekrana bir karakter yazar.
void putc(unsigned char c){
	uint16_t attrib = (0 << 4) | (color & 0x0F);
	volatile uint16_t* where;
	where = (volatile uint16_t *)0xB8000 + (y_pos * 80 + x_pos);
	*where = c | (attrib << 8);
	if(++x_pos >= 80){
		x_pos = 0;
		y_pos++;
	}
	update_cursor_pos(x_pos, y_pos);
	if(y_pos >= 25) {
		x_pos = 0;
		scroll();
	}
	return;
}

//imleci geri hareket ettirerek ekrandaki bir karakteri kaldırır.
void putcback(){
	uint16_t attrib = (0 << 4) | (color & 0x0F);
	volatile uint16_t * where;
	x_pos--;
	if(x_pos < 0) {
		x_pos = 79;
		y_pos--;
	}
	where = (volatile uint16_t *)0xB8000 + (y_pos * 80 + x_pos);
	*where = ' ' | (attrib << 8);
	update_cursor_pos(x_pos, y_pos);
	if(y_pos >= 25) {
		x_pos = 0;
		scroll();
	}
}

//imleç konumunu ilerleterek ekrana bir dizi yazar.
void puts(char* string){
	uint16_t i;
	while(*string){
		switch(*string){
			case 0x0A:
				x_pos = 0x0000;
				y_pos++;
				*string++;
				scroll();
				break;
			case 0x09:
				for(i = 0x0000; i <= 0x0008; i++) {
					putc(' ');
				}
				*string++;
				break;
			default:
				putc(*string);
				*string++;
				break;				
		}
	}
	update_cursor_pos(x_pos, y_pos);
	return;
}

//imleç konumunu ilerleterek ekrana zengin bir dize yazar.
void printf(char* format, ...) {
	va_list ap;
	va_start(ap, format);
	char* pointer;
	for (pointer = format; *pointer != 0x00; pointer++) {
		if (*pointer == '%') {
			++pointer;
			switch (*pointer) {
				case 0x63:
					putc(va_arg(ap, int));
					break;
				case 0x73:
					puts(va_arg(ap, char*));
					break;
				case 0x64:
					puts(int_to_string(va_arg(ap, int), 10));
					break;
				case 0x78:
					puts(int_to_string(va_arg(ap, uint32_t), 16));
					break;
			}
		} else {
			putc(*pointer);
		}
	}
	return;
}