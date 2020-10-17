#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_vigenere.h"

void vigenereCreate(vigenere_t* self, char* key){
	self->key = key;
	self->pos = 0;
}

void vigenereEncriptar(vigenere_t* self, unsigned char* cadena, int largo){
	for (int i = 0; i < largo; i++){
		if (self->key[self->pos] == '\0'){
			self->pos = 0;
		}
		unsigned char cambio = (cadena[i] + self->key[self->pos]);
		cadena[i] = cambio;
		self->pos++;
	}
}

void vigenereDesencriptar(vigenere_t* self, unsigned char* cadena, int largo){
	for (int i = 0; i < largo; i++){
		if (self->key[self->pos] == '\0'){
			self->pos = 0;
		}
		unsigned char cambio = (cadena[i] - self->key[self->pos]);
		cadena[i] = cambio;
		self->pos++;
	}
}

void vigenereDestroy(vigenere_t* self){
}
