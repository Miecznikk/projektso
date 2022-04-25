#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "bool.h"
#include "file.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <dirent.h>
#include "sync.h"
#include "configure.h"
#include <signal.h>
static int create_pid_file(const char *pid_file)
{
    pid_t my_pid = getpid();
    char my_pid_str[10];
    int fd;

    sprintf(my_pid_str, "%d", my_pid);

    if((fd = open(pid_file, O_RDWR|O_CREAT, 0666)) == -1)
        return false;

    if(write(fd, my_pid_str, strlen(my_pid_str)) == -1)
        return false;

    close(fd);

    return true;
}
void handler(int signum){
	syslog(LOG_INFO, "Wymuszenie w trakcie synchronizacji");
	syslog(LOG_NOTICE,"Ctrl+'/' used");
	closelog();
}
void Fork_Process(){
        syslog(LOG_INFO, "Rozpoczecie forkowania");
        pid_t pid, sid;
        pid = fork();
        if (pid < 0) {
                exit(EXIT_FAILURE);
        }
        if (pid > 0) {
                exit(EXIT_SUCCESS);
        }
        umask(0);
        sid = setsid();
        if (sid < 0) {
                exit(EXIT_FAILURE);
        }
        if ((chdir("/")) < 0) {
                exit(EXIT_FAILURE);
        }
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        syslog(LOG_INFO, "Zakonczenie forkowania");
}
int main(int argc, char *argv[]){
        int opt;
        char* dir1;
        char* dir2;
        bool RecursiveFlag=false;
        int time=10;
        char *demon="demon_pid.txt";
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL){}
                int lenght=strlen(cwd);
                lenght+=strlen(demon)+2;
                char full_cwd[lenght];
                snprintf(full_cwd,lenght,"%s/%s",cwd,demon);

        if(argc<=0){
                printf("Too few arguments sent to main\n");
                exit(-1);  
        }
        else{
                while((opt = getopt(argc, argv, ":knrs:d:t:v")) != -1) {
                        switch(opt){
                        case 'n':
                        ///pomoc//
                        case 'r':
                        RecursiveFlag=true;
                                break;
                        case 's':
                        printf("filename %s\n", optarg); 
                        dir1 = optarg;
                                break;
                        case 'd':
                        printf("filename %s\n", optarg); 
                        dir2 = optarg;
                                break;
                        case 't':
                        time=atoi(optarg);
                                break;
                        }
                }
                if(checkIsDirectory(dir1) && checkIsDirectory(dir2)){ 
                configuration config=set_config(dir1,dir2,RecursiveFlag); // albo false flaga ro R        
                if(signal(SIGUSR1, handler)==SIG_ERR)
    	        exit(EXIT_FAILURE);
                openlog ("Start Logging", LOG_PID | LOG_CONS, LOG_LOCAL0);
                syslog(LOG_INFO, "Rozpoczecie dzialania programu");
                Fork_Process();
                create_pid_file(full_cwd);
                while(1){
                file_list *List=Create_List();
                syslog(LOG_INFO, "Rozpoczecie synchronizacji");
                synchronise(List,config);
                syslog(LOG_INFO, "Usypia sie na %d",time);
                sleep(time);
                syslog(LOG_INFO, "Synchronizacja zakonczona");
                }
                }else{
                        printf("Podany plik nie jest katalogiem\n");
                        exit(EXIT_FAILURE);
                }
        }  
        return 0;
}
