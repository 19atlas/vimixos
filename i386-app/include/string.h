#pragma once

#include<stdint.h>
#include<stdbool.h>

//converts a number to a string.
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

//compare two strings.
bool compare_strings(const char* string1, const char* string2) {
	while(*string1!=0) {
		if(*string1 != *string2)
			return false;
		string1++;
		string2++;
	}
	return true;
}

//compares two strings and returns false if they are different.
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


void clear_string(char* string) {  //empties a string.
	while(*string != 0) {
		*string = 0;
		string++;
	}
	return;
}


int string_size(char* string) {  //returns the length of a string.
	int counter = 0;
	while(*string != 0) {
		string++;
		counter++;
	}
	return counter;
}