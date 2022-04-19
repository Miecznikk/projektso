#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include <dirent.h>
#include <errno.h>

bool EnoughParametrs(int argc){
    if(argc<3){
        return false;
    }else{
        return true;
    }
}