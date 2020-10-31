#define _POSIX_C_SOURCE 200112L

#include "server_cripto.h"
#include "server_tda.h"
#include "common_socket.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LONG_CHAR 64
#define CANT_LISTEN 10
#define CANT_ARG 4

void liberarMemoriaInput(){
	fclose(stdin);
	fclose(stdout);
	fclose(stderr); 
}

int main(int argc, char const *argv[]){
	svCript_t recibidor;
	int res = -1;
	char cadena_recv[LONG_CHAR+1];
	memset(cadena_recv, '\0', LONG_CHAR+1);

	if(argc != CANT_ARG){
		liberarMemoriaInput();
		return res;
	}
	char* port = (char*) argv[1];
	char* cripto = (char*) argv[2];
	char* clave = (char*) argv[3]+6;

	criptSvCreate(&recibidor, cripto, clave);
	if (criptSvSocketInit(&recibidor, port, CANT_LISTEN)){
		if (criptSvRecvMsj(&recibidor, cadena_recv, LONG_CHAR)){
			criptSvDestroy(&recibidor);
			res = 0;
		}
	}
	liberarMemoriaInput();
	return res;
}
