#include "sync.h"
#include "file.h"
void synchronise(char *path){
    file_list *Lista=show_dir_content(path);
    printList(Lista);
}