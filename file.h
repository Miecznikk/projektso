#pragma once
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

char** list_dir(char* directory_name);
bool checkIsDirectory(const char* path);


