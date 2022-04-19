#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <bool.h>
#include <file.h>

int main(int argc, char *argv[])
{
      if(checkIsDirectory(argv[1]) && checkIsDirectory(argv[2])){
          printf("SIEMA SIEMA");
      }
}
