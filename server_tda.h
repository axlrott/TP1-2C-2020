#ifndef SOCKET_SERVER_T
#define SOCKET_SERVER_T

typedef struct socket_server{
	int socket_main;
	int socket_servidor;
	struct addrinfo* direcciones;
}socket_server_t;

int socketServerCreate(socket_server_t* self, char* service);

int socketServerBindListen(socket_server_t* self, int cantidad);

int socketServerAccept(socket_server_t* self);

int socketServerRecv(socket_server_t* self, char* recibidor, int largo);

void socketServerDestroy(socket_server_t* self);

#endif
