#pragma once

//memoria per l'ingresso della tastiera.
char* buffer;
int _buf = 0;

//funzione per disabilitare gli interruttori.
extern "C" void disable_ints();

//funzione per abilitare gli interruttori.
extern "C" void enable_ints();