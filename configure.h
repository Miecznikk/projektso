#pragma once
#include <stdlib.h>
#include "bool.h"

typedef struct configuration
{
    char*src_path;
    char*dst_path;
    bool Recursive;
}configuration;

configuration set_config(char*src_dir,char*dst_dir,bool x);
configuration default_config();