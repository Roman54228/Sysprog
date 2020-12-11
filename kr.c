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
    int pf[2];
    int p = pipe(pf);
    pid_t pid = fork();
    int byte = 0;
    char buf[256];
    
    int x;
    if(pid == 0){
        dup2(pf[1],1);
        close(pf[0]);
        close(pf[1]);
        while((x = read(1, buf, 1))>0){
            byte += 1;
            write(1, buf, 1);
            
        }
    }
    printf("%d", byte);
}
