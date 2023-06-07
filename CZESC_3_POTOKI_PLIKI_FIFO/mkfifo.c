#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 2048

int main(int argc, char** argv){
    if(mkfifo("fifo1", 0777) == -1 && errno != EEXIST){
        printf("Błąd funkji fifo\n");
        exit(1);
    }
    int id = fork();
    int fdw, fdr;
    switch(id){
        case -1:
            printf("Błąd funkcji fork\n");
            exit(1);
        case 0:
            //int fdw;
            fdw = open("fifo1", O_WRONLY);
            if(fdw==-1){
                printf("Błąd otwarcia potoku do zapisu\n");
                exit(1);
            }
            char bufor[BUF_SIZE];
            int i;
            for(i=0;i<10;++i){
                snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linię nr %d\n", i);
                write(fdw, bufor, sizeof(bufor));
            }
            close(fdw);
            break;
        default:
            //int fdr;
            fdr = open("fifo1", O_RDONLY);
            if(fdr==-1){
                printf("Błąd otwarcia potoku do odczytu\n");
                exit(1);
            }
            char komunikat[BUF_SIZE];
            while(read(fdr, komunikat, sizeof(komunikat)))
                printf("Odebrano: %s", komunikat);
            close(fdr);
            return 0;
    }
   
    return 0;
}