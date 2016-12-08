/** 
 * Manejo de Directorios utilizando el estándar POSIX y la estructura DIRENT (dirent.h)
 
 * struct dirent {
    ino_t          d_ino;        inode number 
    off_t          d_off;        offset to the next dirent 
    unsigned short d_reclen;     length of this record 
    unsigned char  d_type;       type of file; not supported
                                   by all file system types 
    char           d_name[256];  filename 
	};
 	
 	Esta estructura es la que describe a los directorios en el estándar POSIX.

 	Para poder operar con directorios, hacemos uso de diversas llamadas al SO.
 				
 	int mkdir(const char *pathname, mode_t mode); 
 	- Nos permite crear directorios. El modo especifica los permisos de uso.

	DIR *opendir(const char *name);
	- Abre el flujo de directorio correspondiente al nombre del directorio especificado y nos regresa un puntero a este.
	El flujo se posiciona en la primera entrada del directorio.

	struct dirent *readdir(DIR *dirp);
	- Nos permite leer el flujo de directorio abierto previamente con la función opendir(const char *name).
	Esta función retorna un puntero a una estructura DIRENT que representa a la siguiente entrada en el flujo apuntado por dirp.
	Retorna NULL al llegar al final del flujo o al ocurrir un error.

	int rmdir(const char *pathname);
	- rmdir() remueve el directorio representado por el "pathname" si está vacío. SI no está vacio el directorio, 
	entonces la función falla.

	int closedir(DIR *dirp);
	- La función closedir() cierra el flujo a un directorio asociado con dirp.
	Una llamada exitosa a la función también cierra el descriptor de archivo asociado con dirp.

	char *getcwd(char *buf, size_t size);
	- Nos permite obtener el PATH absoluto del directorio apuntado por buf de tamaño size.
	La función nos devuelve una cadena que contiene el PATH absoluto del directorio en el que nos encontramos trabajando y también devuelve esta por medio
	del argumento buf. Si la longitud de la cadena excede size bytes, se retorna NULL.
  
 **/
 

#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> // Nos provee de funciones que nos permite el manejo de directorios en un entorno POSIX.
#include <stdio.h>

// Programa que emula el comando ls.

int32_t main(int32_t argc, char** argv){
	
}

/* Checar https://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html */
