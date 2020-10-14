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

void encriptar_cadena(unsigned char* cadena, char* key, const char* method){
	if(strcmp(method, CESAR) == 0){
		encripto_cesar(cadena, key, LONG_CHAR);

	}else if(strcmp(method, VIGENERE) == 0){
		encripto_vigenere(cadena, key, LONG_CHAR);

	}else if(strcmp(method, RC4) == 0){
		encripto_rc4(cadena, key, LONG_CHAR);
	}
}

int enviar_mensaje(socket_client_t* socket, FILE* input, char* cadena, char* cripto, char* key){
	int continuar = LONG_CHAR;
	unsigned char* cadena_unsigned = (unsigned char*) cadena;

	while(continuar == LONG_CHAR){
		continuar = fread(cadena_unsigned, sizeof(char), LONG_CHAR, input);

		if (continuar == -1){
			return -1;
		}

		encriptar_cadena(cadena_unsigned, key, cripto);
		send_socket_client(socket, (char*) cadena_unsigned, LONG_CHAR);

		memset(cadena_unsigned, '\0', LONG_CHAR);
	}
	return 0;
}

void liberar_memoria_input(FILE* input){
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

	if(create_socket_client(&socket_cliente, argv[1], argv[2]) == 0){
		if(connect_socket_client(&socket_cliente) == 0){
			if(enviar_mensaje(&socket_cliente, input, cadena, (char*) argv[3], clave) == 0){
				destroy_socket_client(&socket_cliente);
				salida_main = 0;
			}
		}
	}

	liberar_memoria_input(input);
	return salida_main;
}