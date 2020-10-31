#define _POSIX_C_SOURCE 200112L

#include "client_cripto.h"
#include "common_socket.h"
#include "client_tda.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"

void criptClCreate(clCript_t* self, char* cripto, char* clave){
	self->cripto = cripto;
	self->clave = clave;
}

bool criptClSocketInit(clCript_t* self, char* host, char* port){
	if(socketClientCreate(&(self->cliente), host, port) == 0){
		if(socketClientConnect(&(self->cliente)) == 0){
			return true;
		}
	}
	return false;
}

bool criptClEnviarMsj(clCript_t* self, FILE* input, int cant){
	unsigned char cadena[cant];
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	memset(cadena, '\0', cant);
	cesarCreate(&enc_cesar, self->clave);
	vigenereCreate(&enc_vig, self->clave);
	rc4Create(&enc_rc4, self->clave);

	while(!feof(input)){
		int largo = fread(cadena, sizeof(char), cant, input);
		if (ferror(input)){
			return false;
		}
		if(strcmp(self->cripto, CESAR) == 0){
			cesarEncriptar(&enc_cesar, cadena, cant);
		}else if (strcmp(self->cripto, VIGENERE) == 0){
			vigenereEncriptar(&enc_vig, cadena, cant);
		}else if (strcmp(self->cripto, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena, cant);
		}
		if (socketClientSend(&(self->cliente), (char*) cadena, largo) == -1){
			return false;
		}
		memset(cadena, '\0', cant);
	}
	cesarDestroy(&enc_cesar);
	vigenereDestroy(&enc_vig);
	rc4Destroy(&enc_rc4);
	return true;
}

void criptClDestroy(clCript_t* self){
	socketClientDestroy(&(self->cliente));
}
