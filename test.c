/*#include <stdio.h>
#include <signal.h>
#include <unistd.h>

sigset_t blocked_signals;

void handle_signal(int sig) {
    printf("Otrzymano sygnał: %d\n", sig);
}

int main() {
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGINT);
    sigaddset(&blocked_signals, SIGQUIT);

    // Blokuj obsługę sygnałów
    sigprocmask(SIG_BLOCK, &blocked_signals, NULL);

    // Ustaw obsługę sygnałów
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);

    sleep(15);

    // Odblokuj obsługę sygnałów
    sigprocmask(SIG_UNBLOCK, &blocked_signals, NULL);

    printf("Obsługa sygnałów odblokowana.\n");

    sleep(15);

    return 0;
}*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

sigset_t blocked_signals;

void handle_signal(int sig) {
    printf("Otrzymano sygnał: %d\n", sig);
}

int main() {
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGINT);
    sigaddset(&blocked_signals, SIGQUIT);

    // Blokuj obsługę sygnałów
    sigprocmask(SIG_BLOCK, &blocked_signals, NULL);

    // Ustaw obsługę sygnałów
    signal(SIGINT, handle_signal);
    signal(SIGQUIT, handle_signal);

    sleep(15);

    // Sprawdź, które sygnały wystąpiły w ciągu pierwszych 15 sekund
    sigset_t pending_signals;
    sigpending(&pending_signals);

    for (int i = 1; i <= NSIG; i++) {
        if (sigismember(&pending_signals, i)) {
            printf("Sygnał %d wystąpił w ciągu pierwszych 15 sekund.\n", i);
        }
    }

    // Odblokuj obsługę sygnałów
    sigprocmask(SIG_UNBLOCK, &blocked_signals, NULL);

    printf("Obsługa sygnałów odblokowana.\n");

    return 0;
}



/*int main(int argc, char** argv){
    sigset_t *sigmask;
    sigemptyset(sigmask);
    sigaddset(sigmask, SIGINT);
    sigaddset(sigmask, SIGQUIT);
    sigprocmask(SIG_BLOCK, sigmask, NULL);
    int time=0;
    sigset_t *pending;
    //sigemptyset(pending);
    while(1){
        printf("Cześć, tu proces %d\n", getpid());
        sleep(1);
        time++;
        if(time==15){
            sigpending(pending);
            if(sigismember(pending, SIGINT))
                printf("Wystąpił sygnał SIGINT\n");
            if(sigismember(pending, SIGQUIT))
                printf("Wystąpił sygnał SIGQUIT\n");
            sigprocmask(SIG_UNBLOCK, sigmask, NULL);
        }
    }
    if(sigpending(pending)){
        printf("Błąd funkcji sigpending\n");
        exit(1);
    }
    if(sigismember(pending, SIGINT))
        printf("Wystąpił sygnał SIGINT\n");
    if(sigismember(pending, SIGQUIT))
        printf("Wystąpił sygnał SIGQUIT\n");
    sigprocmask(SIG_UNBLOCK, sigmask, NULL);
    return 0;
}*/