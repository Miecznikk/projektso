#include "file.h"

char** list_dir(char* directory_name){
        DIR *d;
        struct dirent *dir;
        char** files;
        int i =0;
        d = opendir(directory_name);
        if(d){
                while((dir = readdir(d)) != NULL){
                        if(dir->d_type == DT_REG){
                                files[i] = malloc(sizeof(char)*255);
                                strcpy(files[i], dir->d_name);
                                i++;
                        }    
                }
                closedir(d);
        }
        return files;
}

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
