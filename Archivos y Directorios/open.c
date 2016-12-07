#include <stdio.h>
#include <fcntl.h> // En esta se encuentra la definición de las funciones open() y creat()
#include <unistd.h> // En esta se encuentra la definición de la función close()

/**
	INFORMACIÓN PRELIMINAR: (Obtenida del manual que nos brinda Linux)
	
	La función "open()" crea y retorna un nuevo descriptor de archivo llamado por el "filename". Inicialmente,
	el indicador de posición para el fichero se encuentra en el inicio. El argumento "mode" se utiliza sólo cuando el fichero es
	creado, pero es buena práctica incluirlo siempre.

	El argumento "flags" controla cómo el fichero debe ser abierto.

	El valor normal de retorno "value" de la función "open" es un descriptor de archivo entero positivo. Si sucede algún error,
	la función devuelve -1



*/