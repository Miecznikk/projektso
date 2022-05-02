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
        syslog(LOG_INFO, "Stworzono plik z PID demona ");
    return true;
}
void handler(int signum){
        syslog(LOG_INFO, "Wymuszenie synchronizacji po przez sygnal SIGUSR");
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
        openlog ("Rozpoczecie Logowania", LOG_PID | LOG_CONS, LOG_LOCAL0);
        syslog(LOG_INFO, "Rozpoczecie dzialania programu");
        int opt;
        char* dir1;
        char* dir2;
        bool RecursiveFlag=false;
        int tmp;
        int time=10;
        int size=10485760;
        char *demon="demon_pid.txt";
        char cwd[PATH_MAX];
        if (getcwd(cwd, sizeof(cwd)) != NULL){}
                int lenght=strlen(cwd);
                lenght+=strlen(demon)+2;
                char full_cwd[lenght];
                snprintf(full_cwd,lenght,"%s/%s",cwd,demon);

        if(argc<=4){
                printf("Too few arguments sent to main\n");
                syslog(LOG_INFO, "Error za mala ilosc argumentow / ZLA SKLADNIA WYWOŁANIA");
                exit(-1);  
        }
        else{
                while((opt = getopt(argc, argv, "rs:d:t:w:x")) != -1) {
                        switch(opt){
                        case 'r':
                        RecursiveFlag=true;
                        syslog(LOG_INFO, "Ustawiony tryb -R");
                                break;
                        case 's':
                        dir1 = optarg;
                        syslog(LOG_INFO, "Sciezka zrodlowa ustawiona na %s",dir1);
                                break;
                        case 'd':
                        dir2 = optarg;
                        syslog(LOG_INFO, "Sciezka dolecowa ustawiona na %s",dir2);
                                break;
                        case 't':
                                time=atoi(optarg);
                        syslog(LOG_INFO, "Interwal synchronizacji ustawiony na %d",time);
                                break;
                        case 'w':
                                tmp=atoi(optarg);
                                size=1024*1024*tmp;
                        syslog(LOG_INFO, "Rozmiar pliku duzego ustawiony na  %d MB",(size/(1024*1024)));
                                break;
                        case '?': 
                                printf("unknown option: %c\n", optopt);
                                break; 
                        }
                }
                if(checkIsDirectory(dir1) && checkIsDirectory(dir2)){
                configuration config=set_config(dir1,dir2,RecursiveFlag,size); // albo false flaga ro R    
                syslog(LOG_INFO, "Sciezki podane prawidlowo");
                if(signal(SIGUSR1, handler)==SIG_ERR){
    	        exit(EXIT_FAILURE);
                }
                Fork_Process();
                create_pid_file(full_cwd);
                while(1){
                syslog(LOG_INFO, "Rozpoczecie Synchronizacji");
                synchronise_remove(config);
                synchronise(config);
                syslog(LOG_INFO, "Zakonczenie synchronizacji");
                syslog(LOG_INFO, "Uspienie pracy na %d s",time);
                sleep(time);
                }
                }else{
                        syslog(LOG_INFO, "Sciezka %s lub %s nie jest katalogiem",dir1,dir2);
                        printf("Podany plik nie jest katalogiem\n");
                        exit(EXIT_FAILURE);
                }
        }  
        return 0;
}
