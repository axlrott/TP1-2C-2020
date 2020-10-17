#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_cesar.h"

void cesarCreate(cesar_t* self, char* key){
	self->key = atoi(key);
}

void cesarEncriptar(cesar_t* self, unsigned char* cadena, int largo){
	for (int i = 0; i < largo ; i++){
		unsigned char cambio = (cadena[i] + self->key);
		cadena[i] = cambio;
	}
}

void cesarDesencriptar(cesar_t* self, unsigned char* cadena, int largo){
	for (int i = 0; i < largo ; i++){
		unsigned char cambio = (cadena[i] - self->key);
		cadena[i] = cambio;
	}
}

void cesarDestroy(cesar_t* self){
}
