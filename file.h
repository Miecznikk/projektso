#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include <dirent.h>
#include <errno.h>

bool checkIsDirectory(const char* path){
    DIR* directory = opendir(path);

    if(directory != NULL)
    {
     closedir(directory);
     return true;
    }else{
            return false;
    }
}


