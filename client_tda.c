#define _POSIX_C_SOURCE 200112L

#include "client_tda.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int initAddress(socket_client_t* self, char* host, char* service){
	int resultado;
	struct addrinfo dir_host;

	memset(&dir_host, 0, sizeof(struct addrinfo));
	dir_host.ai_family = AF_INET;
	dir_host.ai_socktype = SOCK_STREAM;
	dir_host.ai_flags = 0;

	resultado = getaddrinfo(host, service, &dir_host, &(self->direcciones));

	return resultado;
}

int socketClientCreate(socket_client_t* self, char* host, char* service){
	if (initAddress(self, host, service) == -1){
		freeaddrinfo(self->direcciones);
		return -1;
	}
	return 0;
}

int socketClientConnect(socket_client_t* self){
	bool exito = false;
	struct addrinfo* ptr = self->direcciones;

	while(ptr != NULL && !exito){
		int dominio = ptr->ai_family;
		int tipo = ptr->ai_socktype;
		int protocolo = ptr->ai_protocol;

		int create = socketCreate(&(self->socket_main), dominio, tipo, protocolo);
		if (create != -1){
			void* dir = ptr->ai_addr;
			int dir_long = ptr->ai_addrlen;
			int conecto = socketConnect(&(self->socket_main), dir, dir_long);
			if(conecto == -1){
				socketClose(&(self->socket_main));
				ptr = ptr->ai_next;
			}
			exito = (conecto != -1);
		}else{
			ptr = ptr->ai_next;
		}
	}
	if(!exito){
		freeaddrinfo(self->direcciones);
		return -1;
	}
	self->direcciones = ptr;
	return 0;
}

int socketClientSend(socket_client_t* self, char* envio, int largo){
	int res = socketSend(&(self->socket_main), envio, largo);
	if(res == -1){
		socketClientDestroy(self);
		return -1;
	}
	return res;
}

void socketClientDestroy(socket_client_t* self){
	socketShutdown(&(self->socket_main), SHUT_RDWR);
	socketClose(&(self->socket_main));
	freeaddrinfo(self->direcciones);
}
