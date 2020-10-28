#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"
#include "client_tda.h"
#include "client_cripto.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LONG_CHAR 64
#define CANT_ARG 5

void liberarMemoriaInput(FILE* input){
	fclose(stdin);
	fclose(stdout);
	fclose(stderr); 
}

int main(int argc, char const *argv[]){
	FILE* input = stdin;
	clCript_t enviador; 
	int res = -1;

	if(argc != CANT_ARG){
		liberarMemoriaInput(input);
		return res;
	}
	char* host = (char*) argv[1];
	char* port = (char*) argv[2];
	char* cripto = (char*) argv[3];
	char* clave = (char*) argv[4]+6;

	criptClCreate(&enviador, cripto, clave);
	res = criptClSocketInit(&enviador, host, port);
	if (res == -1){
		return res;
	}
	res = criptClEnviarMsj(&enviador, input, LONG_CHAR);
	if (res == -1){
		return res;
	}
	criptClDestroy(&enviador);
	liberarMemoriaInput(input);
	return 0;
}
