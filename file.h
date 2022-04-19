#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <bool.h>

bool checkIsDirectory(const char* path){
        struct stat status;
        if(status.st_mode & S_IFDIR){
                return true;

        }else{
                return false;
        }
}


