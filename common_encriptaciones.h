#ifndef ENCRIPTACIONES_T
#define ENCRIPTACIONES_T

typedef struct cesar{
	int key;
}cesar_t;

typedef struct vigenere{
	char* key;
	int pos;
}vigenere_t;

typedef struct rc4{
	char* key;
	unsigned char array[256];
	int posA;
	int posB;
}rc4_t;

void cesarCreate(cesar_t* self, char* key);
void cesarEncriptar(cesar_t* self, unsigned char* cadena, int largo);
void cesarDesencriptar(cesar_t* self, unsigned char* cadena, int largo);
void cesarDestroy(cesar_t* self);

void vigenereCreate(vigenere_t* self, char* key);
void vigenereEncriptar(vigenere_t* self, unsigned char* cadena, int largo);
void vigenereDesencriptar(vigenere_t* self, unsigned char* cadena, int largo);
void vigenereDestroy(vigenere_t* self);

void rc4Create(rc4_t* self, char* key);
void rc4Encriptar(rc4_t* self, unsigned char* cadena, int largo);
void rc4Destroy(rc4_t* self);

#endif
