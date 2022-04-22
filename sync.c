#include "sync.h"
#include "file.h"
#include "configure.h"
#include <stdio.h>     
#include <time.h> 
void synchronise(configuration config){
    file_list *Lista=show_dir_content(config.src_path);
    printList(Lista);

    while(Lista->next!=NULL){
        Lista=Lista->next;
        int path_src_lenght=strlen(config.src_path);
        int path_dst_lenght=strlen(config.dst_path);
        int name_file_lenght=strlen(Lista->name);
        int tmp=path_src_lenght+name_file_lenght+2;
        int tmp2=path_dst_lenght+name_file_lenght+2;
        char file_src_path[path_src_lenght+name_file_lenght];
        char file_dst_path[path_dst_lenght+name_file_lenght];
        snprintf(file_src_path, tmp, "%s/%s", config.src_path, Lista->name);
        snprintf(file_dst_path, tmp2, "%s/%s", config.dst_path, Lista->name);

        // printf("%s\n",file_src_path);//
        // printf("%s\n",file_dst_path);//
        if(ExistsCheck(file_dst_path)==false){
            copy_file(file_src_path,file_dst_path);
            Copy_Modify_Time(file_src_path,file_dst_path);
        }else{
            if(Check_Time(file_src_path,file_dst_path)==true){
                Copy_Modify_Time(file_src_path,file_dst_path);
            }
        }
    }



}