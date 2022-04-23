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

void synchronise(configuration config){
    file_list *Lista=show_dir_content(config.src_path);
    int path_src_lenght=strlen(config.src_path);
    int path_dst_lenght=strlen(config.dst_path);
    printList(Lista);
    //kopiuje pliki ze zrodlowego do docelowego jesli ich nie ma,a jesli istnieja i ich data modyfikacji jest rozna to ustawiana jest na ta ze zrodlowego//
    while(Lista->next!=NULL){
        Lista=Lista->next;
        int name_file_lenght=strlen(Lista->name);
        int tmp=path_src_lenght+name_file_lenght+2;
        int tmp2=path_dst_lenght+name_file_lenght+2;
        char file_src_path[path_src_lenght+name_file_lenght];
        char file_dst_path[path_dst_lenght+name_file_lenght];
        snprintf(file_src_path, tmp, "%s/%s", config.src_path, Lista->name);
        snprintf(file_dst_path, tmp2, "%s/%s", config.dst_path, Lista->name);
        if(Lista->type==REGULAR_FILE){
            if(ExistsCheck(file_dst_path)==false){
                copy_file(file_src_path,file_dst_path);
                Copy_Modify_Time(file_src_path,file_dst_path);
            }else{
                if(Check_Time(file_src_path,file_dst_path)==false){
                    remove(file_dst_path);
                    copy_file(file_src_path,file_dst_path);
                    Copy_Modify_Time(file_src_path,file_dst_path);
                }
            }
        }
        if(Lista->type==DIRECTORY){
            if(ExistsDirCheck(file_dst_path)==false){
                mkdir(file_dst_path,0755);
                Copy_Modify_Time(file_src_path,file_dst_path);
            }
    
        }
    }
    ///Usuwa pliki ktore sa w docelowym a nie ma ich w zrodlowym///
    file_list *Lista_DST=show_dir_content(config.dst_path);
    while (Lista_DST->next!=NULL)
    {
        Lista_DST=Lista_DST->next;
        int name_file_lenght=strlen(Lista_DST->name);
        int tmp=path_src_lenght+name_file_lenght+2;
        int tmp2=path_dst_lenght+name_file_lenght+2;
        char file_src_path[path_src_lenght+name_file_lenght];
        char file_dst_path[path_dst_lenght+name_file_lenght];
        snprintf(file_src_path, tmp, "%s/%s", config.src_path, Lista_DST->name);
        snprintf(file_dst_path, tmp2, "%s/%s", config.dst_path, Lista_DST->name);
       if(Lista_DST->type==DIRECTORY){
            if(ExistsDirCheck(file_src_path)==false){
                remove(file_dst_path);
            }
    
        }
        if(Lista_DST->type==REGULAR_FILE){
            if(ExistsCheck(file_src_path)==false){
               remove(file_dst_path);
            }
    
        }
    }
}