#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define BUFSIZE	10  //Dimensione del buffer


/*
    RISULTATI TEST:
      Il processo PRODUCER viene schedulato in modo da iterare fino al raggiungimento
      di BUFSIZE-1, seguito dal CONSUMER che itera fino al raggiungimento di 0.
      
      Non c'è overlapping\race condition.
      La race condition è data dall scheduler.

*/




void makeStuff();
void takeStuff();


int main(){
	pid_t producer,consumer;
	int segment_id = shmget (IPC_PRIVATE,512,S_IRUSR|S_IWUSR);
    int *shared_memory = (int*) shmat(segment_id,NULL,0);
    shared_memory[0] = 0;
	if ((producer = fork()) < 0)
		{
			fprintf(stderr,"Generazione processo PRODUCER non riuscita");
			exit(0);
		}

	if (producer == 0) 
	{
	   makeStuff((int*) shmat(segment_id,NULL,0));	
	}
	if ((consumer = fork()) < 0)
		{
			fprintf(stderr,"Generazione processo CONSUMER non riuscita");
			exit(0);
		}
	if (consumer == 0) takeStuff((int*) shmat(segment_id,NULL,0));
	wait(NULL);
	wait(NULL);
}


void makeStuff(int* shared_memory)
{
	while(1)
	{
	    while(shared_memory[0] == BUFSIZE-1); //si blocca se il buffer è pieno
		    //FAI QUALCOSA
	    shared_memory[0] = shared_memory[0] + 1;
	    printf("\n CREA C: [%d]\n",shared_memory[0]);
	}
}

void takeStuff(int *shared_memory)
{	
	while(1)
    {
	    while (shared_memory[0] <= 0); //si blocca se il buffer è vuoto
	    shared_memory[0] = shared_memory[0] - 1;
	    printf("\nPRESO C: [%d]\n",shared_memory[0]);
    }
}
