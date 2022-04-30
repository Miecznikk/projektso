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
#include "filetype.h"
#include "filelist.h"

bool checkIsDirectory(const char* path); // sprawdza czy plik jest katalogiem
FILE_TYPE Get_File_Type(const char* name); // pobiera typ pliku
file_list *show_dir_content(char * path); //czyta zawartosc katalogu i zapisuje na liste
void printList(); // tymczasowe do sprawdzania listy czy tyrbi
bool ExistsCheck(const char *path);
void copy_file(char *src_file,char* dst_file);
bool Check_Time(char *src_file,char* dst_file);
void Copy_Modify_Time(char *src_file,char* dst_file);
bool ExistsDirCheck(const char*path);
file_list *Create_List();
file_list *Recursive_Content(file_list *Lista,char * path);
void copy_file_mmap(char *src_path, char *dst_path);
void Clear_List(file_list **first);

