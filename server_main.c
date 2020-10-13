#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "server_tda.h"
#include "common_encriptaciones.h"

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"
#define LONG_CHAR 65
#define LONG_KEY 10


void desencriptar_cadena(unsigned char* cadena, char* key, const char* method){

	if(strcmp(method, CESAR) == 0){
		desencripto_cesar(cadena, key, LONG_CHAR);

	}else if(strcmp(method, VIGENERE) == 0){
		desencripto_vigenere(cadena, key, LONG_CHAR);

	}else if(strcmp(method, RC4) == 0){
		encripto_rc4(cadena, key, LONG_CHAR);
	}
}

int main(int argc, char const *argv[]){
	socket_server_t socket_servidor;
	char* cadena_recibida = calloc(LONG_CHAR+1, sizeof(char));
	char clave[LONG_KEY];
	int continuar = 1;

	strncpy(clave, argv[3]+6, LONG_KEY);

	create_socket_server(&socket_servidor, argv[1]);
	bind_socket_server(&socket_servidor);
	listen_socket_server(&socket_servidor, 10);
	accept_socket_server(&socket_servidor);

	while(continuar == 1){
		continuar = recv_socket_server(&socket_servidor, cadena_recibida, LONG_CHAR);
		unsigned char* cadena_unsigned = (unsigned char*) cadena_recibida;
		desencriptar_cadena(cadena_unsigned, clave, argv[2]);
		if (continuar != 0){
			printf("%s", cadena_unsigned);
		}
		memset(cadena_recibida, '\0', LONG_CHAR);
	}

	shutdown_socket_server(&socket_servidor);
	close_socket_server(&socket_servidor);
	free(cadena_recibida);

	return 0;
}