#ifndef VIGENERE_T
#define VIGENERE_T

typedef struct vigenere{
	char* key;
	int pos;
}vigenere_t;

void vigenereCreate(vigenere_t* self, char* key);
void vigenereEncriptar(vigenere_t* self, unsigned char* cadena, int largo);
void vigenereDesencriptar(vigenere_t* self, unsigned char* cadena, int largo);
void vigenereDestroy(vigenere_t* self);

#endif
