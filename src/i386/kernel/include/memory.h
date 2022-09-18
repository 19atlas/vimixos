#pragma once

//funzione per impostare una data parte di memoria ad una destinazione con un valore per una lunghezza data.
void* memset (void *dest, int val, unsigned int len) {
	char* ptr = (char*)dest;
	while (len-- > 0) *ptr++ = val;
	return dest;
}

//funzione per copiare una data parte di memoria da una sorgente ad una destinazione per una lunghezza data.
void* memcpy(void *dest, const void *src, int n) {
	char* d = (char*)dest;
	char* s = (char*)src;
	while(n--)
		*(d++) = *(s++);
	return dest;
}

//funzione per copiare una data parte di memoria da una sorgente ad una destinazione per una lunghezza data con l'ESS.
extern "C" int memcpy_sse(void* dst, void* src, unsigned int count);