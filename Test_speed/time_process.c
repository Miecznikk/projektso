#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/mman.h> 
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
void copy_file_mmap(char *src_path, char *dst_path){
    int sfd, dfd;
    char *src, *dest;
    struct stat s;
    size_t filesize;
    sfd = open(src_path, O_RDONLY);
    filesize = lseek(sfd, 0, SEEK_END);
    src = mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, sfd, 0);
    dfd = open(dst_path, O_RDWR | O_CREAT, 0666);
    ftruncate(dfd, filesize);
    dest = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_SHARED, dfd, 0);
    memcpy(dest, src, filesize);
    munmap(src, filesize);
    munmap(dest, filesize);
    close(sfd);
    close(dfd);
}
int main(int argc, char *argv[])
{
    char *file1=argv[1];
    char*file2=argv[2];
    clock_t t;
    t = clock();
    copy_file_mmap(file1,file2);
    remove(file2);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Mmap() took %f seconds to execute \n", time_taken);


    clock_t t2;
    t2 = clock();
    copy_file(file1,file2);
    remove(file2);
    t2 = clock() - t2;
    double time_taken2 = ((double)t2)/CLOCKS_PER_SEC;
    printf("Read/Write() took %f seconds to execute \n", time_taken2);
    return 0;
}
