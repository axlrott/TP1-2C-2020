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
	int resultado;
	int val = 1;

	resultado = init_socket_server_address(self, service);
	if(resultado == -1){
		return resultado;
	}

	struct addrinfo* dir = self->direcciones;
	self->socket_main = socket(dir->ai_family, dir->ai_socktype, dir->ai_protocol);
	setsockopt(self->socket_main, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	if (self->socket_main == -1){
		printf("Error: %s\n", strerror(errno));
		return -1;
	}
	return 0;
}

int bind_socket_server(socket_server_t* self){
	int resultado;
	struct addrinfo* dir = self->direcciones;

	resultado = bind(self->socket_main, dir->ai_addr, dir->ai_addrlen);

	return resultado;

}

int listen_socket_server(socket_server_t* self, int cantidad){
	int resultado;

	resultado = listen(self->socket_main, cantidad);

	return resultado;
}

int accept_socket_server(socket_server_t* self){
	struct addrinfo* dir = self->direcciones;

	self->socket_servidor = accept(self->socket_main, dir->ai_addr, &(dir->ai_addrlen));

	if (self->socket_servidor < 0){
		return -1;
	}
	return 0;
}

int send_socket_server(socket_server_t* self, char* envio, int largo){
	int cant_send = 0;
	int tmp;

	while(largo > cant_send){
		envio += cant_send;
		tmp = send(self->socket_servidor, envio, (largo - cant_send), MSG_NOSIGNAL);
		cant_send += tmp;

		if(tmp == -1){
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

int recv_socket_server(socket_server_t* self, char* recibidor, int largo){
	int cant_recv = 0;
	int tmp;

	while(largo > cant_recv){
		recibidor += cant_recv;
		tmp = recv(self->socket_servidor, recibidor, (largo - cant_recv), 0);
		cant_recv += tmp;

		if(tmp == -1){
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

void shutdown_socket_server(socket_server_t* self){
	shutdown(self->socket_servidor, SHUT_RDWR);
	shutdown(self->socket_main, SHUT_RDWR);

}

void close_socket_server(socket_server_t* self){
	freeaddrinfo(self->direcciones);
	close(self->socket_servidor);
	close(self->socket_main);

}
