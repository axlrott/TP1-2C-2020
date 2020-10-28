#define _POSIX_C_SOURCE 200112L

#include "server_cripto.h"
#include "common_socket.h"
#include "server_tda.h"
#include "common_cesar.h"
#include "common_vigenere.h"
#include "common_rc4.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define CESAR "--method=cesar"
#define VIGENERE "--method=vigenere"
#define RC4 "--method=rc4"

void criptSvCreate(svCript_t* self, char* cripto, char* clave){
	self->cripto = cripto;
	self->clave = clave;
}

int criptSvSocketInit(svCript_t* self, char* port, int cant_listen){
	if(socketServerCreate(&(self->servidor), port) == 0){
		if(socketServerBindListen(&(self->servidor), cant_listen) == 0){
				if(socketServerAccept(&(self->servidor)) == 0){
					return 0;
				}
		}
	}
	return -1;
}

int criptSvRecvMsj(svCript_t* self, char* cadena, int largo){
	int largo_rec = 1;
	cesar_t enc_cesar;
	vigenere_t enc_vig;
	rc4_t enc_rc4;

	cesarCreate(&enc_cesar, self->clave);
	vigenereCreate(&enc_vig, self->clave);
	rc4Create(&enc_rc4, self->clave);

	while(largo_rec > 0){
		largo_rec = socketServerRecv(&(self->servidor), cadena, largo);
		if(largo_rec <= 0){
			break;
		}
		unsigned char* cadena_unsigned = (unsigned char*) cadena;
		if(strcmp(self->cripto, CESAR) == 0){
			cesarDesencriptar(&enc_cesar, cadena_unsigned, largo_rec);
		}else if (strcmp(self->cripto, VIGENERE) == 0){
			vigenereDesencriptar(&enc_vig, cadena_unsigned, largo_rec);
		}else if (strcmp(self->cripto, RC4) == 0){
			rc4Encriptar(&enc_rc4, cadena_unsigned, largo_rec);
		}
		printf("%s", cadena_unsigned);
		memset(cadena, '\0', largo);
	}
	cesarDestroy(&enc_cesar);
	vigenereDestroy(&enc_vig);
	rc4Destroy(&enc_rc4);
	return largo_rec;
}

void criptSvDestroy(svCript_t* self){
	socketServerDestroy(&(self->servidor));
}
