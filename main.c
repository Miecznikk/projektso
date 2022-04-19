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
#include "checkparametrs.h"

int main(int argc, char *argv[])
{
      pid_t pid, sid;
      pid_t child_process;

      char *parametr[] = {"firefox", NULL, NULL};
      if(EnoughParametrs(argc)==true){
      if(checkIsDirectory(argv[1])==true && checkIsDirectory(argv[2])==true){
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
        while (1) {
		   child_process=fork();
		   if(child_process!=0){
			   sleep(300);
		   }else{
                     //TUTAJ BEDZIE ROBIONY DYM//
			execvp("/usr/bin/firefox",parametr);
			
			fprintf (stderr,  "an error occurred in execvp\n"); 
			abort();
		   }
        }
      }else{
            perror("PATH ERROR");
      }
      }else{
            printf("Not enough parametrs, Exiting...\n");
	      exit(1);
      }
}
