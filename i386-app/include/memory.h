#pragma once

//function to set a given part of memory to a destination with a value for a given length.
void* memset (void *dest, int val, unsigned int len) {
	char* ptr = (char*)dest;
	while (len-- > 0) *ptr++ = val;
	return dest;
}

//function to copy a given part of memory from a source to a destination for a given length.
void* memcpy(void *dest, const void *src, int n) {
	char* d = (char*)dest;
	char* s = (char*)src;
	while(n--)
		*(d++) = *(s++);
	return dest;
}

//function to copy a given part of memory from a source to a destination for a given length with the SSE.
extern "C" int memcpy_sse(void* dst, void* src, unsigned int count);