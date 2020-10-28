#define _POSIX_C_SOURCE 200112L

#include "common_socket.h"
#include <stdio.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int socketCreate(socket_t* self, int dominio, int tipo, int protocolo){
	int val = 1;

	self->fd = socket(dominio, tipo, protocolo);
	if (self->fd == -1){
		return -1;
	}
	setsockopt(self->fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
	return 0;
}

int socketBind(socket_t* self, void* dir, int dir_largo){
	if (bind(self->fd, dir, dir_largo) != 0){
		return -1;
	}
	return 0;
}

int socketListen(socket_t* self, int cantidad){
	if (listen(self->fd, cantidad) != 0){
		return -1;
	}
	return 0;
}

int socketAccept(socket_t* self, void* dir, void* dir_largo){
	int skt_main = self->fd;
	int fd_server = accept(skt_main, dir, dir_largo);
	return fd_server;
}

int socketConnect(socket_t* self, void* dir, int dir_largo){
	if (connect(self->fd, dir, dir_largo) != 0){
		return -1;
	}
	return 0;
}

int socketSend(socket_t* self, char* envio, int largo){
	int enviado = 0;

	while(largo > enviado){
		int tam = largo - enviado;
		int tmp = send(self->fd, (envio + enviado), tam, MSG_NOSIGNAL);
		enviado += tmp;

		if(tmp == -1){
			return -1;
		}else if (tmp == 0){
			return 0;
		}
	}
	return 1;
}

int socketRecv(socket_t* self, char* recibido, int largo){
	int cant_recv = 0;

	while(largo > cant_recv){
		int larg_rec = largo - cant_recv;
		int tmp = recv(self->fd, (recibido + cant_recv), larg_rec, 0);
		cant_recv += tmp;

		if(tmp == -1){
			return -1;
		}else if (tmp == 0){
			return cant_recv;
		}
	}
	return cant_recv;
}

void socketShutdown(socket_t* self, int flag){
	shutdown(self->fd, flag);
}

void socketClose(socket_t* self){
	close(self->fd);
}
