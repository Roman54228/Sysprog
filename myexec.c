#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
int main(int argc, char* argv[]){
    int pf[2];
    int p = pipe(pf);
    char buf[2];
    pid_t pid = fork();
    
    int words = 0, bytes = 0, str = 0;
    int isword = 1;
    
    if(pid == 0){
        dup2(1,pf[0]);
        close(pf[0]);
        close(pf[1]);
        execvp(argv[1], argv + 1);
        exit(1);
    }
    else{
        close(pf[1]);
        int x;
        while((x = read(pf[0], buf, 1))>0){
            write(pf[1], buf, 1);
            bytes += 1;
            if(buf[0] == '\n'){
                str += 1;
                isword = 0;
            }
            switch(isword){
                case(1):
                    if(!isspace(buf[0])){
                        
                    }
                    else{
                        isword = 1;
                        words += 1;
                    }
                case(0):
                    isword = 1;
            }
    }
    
        close(pf[0]);

    }
}
