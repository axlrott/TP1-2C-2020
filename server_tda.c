#define _POSIX_C_SOURCE 200112L

#include "server_tda.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int init_socket_server_address(socket_server_t* self, const char* service){
	int resultado;
	struct addrinfo direccion_host;

	memset(&direccion_host, 0, sizeof(struct addrinfo));
	direccion_host.ai_family = AF_INET;
	direccion_host.ai_socktype = SOCK_STREAM;
	direccion_host.ai_flags = AI_PASSIVE;

	resultado = getaddrinfo(NULL, service, &direccion_host, &(self->direcciones));

	return resultado;
}

int create_socket_server(socket_server_t* self, const char* service){
	int val = 1;
	self->socket_servidor = -1;

	if( init_socket_server_address(self, service) != 0 ){
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

int bind_listen_socket_server(socket_server_t* self, int cantidad){
	struct addrinfo* dir = self->direcciones;

	if (bind(self->socket_main, dir->ai_addr, dir->ai_addrlen) != 0){
		destroy_socket_server(self);
		return -1;
	}

	if (listen(self->socket_main, cantidad) != 0){
		destroy_socket_server(self);
		return -1;
	}

	return 0;
}

int accept_socket_server(socket_server_t* self){
	struct addrinfo* dir = self->direcciones;

	self->socket_servidor = accept(self->socket_main, dir->ai_addr, &(dir->ai_addrlen));

	if (self->socket_servidor == -1){
		destroy_socket_server(self);
		return -1;
	}
	return 0;
}

int recv_socket_server(socket_server_t* self, char* recibidor, int largo){
	int cant_recv = 0;

	while(largo > cant_recv){
		recibidor += cant_recv;
		int tmp = recv(self->socket_servidor, recibidor, (largo - cant_recv), 0);
		cant_recv += tmp;

		if(tmp == -1){
			destroy_socket_server(self);
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

void destroy_socket_server(socket_server_t* self){
	if (self->socket_servidor != -1){
		shutdown(self->socket_servidor, SHUT_RDWR);
		close(self->socket_servidor);
	}
	shutdown(self->socket_main, SHUT_RDWR);
	freeaddrinfo(self->direcciones);
	close(self->socket_main);
}
