#ifndef CLIENT_CRIPTO_T
#define CLIENT_CRIPTO_T

#include "common_socket.h"
#include "client_tda.h"
#include <stdio.h>

typedef struct client_cripto{
	socket_client_t cliente;
	char* cripto;
	char* clave;
}clCript_t;

void criptClCreate(clCript_t* self, char* cripto, char* clave);

int criptClSocketInit(clCript_t* self, char* host, char* port);

int criptClEnviarMsj(clCript_t* self, FILE* input, int cant);

void criptClDestroy(clCript_t* self);

#endif
