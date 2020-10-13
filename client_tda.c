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
	int resultado;

	resultado = init_socket_client_address(self, host, service);

	return resultado;
}

int connect_socket_client(socket_client_t* self){
	int resultado;
	bool conectado = false;
	struct addrinfo* ptr;

	for (ptr = self->direcciones; ptr != NULL && conectado == false; ptr = ptr->ai_next){
		self->socket_main = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (self->socket_main == -1){
			printf("Error: %s\n", strerror(errno));
		}else{
			resultado = connect(self->socket_main, ptr->ai_addr, ptr->ai_addrlen);

			if(resultado == -1){
				close_socket_client(self);
				printf("Error: %s\n", strerror(errno));
			}

			conectado = (resultado != -1);
		}
	}

	freeaddrinfo(self->direcciones);
	return conectado;
}

int send_socket_client(socket_client_t* self, char* envio, int largo){
	int cant_send = 0;
	int tmp;

	while(largo > cant_send){
		envio += cant_send;
		tmp = send(self->socket_main, envio, (largo - cant_send), MSG_NOSIGNAL);
		cant_send += tmp;

		if(tmp == -1){
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

int recv_socket_client(socket_client_t* self, char* recibidor, int largo){
	int cant_recv = 0;
	int tmp;

	while(largo > cant_recv){
		recibidor += cant_recv;
		tmp = recv(self->socket_main, recibidor, (largo - cant_recv), 0);
		cant_recv += tmp;

		if(tmp == -1){
			return -1;
		}else if(tmp == 0){
			return 0;
		}
	}
	return 1;
}

void shutdown_socket_client(socket_client_t* self){
	shutdown(self->socket_main, SHUT_RDWR);
}

void close_socket_client(socket_client_t* self){
	close(self->socket_main);
}
