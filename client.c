#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>


void read(int fd, int shmid, int semid){
    FILE *file = fdopen(fd, "r");
    char *addr;
    
    
    addr = shmat(shmid, NULL, 0);
    if (addr == (void *) -1)
    perror("shmat");
    
    
    while(!feof(stream)) {
          if (fgets(addr, 60, file)) {
              enter(semid, 0);
              wait(semid, 1);
              exit(semid, 1);
          }
      }
      fclose(file);
}


int main(int argc, char *argv[])
{
    int semid, shmid;
    struct sembuf sop;
    if ((fd = open(argv[3], O_RDWR | O_EXCL)) < 0)
    {
        perror("open failed");
        exit(1);
    }


    shmid = atoi(argv[1]);
    semid = atoi(argv[2]);
    
    read(fd, shmid, semid);
    close(fd);
    

    /* возврат семафора к 0 */

    sop.sem_num = 0;
    sop.sem_op = -1;
    sop.sem_flg = 0;

    if (semop(semid, &sop, 1) == -1)
        perror("semop");
}

