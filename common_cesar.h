#ifndef CESAR_T
#define CESAR_T

typedef struct cesar{
	int key;
}cesar_t;

void cesarCreate(cesar_t* self, char* key);
void cesarEncriptar(cesar_t* self, unsigned char* cadena, int largo);
void cesarDesencriptar(cesar_t* self, unsigned char* cadena, int largo);
void cesarDestroy(cesar_t* self);

#endif
