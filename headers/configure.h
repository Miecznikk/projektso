#pragma once
#include <stdlib.h>
#include "bool.h"

typedef struct configuration
{
    char*src_path;
    char*dst_path;
    bool Recursive;
    int size;
}configuration;

configuration set_config(char*src_dir,char*dst_dir,bool x,int sizee);
configuration default_config();