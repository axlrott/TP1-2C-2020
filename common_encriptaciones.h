#ifndef ENCRIPTACIONES_T
#define ENCRIPTACIONES_T

void encripto_cesar(unsigned char* cadena, char* key, int largo);
void desencripto_cesar(unsigned char* cadena, char* key, int largo);
void encripto_vigenere(unsigned char* cadena, char* key, int largo);
void desencripto_vigenere(unsigned char* cadena, char* key, int largo);
void encripto_rc4(unsigned char* cadena, char* key, int largo);

#endif