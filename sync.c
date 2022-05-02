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
    syslog(LOG_INFO, "Tworzenie listy z danymi");
    file_list *Lista=Create_List();
    Lista=Recursive_Content(Lista,config.src_path);
    file_list *head_Lista=Lista;
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
                    if(size>config.size){
                        syslog(LOG_INFO, "Kopiowanie pliku przy pomocy mmap waga >10MB. Plik skopiowany z %s do %s",file_src_path,file_dst_path);
                        copy_file_mmap(file_src_path,file_dst_path);
                        }else{
                            syslog(LOG_INFO, "Kopiowanie pliku przy pomocy read/write. Plik skopiowany z %s do %s",file_src_path,file_dst_path);
                            copy_file(file_src_path,file_dst_path);
                        }
                        syslog(LOG_INFO, "Modyfikacja czasu edycji");
                    Copy_Modify_Time(file_src_path,file_dst_path);
             }else{
                 if(Check_Time(file_src_path,file_dst_path)==false){
                     syslog(LOG_INFO, "Kopiowanie pliku z powodu roznego czasu edycji. Plik zmodyfikowany %s",file_dst_path);
                     remove(file_dst_path);
                     if(size/1048576 >10){
                        copy_file_mmap(file_src_path,file_dst_path);
                     }
                     else{
                        copy_file(file_src_path,file_dst_path);
                     }
                     Copy_Modify_Time(file_src_path,file_dst_path);
                 }
             }
        }

        if(Lista->type==DIRECTORY && config.Recursive==true){
            if(ExistsDirCheck(file_dst_path)==false){
                mkdir(file_dst_path,0755);
                syslog(LOG_INFO, "Tworzenie katalogu %s",file_dst_path);
            }
    
        }
    }
    Clear_List(&head_Lista);
    if(head_Lista==NULL){
        syslog(LOG_INFO, "Lista z danymi wyczyszczona, zwolnienie pamieci");
    }
}
void synchronise_remove(configuration config){
    syslog(LOG_INFO, "Tworzenie listy z danymi");
    file_list *Lista_DST=Create_List();
    Lista_DST=Recursive_Content(Lista_DST,config.dst_path);
    file_list *head_Lista_DST=Lista_DST;
    printList(Lista_DST);
    while (Lista_DST->next!=NULL)
    {
    Lista_DST=Lista_DST->next;
    int lenght = strlen(Lista_DST->path) + strlen(Lista_DST->name) - strlen(config.src_path) + strlen(config.dst_path) + 2;
    char file_dst_path[lenght];
    snprintf(file_dst_path, lenght, "%s%s/%s", config.src_path, Lista_DST->path + strlen(config.dst_path), Lista_DST->name);
    lenght = strlen(Lista_DST->path);
    lenght += strlen(Lista_DST->name) + 2;
    char file_src_path[lenght];
    snprintf(file_src_path, lenght, "%s/%s", Lista_DST->path, Lista_DST->name);   
    if(Lista_DST->type==DIRECTORY && config.Recursive==true){
            if(ExistsDirCheck(file_dst_path)==false){
            syslog(LOG_INFO, "Usuwanie pliku %s",file_src_path);
            remove(file_src_path);
        }
    }
    if(Lista_DST->type=REGULAR_FILE){
        if(ExistsCheck(file_dst_path)==false){
            syslog(LOG_INFO, "Usuwanie katalogu %s",file_src_path);
            remove(file_src_path);
        }
    }
    }
    Clear_List(&head_Lista_DST);
    if(head_Lista_DST==NULL){
        syslog(LOG_INFO, "Lista z danymi wyczyszczona, zwolnienie pamieci");
    }
}