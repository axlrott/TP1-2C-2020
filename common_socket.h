#ifndef SOCKET_T
#define SOCKET_T

#include <netdb.h>

typedef struct socketClass{
	int fd;
}socket_t;

int socketCreate(socket_t* self, int dominio, int tipo, int protocolo);

int socketBind(socket_t* self, void* dir, int dir_largo);

int socketListen(socket_t* self, int cantidad);

int socketAccept(socket_t* self, void* dir, void* dir_largo);

int socketConnect(socket_t* self, void* dir, int dir_largo);

int socketSend(socket_t* self, char* envio, int largo);

int socketRecv(socket_t* self, char* recibidor, int largo);

void socketShutdown(socket_t* self, int flag);

void socketClose(socket_t* self);

#endif
