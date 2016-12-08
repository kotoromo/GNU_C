/**
	INFORMACIÓN PRELIMINAR: (Obtenida del manual que nos brinda Linux)
	
	La función "open()" crea y retorna un nuevo descriptor de archivo llamado por el "filename". Inicialmente,
	el indicador de posición para el fichero se encuentra en el inicio. El argumento "mode" se utiliza sólo cuando el fichero es
	creado, pero es buena práctica incluirlo siempre. Esta función realiza una llamada al SISTEMA OPERATIVO.

	El argumento "flags" controla cómo el fichero debe ser abierto.

	El valor normal de retorno "value" de la función "open" es un descriptor de archivo entero positivo. Si sucede algún error,
	la función devuelve -1.
	
	FIRMA: 
	* int open(const char *path, int oflags);
	* int open(const char *path, int oflags, mode_t mode);
	
	------------------------------------------------------------------------------------------------------------------------------
	
	La función "creat()" es equivalente a la sentencia "open (filename, O_WRONLY | O_CREAT | O_TRUNC, mode)"
	Esta función se encuentra obsoleta 
	
	------------------------------------------------------------------------------------------------------------------------------
	
	La función "close()" cierra el descriptor de archivo "filedes". Al cerrar un archivo, sucede lo siguiente:
	* Desasigna el descriptor de archivo.
	* Cualquier seguro de escritura se quita.
	* Cuando todos los descriptores de archivos asociados con un pipe o con una estructura FIFO han sido cerrados,
	  cualquier dato no leído es descartado
	
	Esta función es un punto de cancelación en programas multi-hilo. Si el hilo en el que se encontraba en uso el descriptor de archivo
	es cerrado, los recursos del descriptor de archivo siguen abiertos hasta que la ejecución del programa termine.
	
	
	------------------------------------------------------------------------------------------------------------------------------
	
	
	La función "write()" es una llamada al sistema que se utiliza para escribir información a un descriptor de archivo.
	

	FIRMA: size_t write(int fildes, const void *buf, size_t nbytes);

	donde: 
	* filedes es el descriptor de archivo
	* *buf Apuntador con el contenido a escribir sobre el descriptor de archivo
	* nbytes es el tamaño en bites de la información que se va a escribir.
	 
	------------------------------------------------------------------------------------------------------------------------------
	PROTOCOLO A SEGUIR CUANDO SE ABREN ARCHIVOS:
	* Abrir el archivo
	* Verificar si el archivo ha sido abierto correctamente
	* Operar con el archivo
	* Cerrar el flujo
	 
	------------------------------------------------------------------------------------------------------------------------------
	
	Datos del descriptor de archivo:
	* Dentro del header unistd se encuentra declarada la siguiente estructura:
	
	struct stat {
		dev_t     st_dev;      ID of device containing file 
		ino_t     st_ino;      inode number 
		mode_t    st_mode;     protection 
		nlink_t   st_nlink;    number of hard links 
		uid_t     st_uid;      user ID of owner 
		gid_t     st_gid;      group ID of owner 
		dev_t     st_rdev;     device ID (if special file) 
		off_t     st_size;     total size, in bytes 
		blksize_t st_blksize;  blocksize for file system I/O 
		blkcnt_t  st_blocks;   number of 512B blocks allocated 
		time_t    st_atime;    time of last access 
		time_t    st_mtime;    time of last modification 
		time_t    st_ctime;    time of last status change 
	};
	
	Para acceder a toda esta información necesitamos hacer uso de la función fstat() con la firma:
								int fstat(int fd, struct stat *buf);
	
	Al declarar un apuntador a struct stat, en este se quedará "almacenada" la información del descriptor de archivo.
	

*/

/** PROGRAMA EJEMPLO:
 * Programa que imita la función del comando cp de linux
 */

#include <sys/types.h>

#include <sys/stat.h>													// Las cabeceras sys/stat.h y sys/types.h son necesarias para algunas distribuciones de GNU/Linux
#include <stdio.h>
#include <stdint.h>
#include <unistd.h> 													// En este se encuentra la declaración de las funciones close(), write() y la estructura struct stat asi como la función fstat()
#include <fcntl.h>														// En este se encuentra la declaración de la función open()
#include <stdlib.h>

int32_t main(int32_t argc, char** argv){								// El programa toma como argumentos los archivos a copiar
	
	const char* archivo_from = argv[1];									
	const char* archivo_to = argv[2];
	
	int32_t desc_arch_from = open(archivo_from, O_RDONLY);
	
	int32_t desc_arch_to = open(archivo_to, O_RDWR | O_CREAT);
	
	if (argc <= 1){						
		printf("\nNo se especificaron archivos.\n");
		printf("\nEl programa terminará su ejecución.\n");
		
		return 1;
	}
	
	if ( (desc_arch_to < 0) || (desc_arch_from < 0) ){					// Verificamos que los descriptores de archivo se han abierto de manera satisfactoria
		const char* mensaje = 
		"El descriptor de archivo no se pudo abrir.";

		printf(mensaje);
		return 1;
	}
	
	struct stat stat_buff;												//Declaramos nuestro apuntador a struct stat.
	char* contenido_archivo = NULL;										// Declaramos nuestro buffer del archivo.
	
	fstat(desc_arch_from, &stat_buff);									//Obtenemos la información.
	contenido_archivo = (char*) malloc(sizeof(char)*stat_buff.st_size);
	
	read(desc_arch_from, contenido_archivo, stat_buff.st_size);			// Leemos la información contenida en el descriptor de archivo y la almacenamos en nuestro buffer.
	write(desc_arch_to, contenido_archivo, stat_buff.st_size);			// Va a escribir st_size bytes (contenido de archivo)
		
	close(desc_arch_from);												//Cerramos los flujos.
	close(desc_arch_to);
	free(contenido_archivo);											//Liberamos el espacio reservado para el contenido.
	
	return 0;
}

/**
 * Para información adicional, consultar http://codewiki.wikidot.com/system-calls
 **/

