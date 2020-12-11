#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/sem.h>


int main(int argc, char* argv[])
{
    int pf1[2];
    int pf2[2];
     if(pipe(pf1)<0){
        perror("pipe1");
    }
    if(pipe(pf2)<0){
        perror("pipe2");
    }
    pid_t pid = fork();
    int byte = 0;
    char buf1[2];
    char buf2[2];
    int out = 0;
    int err = 0;
  
    if(pid == 0){
        close(pf1[1]);
        while (read(pf[0], buf1, 1) == 1) {
            out++;
            if(write(1, buf1, 1)<0){
                perror("write_out");
            }
            close(pf1[0]);
            exit(1);
        }
        if(out > 0){
            printf("%d", out);
        }
        }
    }
     if(pid == 0){
         close(pf2[1]);
         while(read(pf2[0], buf2, 1) == 1){
             err++;
             if(write(1, buf2, 1)<0){
                 perror("write_err");
             }
             close(pf2[0]);
             exit(1)
         }
     }
    printf("%d", byte);
}
