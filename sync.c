#include "sync.h"
#include "file.h"
#include "configure.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>
#include "bool.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
void synchronise(file_list *Lista,configuration config){
    Lista=Recursive_Content(Lista,config.src_path);
    //kopiuje pliki ze zrodlowego do docelowego jesli ich nie ma,a jesli istnieja i ich data modyfikacji jest rozna to ustawiana jest na ta ze zrodlowego//
    while(Lista->next!=NULL){
        Lista=Lista->next;
        int lenght = strlen(Lista->path) + strlen(Lista->name) - strlen(config.src_path) + strlen(config.dst_path) + 2;
        char file_dst_path[lenght];
        snprintf(file_dst_path, lenght, "%s%s/%s", config.dst_path, Lista->path + strlen(config.src_path), Lista->name);
        lenght = strlen(Lista->path);
        lenght += strlen(Lista->name) + 2;
        char file_src_path[lenght];
        snprintf(file_src_path, lenght, "%s/%s", Lista->path, Lista->name);
        struct stat st;
        stat(file_src_path, &st);
        int size = st.st_size;
        if(Lista->type==REGULAR_FILE){
            if(ExistsCheck(file_dst_path)==false){
                if(size%1048576 >10){
                copy_file_mmap(file_src_path,file_dst_path);
                }else{
                    copy_file(file_src_path,file_dst_path);
                }
                Copy_Modify_Time(file_src_path,file_dst_path);
            }else{
                if(Check_Time(file_src_path,file_dst_path)==false){
                    remove(file_dst_path);
                    copy_file(file_src_path,file_dst_path);
                    Copy_Modify_Time(file_src_path,file_dst_path);
                }
            }
        }

        if(Lista->type==DIRECTORY && config.Recursive==true){
            if(ExistsDirCheck(file_dst_path)==false){
                mkdir(file_dst_path,0755);
                Copy_Modify_Time(file_src_path,file_dst_path);
            }
    
        }
    }
    ///Usuwa pliki ktore sa w docelowym a nie ma ich w zrodlowym///
    file_list *Lista_DST=Create_List();
    Lista_DST=Recursive_Content(Lista_DST,config.dst_path);
    while (Lista_DST->next!=NULL)
    {
     Lista_DST=Lista_DST->next;
     int lenght = strlen(Lista_DST->path) + strlen(Lista_DST->name) - strlen(config.src_path) + strlen(config.dst_path) + 2;
    char file_dst_path[lenght];
    snprintf(file_dst_path, lenght, "%s%s/%s", config.src_path, Lista_DST->path + strlen(config.dst_path), Lista_DST->name);
    lenght = strlen(Lista->path);
    lenght += strlen(Lista->name) + 2;
    char file_src_path[lenght];
    snprintf(file_src_path, lenght, "%s/%s", Lista_DST->path, Lista_DST->name);   
    if(Lista_DST->type==DIRECTORY && config.Recursive==true){
            if(ExistsDirCheck(file_dst_path)==false){
            remove(file_src_path);
        }
    }
    if(Lista_DST->type=REGULAR_FILE){
        if(ExistsCheck(file_dst_path)==false){
            remove(file_src_path);
        }
    }
    }
    free(Lista);
    free(Lista_DST);
}