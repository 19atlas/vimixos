#pragma once

#include"stdio.h"
#include"fs.h"
#include"dt.h"
#include"keyboard.h"
#include"timer.h"
#include"rtc.h"

//inizializza le componenti del gestore d'avvio.
void initialize() {
	initialize_fs();
	initialize_dt();
	initialize_keyboard();
	initialize_timer(1.1931816666);
	initialize_rtc();
	return;
}