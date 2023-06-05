#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//podstawowa wersja programu wyświetla cykliczne 3 napisy po naciśnięciu CTRL+C
//zakończenie programu CTRL+\ (SIGQUIT)

char napisy[4][80]={"Ha! Ha! Ha! To tylko sygnał powierzchowny!\n", 
"Tylko proces %d śmieje się sygnałowi %d prosto w twarz!\n", 
"Auć - to bolało!\n",
"Dobrze! Dobrze! Już kończę\n"};
int nr_napisu=0;

void obsluga_sig_int(int sig){
    printf(napisy[nr_napisu],getpid(),sig);
    nr_napisu=((nr_napisu+1)%3);
    sleep(4);
}

void obsluga_sig_quit(int sig){
    printf("Przywrocono normalną obsługę sygnału SIGINT\n");
    signal(SIGINT, SIG_DFL);
}

void obsluga_sig_alrm(int sig){
    printf("Ding! Ding! Ding! - Przywracam domyślną obsługę CTRL+C\n");
    signal(SIGINT, SIG_DFL);
}

void obsluga_sygnalow(int sig){
    if(sig==SIGINT)
        obsluga_sig_int(sig);
    if(sig==SIGQUIT)
        obsluga_sig_quit(sig);
    if(sig==SIGALRM)
        obsluga_sig_alrm(sig);
}

int main(int argc, char** argv){
    /*signal(SIGINT,obsluga_sig_int);
    signal(SIGQUIT, obsluga_sig_quit);
    signal(SIGALRM, obsluga_sig_alrm);*/

    struct sigaction act_int, act_quit, act_alrm;
    act_int.sa_handler = obsluga_sig_int;
    sigemptyset(&act_int.sa_mask);
    act_int.sa_flags = 0;
    sigaction(SIGINT, &act_int, 0);

    act_quit.sa_handler = obsluga_sig_quit;
    sigemptyset(&act_quit.sa_mask);
    act_quit.sa_flags = 0;
    sigaction(SIGQUIT, &act_quit, 0);

    act_alrm.sa_handler = obsluga_sig_alrm;
    sigemptyset(&act_alrm.sa_mask);
    act_alrm.sa_flags = 0;
    sigaction(SIGALRM, &act_alrm, 0);
    
    alarm(15);
    while(1){
        printf("Cześć, tu proces: %d\n", getpid());
        sleep(1);
    }
    return 0;
}