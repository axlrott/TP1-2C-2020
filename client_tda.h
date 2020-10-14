#ifndef SOCKET_CLIENT_T
#define SOCKET_CLIENT_T

typedef struct socket_client{

	int socket_main;
	struct addrinfo* direcciones;

}socket_client_t;

int create_socket_client(socket_client_t* self, const char* hostname, const char* servicename);

int connect_socket_client(socket_client_t* self);

int send_socket_client(socket_client_t* self, char* envio, int largo);

int recv_socket_client(socket_client_t* self, char* recibidor, int largo);

void destroy_socket_client(socket_client_t* self);

#endif