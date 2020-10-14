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
#define LONG_KEY 15
#define CANT_LISTEN 10
#define CANT_ARG 4


void desencriptar_cadena(unsigned char* cadena, char* key, const char* method){

	if(strcmp(method, CESAR) == 0){
		desencripto_cesar(cadena, key, LONG_CHAR);

	}else if(strcmp(method, VIGENERE) == 0){
		desencripto_vigenere(cadena, key, LONG_CHAR);

	}else if(strcmp(method, RC4) == 0){
		encripto_rc4(cadena, key, LONG_CHAR);
	}
}

int imprimir_mensaje(socket_server_t* socket, char* cadena, char* cripto, char* key){
	int continuar = 1;

	while(continuar == 1){
		continuar = recv_socket_server(socket, cadena, LONG_CHAR);
		unsigned char* cadena_unsigned = (unsigned char*) cadena;
		desencriptar_cadena(cadena_unsigned, key, cripto);
		
		if (continuar > 0){
			printf("%s", cadena_unsigned);
		}else if (continuar == -1){
			return -1;
		}
		memset(cadena, '\0', LONG_CHAR);
	}
	return 0;
}

int main(int argc, char const *argv[]){
	socket_server_t socket_servidor;
	char cadena_recibida[LONG_CHAR+1];
	char clave[LONG_KEY];

	if(argc != CANT_ARG){
		return -1;
	}

	strncpy(clave, argv[3]+6, LONG_KEY);
	memset(cadena_recibida, '\0', LONG_CHAR+1);

	if(create_socket_server(&socket_servidor, argv[1]) == 0){
		if(bind_listen_socket_server(&socket_servidor, CANT_LISTEN) == 0){
			if(accept_socket_server(&socket_servidor) == 0){
				if(imprimir_mensaje(&socket_servidor, cadena_recibida, (char*) argv[2], clave) == 0){
					destroy_socket_server(&socket_servidor);
					return 0;
				}
			}
		}
	}

	return -1;
}