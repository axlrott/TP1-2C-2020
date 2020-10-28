#ifndef SOCKET_CLIENT_T
#define SOCKET_CLIENT_T

#include "common_socket.h"

typedef struct client{
	socket_t socket_main;
	struct addrinfo* direcciones;
}socket_client_t;

int socketClientCreate(socket_client_t* self, char* host, char* service);

int socketClientConnect(socket_client_t* self);

int socketClientSend(socket_client_t* self, char* envio, int largo);

void socketClientDestroy(socket_client_t* self);

#endif
