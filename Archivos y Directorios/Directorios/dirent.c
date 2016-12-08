/** 
 * Manejo de Directorios utilizando el estándar POSIX y la estructura DIRENT
 * 
 * struct dirent {
    ino_t          d_ino;        inode number 
    off_t          d_off;        offset to the next dirent 
    unsigned short d_reclen;     length of this record 
    unsigned char  d_type;       type of file; not supported
                                   by all file system types 
    char           d_name[256];  filename 
	};
 * 
 * 
 **/
 

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <dirent.h>

int32_t main(void){
	

	return 0;
}

/* Checar https://users.cs.cf.ac.uk/Dave.Marshall/C/node20.html */
