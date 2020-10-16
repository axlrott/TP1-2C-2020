# TP1

## Nombre y Apellido: Axel Aparicio Rotermund
## Padron: 96283
## Link Github: https://github.com/axlrott/TP1-2C-2020.git

### Introduccion:

En este trabajo practico se realizaron dos programas, uno en el cual se encripta un mensaje enviado por entrada estandar y se lo envia por un socket cliente y otro programa en el cual se lo recibira mediante un socket servidor, se desencriptara el mensaje y luego se lo mostrara por pantalla.

### Encriptaciones:

Las encriptaciones utilizadas en los programas seran Cesar, Vigenere y RC4.
Cada una de estas encriptaciones van a ser estructuras, las cuales van a recibir sus respectivas claves y encriptaran/desencriptaran en base a eso.

#### Cesar:

La encriptacion de cesar va a recibir una clave al ser creada, la misma va a ser una cadena de caracteres pero debe representar un numero.
Al encriptar se recibira una cadena de caracteres y el largo de la misma y a cada caracter de esa cadena se le sumara el numero de la clave. En el caso de desencriptar se hara lo mismo pero en vez de sumar la clave se la restara.

#### Vigenere:

La encriptacion de Vigenere recibe una clave que va a representar una palabra y se inicializa la posicion de la clave en 0.
Al encriptar se recibe una cadena de caracteres y el largo, se encripta sumando cada caracter con el respectivo caracter de la clave, cuando la clave llega a la posicion final se vuelve a cero y se continua sumando. Al desencriptar es lo mismo solo que restando caracter con caracter de la clave.

#### RC4:

La encriptacion RC4 recibe una clave que representa una palabra y al inicializarse ya crea un array haciendo KDA. Al encriptar utiliza PRGA para tomar una clave de ese array creado y hacer un XOR con cada caracter de la cadena a encriptar. El desencriptar una cadena es hacer lo mismo que encriptarla.

### Socket Cliente:

El socket Cliente se va a crear pasandole por parametro el host y el puerto a utilizar.
Todas las funciones del socket cliente van a devolver 0 en caso de exito y devolveran -1 en caso de falla, tambien en caso de que haya alguna falla el socket hara un Destroy internamente y se cerrara.
La funcion send recibira una cadena de caracteres y un largo, y se enviara ese largo de la cadena de caracteres, en caso de que al enviarse se mandace menos del largo se volvera a mandar lo que resta de la cadena hasta cumplir con que se haya enviado el largo pasado por parametro.

### Socket Servidor:

El socket servidor se creara pasandole un puerto a utilizar.
Todas las funciones a excepcion del recv devolveran 0 en caso exitoso o -1 en caso de que haya alguna falla y al igual que en el socket cliente si se detecta una falla el socket hara un Destroy internamente y se cerrara.
El recv va a recibir de un socket cliente y guardar lo que reciba en la cadena de caracteres pasada por paramentro hasta que se alcanze el largo especificado que se pase por parametro o hasta que el socket cliente se haya cerrado.

### Cliente Main:

### Servidor Main:


