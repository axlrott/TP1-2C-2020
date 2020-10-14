#define _POSIX_C_SOURCE 200112L

#include "client_tda.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int init_socket_client_address(socket_client_t* self, const char* host, const char* service){
	int resultado;
	struct addrinfo direccion_host;

	memset(&direccion_host, 0, sizeof(struct addrinfo));
	direccion_host.ai_family = AF_INET;
	direccion_host.ai_socktype = SOCK_STREAM;
	direccion_host.ai_flags = 0;

	resultado = getaddrinfo(host, service, &direccion_host, &(self->direcciones));

	return resultado;
}

int create_socket_client(socket_client_t* self, const char* host, const char* service){
	if ( init_socket_client_address(self, host, service) == -1 ){
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

int connect_socket_client(socket_client_t* self){
	struct addrinfo* dir = self->direcciones;

	if ( connect(self->socket_main, dir->ai_addr, dir->ai_addrlen) != 0 ){
		destroy_socket_client(self);
		return -1;
	}
	
	return 0;
}

int send_socket_client(socket_client_t* self, char* envio, int largo){
	int cant_send = 0;

	while(largo > cant_send){
		envio += cant_send;
		int tmp = send(self->socket_main, envio, (largo - cant_send), MSG_NOSIGNAL);
		cant_send += tmp;

		if(tmp == -1){
			destroy_socket_client(self);
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

void destroy_socket_client(socket_client_t* self){
	freeaddrinfo(self->direcciones);
	shutdown(self->socket_main, SHUT_RDWR);
	close(self->socket_main);
}
