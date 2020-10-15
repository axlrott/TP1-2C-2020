#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "client_tda.h"
#include "common_encriptaciones.h"

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"
#define LONG_CHAR 65
#define LONG_KEY 15
#define CANT_ARG 6

int sendMsj(socket_client_t* skt, FILE* inp, char* env, char* crip, char* key){
	unsigned char* cadena_unsigned = (unsigned char*) env;
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	cesarCreate(&enc_cesar, key);
	vigenereCreate(&enc_vig, key);
	rc4Create(&enc_rc4, key);

	while(fread(cadena_unsigned, sizeof(char), LONG_CHAR, inp)){
		if (ferror(inp)){
			return -1;
		}
		if(strcmp(crip, CESAR) == 0){
			cesarEncriptar(&enc_cesar, cadena_unsigned, LONG_CHAR);
		}else if (strcmp(crip, VIGENERE) == 0){
			vigenereEncriptar(&enc_vig, cadena_unsigned, LONG_CHAR);
		}else if (strcmp(crip, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena_unsigned, LONG_CHAR);
		}
		SockClientSend(skt, (char*) cadena_unsigned, LONG_CHAR);
		memset(cadena_unsigned, '\0', LONG_CHAR);
	}
	cesarCreate(&enc_cesar, key);
	vigenereCreate(&enc_vig, key);
	rc4Create(&enc_rc4, key);
	return 0;
}

void liberarMemoriaInput(FILE* input){
	if (input != stdin){
		fclose(input);
	}
}

int main(int argc, char const *argv[]){
	FILE* input;
	socket_client_t socket_cliente;
	char clave[LONG_KEY];
	char cadena[LONG_CHAR];
	int salida_main = -1;

	if(argc == CANT_ARG){
		input = fopen(argv[5], "r");
	}else if (argc == CANT_ARG-1){
		input = stdin;
	}else{
		return salida_main;
	}
	if(!input){
		return salida_main;
	}

	strncpy(clave, (argv[4]+6), LONG_KEY);
	memset(cadena, '\0', LONG_CHAR);

	if(SockClientCreate(&socket_cliente, (char*) argv[1], (char*) argv[2]) == 0){
		if(SockClientConnect(&socket_cliente) == 0){
			if(sendMsj(&socket_cliente, input, cadena, (char*) argv[3], clave) == 0){
				SockClientDestroy(&socket_cliente);
				salida_main = 0;
			}
		}
	}
	liberarMemoriaInput(input);
	return salida_main;
}
