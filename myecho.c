
#include <stdio.h>
#include <string.h>

int main(int ac, char *av[]) {
    
    if(ac == 1){
        printf("\n");
        return 0;
    }
    int f = 0;
    if(strcmp(av[1],"-n") == 0){
        f = 2;
        
        int i;
        for(int i = f;i < ac; i++){
        if(i < ac - 1){
            printf("%s ", av[i]);
        }
        else{
            printf("%s", av[i]);
        }
            
        }
    }
    else{
        f = 1;
        for(int i = f;i < ac; i++){
            if(i < ac - 1){
                printf("%s ", av[i]);
            }
            else{
                printf("%s", av[i]);
            }
        }
        printf("\n");
        
     /*if(f == 0){
        printf("\n");
    }
    return 0;*/
    
    
}
}

