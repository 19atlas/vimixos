#include"include/initialize.h"
#include"include/stdio.h"
#include"include/ata.h"
#include"include/fs.h"
#include"include/fat12.h"
#include"include/dt.h"

//bootloader main global function.
extern "C" void bootloader() {
	//initialize the components.
	initialize();
	//read the data kernel.bin ie the core of the operating system.
	fread("KERNEL  BIN", 0x0100000);
	//jump to the address where the kernel was loaded and run it.
	uintptr_t kernel_entry = 0x0100000;
	void(*kernel)(void) = (void(*)())kernel_entry;
	kernel();
	return;
}