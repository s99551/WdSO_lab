#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_SIZE 2048
#define NAME "myfifo"

int main(int argc, char** argv){
    if(mkfifo(NAME, 0777) == -1 && errno != EEXIST){
        printf("Błąd funkji fifo\n");
        exit(1);
    }
    int fdw = open(NAME, O_WRONLY | O_NONBLOCK);
    if(fdw==-1){
        printf("Błąd otwarcia potoku do zapisu\n");
        exit(1);
    }
    char bufor[BUF_SIZE];
    int i;
    for(i=0;i<10;++i){
        snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linię nr %d\n", i);
        write(fdw, bufor, sizeof(bufor));
        sleep(1);
    }
    close(fdw);
    return 0;
}