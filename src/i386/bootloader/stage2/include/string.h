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