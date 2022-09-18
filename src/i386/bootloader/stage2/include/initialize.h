#pragma once

#include"stdio.h"
#include"fs.h"

//inizializza le componenti del gestore d'avvio.
void initialize() {
	initialize_fs();
	return;
}