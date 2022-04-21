#include "filetype.h"
typedef struct file_list file_list;

struct file_list {
    char *name; // nazwa pliku/katalogu
    char *path; //katalog z ktorego pochodzi
    char* time;
    FILE_TYPE type;
    struct file_list *next; // wskaźnik na następny element
};