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

int imprimirMsj(socket_server_t* skt, char* cadena, char* cripto, char* key){
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	cesarCreate(&enc_cesar, key);
	vigenereCreate(&enc_vig, key);
	rc4Create(&enc_rc4, key);

	int continuar = socketServerRecv(skt, cadena, LONG_CHAR);
	while(continuar == 1){
		if (continuar == -1){
			return -1;
		}
		unsigned char* cadena_unsigned = (unsigned char*) cadena;

		if(strcmp(cripto, CESAR) == 0){
			cesarDesencriptar(&enc_cesar, cadena_unsigned, LONG_CHAR);
		}else if (strcmp(cripto, VIGENERE) == 0){
			vigenereDesencriptar(&enc_vig, cadena_unsigned, LONG_CHAR);
		}else if (strcmp(cripto, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena_unsigned, LONG_CHAR);
		}

		printf("%s", cadena_unsigned);
		memset(cadena, '\0', LONG_CHAR);
		continuar = socketServerRecv(skt, cadena, LONG_CHAR);
	}
	cesarDestroy(&enc_cesar);
	vigenereDestroy(&enc_vig);
	rc4Destroy(&enc_rc4);
	return 0;
}

int main(int argc, char const *argv[]){
	socket_server_t socket_serv;
	char cadena_recv[LONG_CHAR+1];
	char clave[LONG_KEY];

	if(argc != CANT_ARG){
		return -1;
	}

	strncpy(clave, argv[3]+6, LONG_KEY);
	memset(cadena_recv, '\0', LONG_CHAR+1);

	if(socketServerCreate(&socket_serv, (char*) argv[1]) == 0){
		if(socketServerBindListen(&socket_serv, CANT_LISTEN) == 0){
			if(socketServerAccept(&socket_serv) == 0){
				if(imprimirMsj(&socket_serv, cadena_recv, (char*) argv[2], clave) == 0){
					socketServerDestroy(&socket_serv);
					return 0;
				}
			}
		}
	}

	return -1;
}
