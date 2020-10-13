#ifndef SOCKET_SERVER_T
#define SOCKET_SERVER_T

typedef struct socket_server{
	int socket_main;
	int socket_servidor;
	struct addrinfo* direcciones;
	
}socket_server_t;

int create_socket_server(socket_server_t* self, const char* service);

int bind_socket_server(socket_server_t* self);

int listen_socket_server(socket_server_t* self, int cantidad);

int accept_socket_server(socket_server_t* self);

int send_socket_server(socket_server_t* self, char* envio, int largo);

int recv_socket_server(socket_server_t* self, char* recibidor, int largo);

void shutdown_socket_server(socket_server_t* self);

void close_socket_server(socket_server_t* self);

#endif