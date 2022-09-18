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

//funzione globale principale main.
extern "C" void main() {
	//inizializza le componenti del sistema operativo.
	initialize();
	//scrivi "ciao mondo" sullo schermo.
	printf("SOLE-i386.\n");
	printf("C:>");
	return;
}