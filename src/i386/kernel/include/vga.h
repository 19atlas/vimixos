#include"stdio.h"
#define VIDEO_MEMORY_ADDRESS 0xb8000;
#define WIDTH 80
#define HEIGHT 25


static short xx=0;
static short yy=0;

unsigned int strlen(char *str){
    unsigned int len=0;
    while(str[len]){
        len++;
    }
    return len;
}

void vga_init(){
    short *buffer=(short *)VIDEO_MEMORY_ADDRESS;
    for(short i=0;i<=80*25*2;i++){
        buffer[i]=0x4020;
    }
}
void term_put(char *str){
    short *buffer=(short *)VIDEO_MEMORY_ADDRESS;
    for(char i=0;i<=strlen(str);i++){
        if(str[i]=='\n'|| xx==WIDTH){
            yy++;
            xx=0;
        }else{
            if(str[i]!='\0'){
                buffer[yy*WIDTH+xx]=str[i]|0x40<<8;
            }
            xx++;
        }
    }
}
/*
void clearKOD(){
    int i=0;
	
	 // empty text with white text.
	signed int blankCell = string_size(" ");
	
	for (i = 0; i < HEIGHT; i++){
      for (int j = 0; j < WIDTH; j++) {
        video_memory[2 * (WIDTH * i + j)] = '\0';
        video_memory[2 * (WIDTH * i + j) + 1] = 0x0B;
      }
    }
}
*/