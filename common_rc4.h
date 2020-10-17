#ifndef RC4_T
#define RC4_T
#define CANT_CHAR 256

typedef struct rc4{
	char* key;
	unsigned char array[CANT_CHAR];
	int posA;
	int posB;
}rc4_t;

void rc4Create(rc4_t* self, char* key);
void rc4Encriptar(rc4_t* self, unsigned char* cadena, int largo);
void rc4Destroy(rc4_t* self);

#endif
