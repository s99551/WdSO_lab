#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){
    int pid = fork();
    int status=0;
    pid_t wpid;
    switch(pid){
        case -1:
            printf("Błąd funkcji fork()\n");
            exit(1);
            break;
        case 0:
            printf("Tu proces potomny, PID: %d\n", getpid());
            sleep(10);
            printf("Proces potomny zakończył pracę.\n");
            exit(0);
        default:
            while(1){
                wpid = waitpid(pid, &status, WNOHANG);
                printf("Czekam na zakończenie działania potomka\n");
                sleep(1);
                if(wpid == pid)
                    break;
            }
            printf("Potomek zakończył działanie ze statusem %d\n", status);
    }

    return 0;
}