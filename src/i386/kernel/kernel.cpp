#include"include/initialize.h"
#include"include/stdio.h"
#include"include/ata.h"
#include"include/fs.h"
#include"include/fat12.h"
#include"include/memory.h"
#include"include/dt.h"
#include"include/isr.h"
#include"include/keyboard.h"
#include"include/mouse.h"
#include"include/timer.h"
#include"include/rtc.h"
#include"include/math.h"
#include"include/pic.h"
#include"include/vga.h"

#define MSIZE 48 * M
#define GUI_MODE 0
#define NETWORK_MODE 0

//main function
extern "C" int main() {
	printf("vimixOS\n");
	//initalize system resources
	initialize();
	vga_init();
	printf(">_");
	return 0;
}