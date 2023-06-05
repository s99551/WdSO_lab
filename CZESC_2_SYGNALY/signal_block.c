#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
    sigset_t sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGINT);
    sigaddset(&sigmask, SIGQUIT);
    sigprocmask(SIG_BLOCK, &sigmask, NULL);

    sigset_t pending;
    int time=0;

    while(1){
        printf("Cześć, tu proces %d\n", getpid());
        if(time==15){
            sigpending(&pending);
            if(sigismember(&pending, SIGINT))
                printf("W ciągu pierwszych 15 sekund wystąpił sygnał SIGINT\n");
            if(sigismember(&pending, SIGQUIT))
                printf("W ciągu pierwszych 15 sekund wystąpił sygnał SIGQUIT\n");
            printf("Obsługa sygnałów odblokowana\n");
            sigprocmask(SIG_UNBLOCK, &sigmask, NULL);
        }
        sleep(1);
        time++;
    }


    return 0;
}