#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_encriptaciones.h"
#define MAX_CHAR 255

int calcularLargoKey(char* key){
	int pos;
	for (pos = 0; key[pos] != '\0'; pos++){
	}
	return pos;
}

void cambiarPosiciones(unsigned char* array, int posA, int posB){
	unsigned char temp = array[posA];
	array[posA] = array[posB];
	array[posB] = temp;
}

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

void kdaRC4(rc4_t* self, int largo_array){
	int j = 0;
	int largo_key = calcularLargoKey(self->key);

	for (int i = 0; i < largo_array; i++){
		self->array[i] = i;
	}

	for (int i = 0; i < largo_array; i++){
		j= (j + self->key[i % largo_key] + self->array[i]) & MAX_CHAR;
		cambiarPosiciones(self->array, i, j);
	}
}

void prgaRC4(rc4_t* self, unsigned char* cadena, int largo){
	for (int k = 0; k < largo; k++){
		self->posA = (self->posA + 1) & MAX_CHAR;
		self->posB = (self->posB + self->array[self->posA]) & MAX_CHAR;
		cambiarPosiciones(self->array, self->posA, self->posB);

		int pos_out = (self->array[self->posA] + self->array[self->posB]) & MAX_CHAR;
		unsigned char output = self->array[pos_out];
		cadena[k] = cadena[k] ^ output;
	}
}

void rc4Create(rc4_t* self, char* key){
	self->key = key;
	self->posA = 0;
	self->posB = 0;
}

void rc4Encriptar(rc4_t* self, unsigned char* cadena, int largo){
	int largo_array = 256;
	kdaRC4(self, largo_array);
	prgaRC4(self, cadena, largo);
}

void rc4Destroy(rc4_t* self){

}
