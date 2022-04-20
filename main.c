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
                char** files_dir1;
                char** files_dir2;
                if(checkIsDirectory(dir1) && checkIsDirectory(dir2)){
                        files_dir1 = list_dir(dir1);
                        files_dir2 = list_dir(dir2);

                        printf("%d",compare_dirs(files_dir1,files_dir2));
                }
                else{
                        printf("Podany plik nie jest katalogiem\n");
                        exit(EXIT_FAILURE);
                }
        }  
}
