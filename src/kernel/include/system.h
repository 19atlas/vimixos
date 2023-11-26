#pragma once

//klavye girişi için bellek.
char* buffer;
int _buf = 0;

//anahtarları devre dışı bırakma işlevi.
extern "C" void disable_ints();

//anahtarları etkinleştirme işlevi.
extern "C" void enable_ints();