#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include "file.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include "sync.h"

int main(int argc, char *argv[]){
        if(argc<=2){
                printf("Too few arguments sent to main\n");
                exit(-1);  
        }
        else{
                char* dir1 = argv[1];
                char* dir2 = argv[2];
                if(checkIsDirectory(dir1) && checkIsDirectory(dir2)){
                        synchronise(dir1);
                }
                else{
                        printf("Podany plik nie jest katalogiem\n");
                        exit(EXIT_FAILURE);
                }
        }  
}
