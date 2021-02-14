#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int yama = 0;


void *kopaem(void* arg){
    
    int n = 100;
    int m = 20;
    
    int l = n/m;

    yama += l;
    printf("plus %d,%d \n", l, yama);
    sleep(1);
}

int main(int argc, char *argv[])
{
    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    
    
    pthread_t *tid = (pthread_t *)(malloc(sizeof(pthread_t) * m));
    for (int i = 0; i < m; i++)
    {
        if (pthread_create(&tid[i], NULL,(void *(*)(void *)) kopaem, NULL) != 0)
        {
            perror("thread create");
            exit(1);
        }
    }
    for (int i = 0; i < m; i++)
    {
        pthread_join(tid[i], NULL);
    }
    
    printf("yama - %d", yama);
    
    
    return 0;
   
}

sdgdsgdg
