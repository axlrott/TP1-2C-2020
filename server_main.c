#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "server_tda.h"
#include "common_encriptaciones.h"

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"
#define LONG_CHAR 64
#define LONG_KEY 15
#define CANT_LISTEN 10
#define CANT_ARG 4

int imprimirMsj(socket_server_t* skt, char* cripto, char* key){
	int largo_rec = 1;
	char cadena[LONG_CHAR+1];
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	memset(cadena, '\0', LONG_CHAR+1);
	cesarCreate(&enc_cesar, key);
	vigenereCreate(&enc_vig, key);
	rc4Create(&enc_rc4, key);

	while(largo_rec > 0){
		largo_rec = socketServerRecv(skt, cadena, LONG_CHAR);

		if(largo_rec == 0){
			break;
		}

		unsigned char* cadena_unsigned = (unsigned char*) cadena;
		if(strcmp(cripto, CESAR) == 0){
			cesarDesencriptar(&enc_cesar, cadena_unsigned, largo_rec);
		}else if (strcmp(cripto, VIGENERE) == 0){
			vigenereDesencriptar(&enc_vig, cadena_unsigned, largo_rec);
		}else if (strcmp(cripto, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena_unsigned, largo_rec);
		}
		printf("%s", cadena_unsigned);
		memset(cadena, '\0', LONG_CHAR);
	}
	if (largo_rec == -1){
			return -1;
		}
	cesarDestroy(&enc_cesar);
	vigenereDestroy(&enc_vig);
	rc4Destroy(&enc_rc4);
	return 0;
}

void liberarMemoriaInput(){
	fclose(stdin);
	fclose(stdout);
	fclose(stderr); 
}

int main(int argc, char const *argv[]){
	socket_server_t socket_serv;
	char clave[LONG_KEY];
	int salida_main = -1;

	if(argc != CANT_ARG){
		liberarMemoriaInput();
		return salida_main;
	}

	strncpy(clave, argv[3]+6, LONG_KEY);

	if(socketServerCreate(&socket_serv, (char*) argv[1]) == 0){
		if(socketServerBindListen(&socket_serv, CANT_LISTEN) == 0){
			if(socketServerAccept(&socket_serv) == 0){
				if(imprimirMsj(&socket_serv, (char*) argv[2], clave) == 0){
					socketServerDestroy(&socket_serv);
					salida_main = 0;
				}
			}
		}
	}
	liberarMemoriaInput();
	return salida_main;
}
