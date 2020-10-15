#ifndef SOCKET_CLIENT_T
#define SOCKET_CLIENT_T

typedef struct socket_client{
	int socket_main;
	struct addrinfo* direcciones;
}socket_client_t;

int SockClientCreate(socket_client_t* self, char* host, char* service);

int SockClientConnect(socket_client_t* self);

int SockClientSend(socket_client_t* self, char* envio, int largo);

void SockClientDestroy(socket_client_t* self);

#endif
