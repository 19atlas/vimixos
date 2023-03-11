#include"include/initialize.h"
#include"include/stdio.h"
#include"include/ata.h"
#include"include/fs.h"
#include"include/fat12.h"

//bootloader main global function.
extern "C" void bootloader() {
	//initialize the components.
	initialize();
	//read the data kernel.bin ie the core of the operating system.
	fread("KERNEL  BIN", 0x0100000);
	//jump to the address where the kernel was loaded and run it.
	void(*kernel)(void) = (void(*)())0x0100000;
	kernel();
	return;
}