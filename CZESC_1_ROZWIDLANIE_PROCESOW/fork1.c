#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char** argv[]){
	int id = fork(); // funkcja zwraca numer procesu rodzica
	//printf("Hello world from id: %d\n", id);

	if(id == -1){
		printf("Blad procesu rozwidlania\n");
		exit(1);
	}

	if(id==0){
		for(int i=0;i<5;i++){
			printf("Hello from child process ");
			printf("Process ID: %d parent ID: %d\n",getpid(), getppid());
			sleep(1);
		}
		exit(0);
	}
	else{
		printf("Hello from the main process ");
		printf("Process ID: %d parent ID: %d\n", getpid(), getppid());
		sleep(1);
		//exit(0); // zakonczenie dzialania procesu rodzica - tworzy sie proces osierocony o ppid=1
	}
	int status;
	//pid_t child_pid = waitpid(id, &status, WNOHANG); // przypisanie kodu zwroconego przez proces potommy do zmiennej status
	//pid_t child_pid = wait(&status); // rodzic czeka na zakonczenie procesu potomnego
	//printf("Proces potomny zostal zakonczony. Kod powrotu: %d\n", WEXITSTATUS(status)); // wyswietlenie kodu zakonczenia procesu potomnego
	while(!waitpid(id, &status, WNOHANG)){
		printf("Rodzic czeka na zakonczenie pracy potomka\n");
		sleep(1);
	}
	printf("Proces potomny zostal zakonczony. Kod powrotu: %d\n", WEXITSTATUS(status));
	return 0;
}
