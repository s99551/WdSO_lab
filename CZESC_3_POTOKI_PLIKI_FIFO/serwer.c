#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv){
    int i;
    for(i=0;i<10;++i){
        printf("Serwer: wysyłam linie nr %d\n", i);
        //sleep(1);
    }
    fflush(stdout);
    return(EXIT_SUCCESS);
}