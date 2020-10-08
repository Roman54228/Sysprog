
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>


void Copy(const int otkuda, const int kuda) {
    char buff[4096];
    int n = read(otkuda, buff, 4096), p = 0;
    if (n < 0) {
        perror("error");
        exit(1);
    }
    while (n > 0) {
        p = write(kuda, buff, n);
        if (p < 0) {
            perror("error");
            exit(1);
        }
        n -= p;
    }
}


int main(int argc, char *argv[]) {
    int i = 0, count = 0;
    char *otkuda_name, *kuda_name;
    for (i = 1; i < argc; ++i) {
        if (argv[i][0] != '-') {
            if (count == 0) {
                otkuda_name = argv[i];
                count++;
            }
            else if (count == 1) {
                kuda_name = argv[i];
                count++;
            }
            else {
                count++;
            }
            
        }
    }
    if (count != 2 ) {
        printf("error");
        return 0;
    }

    int otk, kda, ch = 0;
    if ((otk = open(otkuda_name, O_RDONLY)) < 0) {
        perror("error");
        exit(1);
    }
    int I=0,v=0,f=0;
    while ((ch = getopt(argc, argv, "ifv")) != -1) {
        switch (ch) {
            case 'i':
                I=1;
                break;
            case 'v':
                v=1;
                break;
            case 'f':
                f=1;
                break;
        }
    }
    if (f == 1) {
        remove(kuda_name);
    }
   
    if ((kda = open(kuda_name, O_RDWR | O_CREAT | O_TRUNC, S_IWRITE | S_IREAD)) < 0) {
        perror("error");
        exit(1);
    }

    if (I == 1) {
        printf("overwrite %s? (y/n [n])", kuda_name);
        char answer;
        scanf("%c", &answer);
        if (answer != 'y') {
            printf("not overwritten\n");
            return 0;
        }
    }
    if (v == 1) {
        printf("%s->%s\n", otkuda_name, kuda_name);
    }
   
    Copy(otk, kda);
    close(otk);
    close(kda);
    return 0;
}
