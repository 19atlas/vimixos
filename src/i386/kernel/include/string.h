#pragma once

#include<stdint.h>
#include<stdbool.h>

//converte un numero in una stringa.
char* int_to_string(unsigned int num, int base) { 
	static char repr[]= "0123456789ABCDEF";
	static char buffer[50]; 
	char *ptr; 

	ptr = &buffer[49]; 
	*ptr = '\0'; 

	do {
		*--ptr = repr[num%base]; 
		num /= base; 
	}while(num != 0); 

	return(ptr); 
}

//compara due stringhe.
bool compare_strings(const char* string1, const char* string2) {
	while(*string1!=0) {
		if(*string1 != *string2)
			return false;
		string1++;
		string2++;
	}
	return true;
}

//compara due stringhe e se sono diverse ritorna falso.
bool compare_strings_ws(const char* string1, const char* string2) {
	while(1) {
		if(*string1==0 && *string2!=0)
			return false;
		if(*string1==0)
			return true;
		if(*string1 != *string2)
			return false;
		string1++;
		string2++;
	}
	return true;
}

//svuota una stringa.
void clear_string(char* string) {
	while(*string != 0) {
		*string = 0;
		string++;
	}
	return;
}

//ritorna la lunghezza di una stringa.
int string_size(char* string) {
	int counter = 0;
	while(*string != 0) {
		string++;
		counter++;
	}
	return counter;
}