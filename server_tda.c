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
	int val = 1;
	self->socket_servidor = -1;

	if(initAddress(self, service) != 0){
		return -1;
	}

	struct addrinfo* dir = self->direcciones;
	self->socket_main = socket(dir->ai_family, dir->ai_socktype, dir->ai_protocol);
	setsockopt(self->socket_main, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	if (self->socket_main == -1){
		freeaddrinfo(self->direcciones);
		return -1;
	}
	return 0;
}

int socketServerBindListen(socket_server_t* self, int cantidad){
	struct addrinfo* dir = self->direcciones;

	if (bind(self->socket_main, dir->ai_addr, dir->ai_addrlen) != 0){
		socketServerDestroy(self);
		return -1;
	}

	if (listen(self->socket_main, cantidad) != 0){
		socketServerDestroy(self);
		return -1;
	}

	return 0;
}

int socketServerAccept(socket_server_t* self){
	struct addrinfo* dir = self->direcciones;
	int skt_main = self->socket_main;

	self->socket_servidor = accept(skt_main, dir->ai_addr, &(dir->ai_addrlen));

	if (self->socket_servidor == -1){
		socketServerDestroy(self);
		return -1;
	}
	return 0;
}

int socketServerRecv(socket_server_t* self, char* cadena, int largo){
	int cant_recv = 0;

	while(largo > cant_recv){
		int larg_rec = largo - cant_recv;
		int tmp = recv(self->socket_servidor, (cadena + cant_recv), larg_rec, 0);
		cant_recv += tmp;

		if(tmp == -1){
			socketServerDestroy(self);
			return -1;
		}else if (tmp == 0){
			return cant_recv;
		}
	}
	return cant_recv;
}

void socketServerDestroy(socket_server_t* self){
	if (self->socket_servidor != -1){
		shutdown(self->socket_servidor, SHUT_RDWR);
		close(self->socket_servidor);
	}
	shutdown(self->socket_main, SHUT_RDWR);
	freeaddrinfo(self->direcciones);
	close(self->socket_main);
}
