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

int SockClientCreate(socket_client_t* self, char* host, char* service){
	if (initAddress(self, host, service) == -1){
		freeaddrinfo(self->direcciones);
		return -1;
	}

	struct addrinfo* dir = self->direcciones;
	self->socket_main = socket(dir->ai_family, dir->ai_socktype, dir->ai_protocol);

	if (self->socket_main == -1){
		freeaddrinfo(self->direcciones);
		return -1;
	}

	return 0;
}

int SockClientConnect(socket_client_t* self){
	struct addrinfo* dir = self->direcciones;

	if (connect(self->socket_main, dir->ai_addr, dir->ai_addrlen) != 0){
		SockClientDestroy(self);
		return -1;
	}
	
	return 0;
}

int SockClientSend(socket_client_t* self, char* envio, int largo){
	int enviado = 0;

	while(largo > enviado){
		int tam = largo - enviado;
		int tmp = send(self->socket_main, (envio + enviado), tam, MSG_NOSIGNAL);
		enviado += tmp;

		if(tmp == -1){
			SockClientDestroy(self);
			return -1;
		}else if (tmp == 0){
			return 0;
		}
	}
	return 1;
}

void SockClientDestroy(socket_client_t* self){
	freeaddrinfo(self->direcciones);
	shutdown(self->socket_main, SHUT_RDWR);
	close(self->socket_main);
}
