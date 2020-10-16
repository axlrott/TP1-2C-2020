#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "client_tda.h"
#include "common_encriptaciones.h"

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"
#define LONG_CHAR 64
#define LONG_KEY 15
#define CANT_ARG 6

int sendMsj(socket_client_t* skt, FILE* input, char* crip, char* key){
	unsigned char cadena[LONG_CHAR];
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	memset(cadena, '\0', LONG_CHAR);
	cesarCreate(&enc_cesar, key);
	vigenereCreate(&enc_vig, key);
	rc4Create(&enc_rc4, key);

	while(!feof(input)){
		int largo = fread(cadena, sizeof(char), LONG_CHAR, input);
		if (ferror(input)){
			return -1;
		}

		if(cadena[largo-1] == '\n'){
			largo--;
		}
		if(strcmp(crip, CESAR) == 0){
			cesarEncriptar(&enc_cesar, cadena, LONG_CHAR);
		}else if (strcmp(crip, VIGENERE) == 0){
			vigenereEncriptar(&enc_vig, cadena, LONG_CHAR);
		}else if (strcmp(crip, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena, LONG_CHAR);
		}
		SockClientSend(skt, (char*) cadena, largo);
		memset(cadena, '\0', LONG_CHAR);
	}
	cesarDestroy(&enc_cesar);
	vigenereDestroy(&enc_vig);
	rc4Destroy(&enc_rc4);
	return 0;
}

void liberarMemoriaInput(FILE* input){
	if (input != stdin){
		fclose(input);
	}
	fclose(stdin);
	fclose(stdout);
	fclose(stderr); 
}

int main(int argc, char const *argv[]){
	FILE* input = stdin;
	socket_client_t socket_cliente;
	char clave[LONG_KEY];
	int salida_main = -1;

	if(argc == CANT_ARG){
		input = fopen(argv[5], "r");
	}else if (argc < CANT_ARG-1){
		liberarMemoriaInput(input);
		return salida_main;
	}
	strncpy(clave, (argv[4]+6), LONG_KEY);

	if(SockClientCreate(&socket_cliente, (char*) argv[1], (char*) argv[2]) == 0){
		if(SockClientConnect(&socket_cliente) == 0){
			if(sendMsj(&socket_cliente, input, (char*) argv[3], clave) == 0){
				SockClientDestroy(&socket_cliente);
				salida_main = 0;
			}
		}
	}
	liberarMemoriaInput(input);
	return salida_main;
}
