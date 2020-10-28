#ifndef SOCKET_SERVER_T
#define SOCKET_SERVER_T

#include "common_socket.h"

typedef struct server{
	socket_t socket_main;
	socket_t socket_servidor;
	struct addrinfo* direcciones;
}socket_server_t;

int socketServerCreate(socket_server_t* self, char* service);

int socketServerBindListen(socket_server_t* self, int cantidad);

int socketServerAccept(socket_server_t* self);

int socketServerRecv(socket_server_t* self, char* recibidor, int largo);

void socketServerDestroy(socket_server_t* self);

#endif
