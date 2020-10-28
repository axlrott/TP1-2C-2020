#ifndef SERVER_CRIPTO_T
#define SERVER_CRIPTO_T

#include "common_socket.h"
#include "server_tda.h"
#include <stdio.h>

typedef struct client_cripto{
	socket_server_t servidor;
	char* cripto;
	char* clave;
}svCript_t;

void criptSvCreate(svCript_t* self, char* cripto, char* clave);

int criptSvSocketInit(svCript_t* self, char* port, int cant_listen);

int criptSvRecvMsj(svCript_t* self, char* cadena, int largo);

void criptSvDestroy(svCript_t* self);

#endif
