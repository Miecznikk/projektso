#include "file.h"
#include <dirent.h> 
#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h> 
#include <assert.h>
#include <fcntl.h>
#include <sys/wait.h>
bool ExistsCheck(const char *path){ //sprawdza czy plik istnieje
  if( access( path, F_OK ) == 0 ) {
    return true;
} else {
    return false;
}
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
FILE_TYPE Get_File_Type(const char* name){
        struct stat sb;
        stat(name, &sb);
         switch (sb.st_mode & S_IFMT) {
        case S_IFBLK:  return BLOCK_DEVICE;            break;
        case S_IFCHR:  return CHARACTER_DEVICE;        break;
        case S_IFDIR:  return DIRECTORY;               break;
        case S_IFIFO:  return FIFO;                    break;
        case S_IFLNK:  return SYMBOLIC_LINK;           break;
        case S_IFREG:  return REGULAR_FILE;            break;
        case S_IFSOCK: return SOCKET;                  break;
        default:       return UNKNOWN;                 break;
    }
}
file_list *Create_List(){
  file_list *Lista=malloc(sizeof(file_list));
  Lista->next=NULL;
  Lista->name=NULL;
  Lista->path=NULL;
  Lista->time=NULL;
  return Lista;
}
file_list *insertList(file_list *Lista,char* namee,FILE_TYPE typee,char* pathh,char *timee){
   while(Lista->next != NULL) Lista = Lista->next;
    Lista->next = malloc(sizeof(file_list));
	  Lista = Lista->next;
    Lista->name = malloc(strlen(namee));
    Lista->name = namee;
    Lista->path = malloc(strlen(pathh));
    Lista->path=pathh;
    Lista->time=malloc(strlen(timee));
    Lista->time=timee;
    Lista->next = NULL;
    Lista->type = typee;
    return Lista;
}

file_list *show_dir_content(char * path)
{
  // int path_lenght=strlen(path);//
  file_list *Lista=Create_List();
  DIR * directory = opendir(path); // open the path
  if(directory==NULL) return NULL; // if was not able, return
  struct dirent * dir; // for the directory entries
  struct stat attr;
  stat(path, &attr);
  while ((dir = readdir(directory)) != NULL) // if we were able to read somehting from the directory
    {
      if(dir-> d_type != DT_DIR){
                        int path_lenght=strlen(path); //ilosc znakow w sciezce
                        path_lenght+=strlen(dir->d_name)+2;// dlugosc + nazwa pliku
                        char path_file[path_lenght]; // contener na to
                        snprintf(path_file, path_lenght, "%s/%s", path, dir->d_name); // laczy
                        printf("%s\n",path_file); // testowo wypisuje sciezke
                        if(ExistsCheck(path_file)==false){printf("dzieki dziala");} //sprawdza czy exists do pliku dziala
                        printf("%s,%s\n", dir->d_name,ctime(&attr.st_mtime)); // wypisuje resze parametrow
                        insertList(Lista,dir->d_name,Get_File_Type(path_file),path,ctime(&attr.st_mtime)); //dodaje na lsite
      }else{

                if(dir -> d_type == DT_DIR && strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0 ) // if it is a directory
                {
                  //rekursywnie dodac
      }else{

        }
      }      
    }
    closedir(directory); // finally close the directory
    return Lista;
}
void printList(file_list *Lista) {
   while(Lista->next != NULL){
     Lista = Lista->next; //wypisuje zawartosc listy i to co zebral
     printf("(%s,%d,%s,%s",Lista->name,Lista->type,Lista->path,Lista->time);
   }
	
}
void copy_file(char *src_file,char* dst_file){
    int fp_dst;
    int fp_src;
    fp_dst=open(dst_file,O_RDWR|O_CREAT, 0666);
    fp_src=open(src_file,O_RDONLY);
    size_t bytes_read;
    unsigned char znak[1];	
    do{
        bytes_read=read(fp_src,znak,1);
        write(fp_dst, znak, 1);
        }while(bytes_read == sizeof (znak));		
      close(fp_src);
      close(fp_dst);
      return;

}
bool Check_Time(char *src_file,char* dst_file){
  struct stat attr1,attr2;
  if (stat(src_file, &attr1) != 0 || stat(dst_file, &attr2) != 0)
    {
        printf("file excetion");
        exit(1);
    }
    if(difftime(attr1.st_mtime,attr2.st_mtime) >= 0 || difftime(attr2.st_mtime,attr1.st_mtime)){
        //zrodlowy//                                   
        return true;
    }else{
      return false;
    } 
}
void Copy_Modify_Time(char *src_file,char* dst_file){
    struct stat st;
    struct utimbuf new_times;
    stat(src_file, &st);
    new_times.actime = st.st_atim.tv_sec;
    new_times.modtime = st.st_mtim.tv_sec;
    utime(dst_file, &new_times);
    chmod(dst_file, st.st_mode);
}