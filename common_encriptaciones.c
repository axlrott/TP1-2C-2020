#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common_encriptaciones.h"
#define MAX_CHAR 255

int calcular_largo_key(char* key){
	int pos;
	for (pos = 0; key[pos] != '\0'; pos++){
	}
	return pos;
}

void cambiar_posiciones(unsigned char* array, int pos_a, int pos_b){
	unsigned char temp = array[pos_a];
	array[pos_a] = array[pos_b];
	array[pos_b] = temp;
}

void encripto_cesar(unsigned char* cadena, char* key, int largo){
	int key_num = atoi(key);

	for (int i = 0; i < largo ; i++){
		unsigned char cambio = (cadena[i]+key_num);
		cadena[i] = cambio;
	}

}

void desencripto_cesar(unsigned char* cadena, char* key, int largo){
	int key_num = atoi(key);

	for (int i = 0; i < largo ; i++){
		unsigned char cambio = (cadena[i]-key_num);
		cadena[i] = cambio;
	}

}

void encripto_vigenere(unsigned char* cadena, char* key, int largo){
	int j = 0;
	for (int i = 0; i < largo; i++){
		if (key[j] == '\0'){
			j = 0;
		}
		unsigned char cambio = (cadena[i] + key[j]);
		cadena[i] = cambio;
		j++;
	}
}

void desencripto_vigenere(unsigned char* cadena, char* key, int largo){
	int j = 0;
	for (int i = 0; i < largo; i++){
		if (key[j] == '\0'){
			j = 0;
		}
		unsigned char cambio = (cadena[i] - key[j]);
		cadena[i] = cambio;
		j++;
	}
}

void kda_rc4(unsigned char* array_numerico, char* key, int largo_array){
	int j = 0;
	int largo_key = calcular_largo_key(key);

	for (int i = 0; i < largo_array; i++){
		array_numerico[i] = i;
	}
	
	for (int i = 0; i < largo_array; i++){
		j= (j + key[i % largo_key] + array_numerico[i]) & MAX_CHAR;
		cambiar_posiciones(array_numerico, i, j);
	}
}

void prga_rc4(unsigned char* array_numerico, unsigned char* cadena, int largo){
	int pos_a = 0;
	int pos_b = 0;
	unsigned char output;
	int pos_output;

	for (int k = 0; k < largo; k++){
		pos_a = (pos_a + 1) & MAX_CHAR;
		pos_b = (pos_b + array_numerico[pos_a]) & MAX_CHAR;
		cambiar_posiciones(array_numerico, pos_a, pos_b);

		pos_output = (array_numerico[pos_a] + array_numerico[pos_b]) & MAX_CHAR;
		output = array_numerico[pos_output];
		cadena[k] = cadena[k] ^ output;
	}
}

void encripto_rc4(unsigned char* cadena, char* key, int largo){
	int largo_array = 256;
	unsigned char array_numerico[largo_array];

	kda_rc4(array_numerico, key, largo_array);
	prga_rc4(array_numerico, cadena, largo);

}
