#pragma once
#include <stdlib.h>
#include "bool.h"

typedef struct configuration
{
    char*src_path;
    char*dst_path;
}configuration;

configuration set_config(char*src_dir,char*dst_dir);
configuration default_config();