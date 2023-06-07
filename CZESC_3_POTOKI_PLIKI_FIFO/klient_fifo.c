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
    int fdr = open("fifo1", O_RDONLY);
    if(fdr==-1){
        printf("Błąd otwarcia potoku do odczytu\n");
        exit(1);
    }
    char komunikat[BUF_SIZE];
    while(read(fdr, komunikat, sizeof(komunikat))){
        printf("Odebrano: %s", komunikat);
        sleep(2);
    }
    close(fdr);

    return 0;
}