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

union semun {
               int              val;    /* Value for SETVAL */
               struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
               unsigned short  *array;  /* Array for GETALL, SETALL */
               struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};

int main(int argc, char *argv[])
{
    int semid, shmid;
    union semun arg1;
    struct sembuf sop;
    char *addr;

    

    shmid = shmget(IPC_PRIVATE, 10000, IPC_CREAT | 0600);
    if (shmid == -1)
        perror("shmid");

    semid = semget(IPC_PRIVATE, 1, IPC_CREAT | 0600);
    if (shmid == -1)
        perror("semid");

    

    addr = shmat(shmid, NULL, SHM_RDONLY);
    if (addr == (void *) -1)
        perror("shmat");

    

    arg1.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1)
        perror("semctl");

    

    sop.sem_num = 0;
    sop.sem_op = 0;
    sop.sem_flg = 0;

    if (semop(semid, &sop, 1) == -1)
        perror("semop");

   

    printf("%s\n", addr);
    
   /* if (shmctl(shmid, IPC_RMID, NULL) == -1)
        perror("shmctl");*/
    

    return 0;
}

