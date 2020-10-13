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

void encriptar_cadena(unsigned char* cadena, char* key, const char* method){
	if(strcmp(method, CESAR) == 0){
		encripto_cesar(cadena, key, LONG_CHAR);

	}else if(strcmp(method, VIGENERE) == 0){
		encripto_vigenere(cadena, key, LONG_CHAR);

	}else if(strcmp(method, RC4) == 0){
		encripto_rc4(cadena, key, LONG_CHAR);
	}
}

int main(int argc, char const *argv[]){
	FILE* input;
	socket_client_t socket_cliente;
	int continuar = LONG_CHAR;
	char clave[LONG_KEY];
	char* cadena = calloc(LONG_CHAR, sizeof(char));

	strncpy(clave, argv[4]+6, LONG_KEY);
	unsigned char* cadena_unsigned = (unsigned char*) cadena;

	if(argc > 5){
		input = fopen(argv[5], "r");
	}else{
		input = stdin;
	}
	if(!input){
		return -1;
	}

	create_socket_client(&socket_cliente, argv[1], argv[2]);
	connect_socket_client(&socket_cliente);

	while( continuar == LONG_CHAR){
		continuar = fread(cadena_unsigned, sizeof(char), LONG_CHAR, input);

		encriptar_cadena(cadena_unsigned, clave, argv[3]);
		send_socket_client(&socket_cliente, (char*) cadena_unsigned, LONG_CHAR);

		memset(cadena_unsigned, '\0', LONG_CHAR);
	}

	if (input != stdin){
		fclose(input);
	}

	shutdown_socket_client(&socket_cliente);
	close_socket_client(&socket_cliente);
	free(cadena);

	return 0;
}