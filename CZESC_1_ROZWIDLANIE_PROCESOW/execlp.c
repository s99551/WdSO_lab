#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv){
    printf("Wykonuję polecenie za pomocą funkcji system()\n");
    system("echo Pośpię sobie chwileczkę");
    system("sleep 10");
    printf("Polecenie wywołane za pomocą system() zakończyło się\n");
    printf("Wykonuję polecenie za pomocą funkcji execlp()\n");
    //execlp("sh","sh","-c","echo Pośpię sobie chwileczkę && sleep 10",NULL);
    //execlp("sh","sh","-c","sleep 10",NULL);

    __pid_t child = fork(); // po wywolaniu funkcji execlp() program konczy dzialanie dlateho nalezy utworzyc proces potomny
    switch (child)
    {
    case -1:
        printf("Błąd tworzenia procesu potomnego\n");
        exit(1);
        break;
    case 0:
        execlp("sh","sh","-c","echo Pośpię sobie chwileczkę && sleep 10",NULL);
        printf("Błąd funkcji execlp()\n");
        exit(1);
    default:

        break;
    }
    wait(NULL); // czekanie na zakonczenie procesu potomnego
    printf("Polecenie wywołane za pomocą execlp() zakończyło się\n"); // komunikat wyswietla sie po zakonczeniu dzialania funkcji execlp()
    return 0;
}