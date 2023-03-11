#pragma once

#include"stdio.h"
#include"fs.h"
#include"dt.h"
#include"keyboard.h"
#include"timer.h"
#include"rtc.h"
#include"mouse.h"

//initialize the boot manager components.
void initialize() {
	initialize_fs();
	initialize_dt();
	initialize_keyboard();
	initialize_timer(1.1931816666);
	initialize_rtc();
	//initialize_mouse();
	return;
}