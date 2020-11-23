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

struct msgbuf
{
    long mtype;     /* тип сообщения, должен быть > 0 */
    char mtext[100]; /* содержание сообщения */
};

void judge(int id, int n)
{
    struct timespec mt1, mt2;
    struct msgbuf j, jj = {2, "1"};
    
    
    for(int i = 0; i < n; i++){
        if(msgrcv(id, &j, 9, 1, 0) < 0){
            perror("ju rcv");
            exit(1);
        }
    }
    printf("Судья: все на месте\n");
    if(msgsnd(id, &jj, 10, 0) < 0){
        perror("ju snd");
        exit(1);
    }
    printf("Судья: Старт!\n");
    
    clock_gettime(CLOCK_REALTIME, &mt1);
    
    
    if(msgrcv(id, &j, 11, n + 2, 0) < 0){
        perror("ju rcv");
        exit(1);
    }
    clock_gettime(CLOCK_REALTIME, &mt2);
    printf("Судья: Конец!%ld", 1000*(mt2.tv_sec - mt1.tv_sec)+
            (mt2.tv_nsec - mt1.tv_nsec)/1000000 );
   
}

void runner(int i, int id){
    struct msgbuf r = {1, "1"}, rr, rrr = {i + 3, "1"};


    
    if(msgsnd(id, &r, 9, 0) < 0){
        perror("r snd");
        exit(1);
    }
    
    if(msgrcv(id, &rr, 9, i + 2, 0) < 0){
        perror("rr rcv");
        exit(1);
    }
    
    if(msgsnd(id, &rrr, 9, 0) < 0){
        perror("rrr snd");
        exit(1);
    }
    
    printf("Бегун %d : передаю эстафету\n", i);
    
}

int main(int argc, char* argv[]){
        setbuf(stdout, NULL);
        int n = atoi(argv[1]);
        key_t key = ftok(".", 's');//IPC_PRIVATE
        int id = msgget(key, IPC_CREAT  | 0700);
        if (id < 0)
        {
            perror("msgget");
            exit(1);
        }

        for (int i = 0; i < n+1 ; i++)
        {
            int pid = fork();

            if (pid == 0)
            {
                if (i == n)
                {
                    judge(id, n);
                }
                else
                {
                    runner(i, id);
                }
                exit(1);
            }
        }

        msgctl(id, IPC_RMID, 0);
        return 0;
    }
    

