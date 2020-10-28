#define _POSIX_C_SOURCE 200112L

#include "server_tda.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int initAddress(socket_server_t* self, char* service){
	int resultado;
	struct addrinfo direccion_host;

	memset(&direccion_host, 0, sizeof(struct addrinfo));
	direccion_host.ai_family = AF_INET;
	direccion_host.ai_socktype = SOCK_STREAM;
	direccion_host.ai_flags = AI_PASSIVE;

	resultado = getaddrinfo(NULL, service, &direccion_host, &(self->direcciones));
	return resultado;
}

int socketServerCreate(socket_server_t* self, char* service){
	self->socket_servidor.fd = -1;
	int creado = -1;
	if(initAddress(self, service) != 0){
		freeaddrinfo(self->direcciones);
		return -1;
	}
	struct addrinfo* ptr = self->direcciones;

	while(ptr != NULL && creado == -1){
		int dominio = ptr->ai_family;
		int tipo = ptr->ai_socktype;
		int protocolo = ptr->ai_protocol;

		creado = socketCreate(&(self->socket_main), dominio,tipo, protocolo);
		if (creado == -1){
			ptr = ptr->ai_next;
		}
	}
	if (creado == -1){
		freeaddrinfo(self->direcciones);
		return -1;
	}
	self->direcciones = ptr;
	return 0;
}

int socketServerBindListen(socket_server_t* self, int cantidad){
	void* dir = self->direcciones->ai_addr;
	int dir_long = self->direcciones->ai_addrlen;

	if (socketBind(&(self->socket_main), dir, dir_long) == -1){
		socketServerDestroy(self);
		return -1;
	}

	if (socketListen(&(self->socket_main), cantidad)){
		socketServerDestroy(self);
		return -1;
	}
	return 0;
}

int socketServerAccept(socket_server_t* self){
	void* dir = self->direcciones->ai_addr;
	void* dir_long = &(self->direcciones->ai_addrlen);
	int fd_servidor = socketAccept(&(self->socket_main), dir, dir_long);

	if (fd_servidor == -1){
		socketServerDestroy(self);
		return -1;
	}
	self->socket_servidor.fd = fd_servidor;
	return 0;
}

int socketServerRecv(socket_server_t* self, char* cadena, int largo){
	int res = socketRecv(&(self->socket_servidor), cadena, largo);
	
	if (res == -1){
		socketServerDestroy(self);
		return -1;
	}
	return res;
}

void socketServerDestroy(socket_server_t* self){
	if (self->socket_servidor.fd != -1){
		socketShutdown(&(self->socket_servidor), SHUT_RDWR);
		socketClose(&(self->socket_servidor));
	}
	socketShutdown(&(self->socket_main), SHUT_RDWR);
	socketClose(&(self->socket_main));
	freeaddrinfo(self->direcciones);
}
