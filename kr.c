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

void hello()
{
    printf("\nhello!\n");
}

int main()
{
    int byte = 0;
    char buf[256];
    pid_t pid;
    int x;
    if(pid == 0){
        while((x = read(1, buf, 1))>0){
            byte += 1;
            
        }
    }
    printf("%d", byte);
}
