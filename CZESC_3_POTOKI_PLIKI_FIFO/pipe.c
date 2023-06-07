#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUF_SIZE 2048

int main(int argc, char** argv){
    int fd[2];
    // fd[0] - read
    // fd[1] - write
    if (pipe(fd) == -1){
        printf("Błąd funkcji pipe\n");
        return EXIT_FAILURE;
    }
    int id = fork(); 
    switch(id){
        case -1:
            printf("Błąd funkcji fork\n");
            return EXIT_FAILURE;
        case 0:
            close(fd[0]);
            char bufor[BUF_SIZE];
            int i;
            for(i=0;i<10;++i){
                snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linię nr %d\n", i);
                write(fd[1], bufor, sizeof(bufor));
            }
            close(fd[1]);
            break;
        default:
            close(fd[1]);
            char komunikat[BUF_SIZE];
            while(read(fd[0], komunikat, sizeof(komunikat)))
                printf("%s", komunikat);
            close(fd[0]);
    }
    return EXIT_SUCCESS;
}