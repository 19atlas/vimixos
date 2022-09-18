#include"include/initialize.h"
#include"include/stdio.h"
#include"include/ata.h"
#include"include/fs.h"
#include"include/fat12.h"

//funzione globale principale bootloader.
extern "C" void bootloader() {
	//inizializza le componenti.
	initialize();
	//leggi il dato kernel.bin cioe` il nucleo del sistema operativo.
	fread("KERNEL  BIN", 0x0100000);
	//salta all'indirizzo dove e` stato caricato il nucleo ed eseguilo.
	void(*kernel)(void) = (void(*)())0x0100000;
	kernel();
	return;
}