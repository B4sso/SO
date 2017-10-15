#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define BUFSIZE	10  //Dimensione del buffer

void makeStuff();
void takeStuff();

int main(){
	int segment_id; //Riferimento assoluto al segmento allocato
	int* shared_memory;//Puntatore ad int che ospiterà il riferimento
	const int size = 1*sizeof(int);//Size del segmento di memoria
	pid_t producer,consumer;

	if ((producer = fork()) < 0)
		{
			fprintf(stderr,"Generazione processo PRODUCER non riuscita");
			exit(0);
		}

	if (producer == 0) //Se è il processo producer,esegui makeStuff
			makeStuff();

	if ((consumer = fork()) < 0)
		{
			fprintf(stderr,"Generazione processo CONSUMER non riuscita");
			exit(0);
		}

	if (consumer == 0) //Se è il processo producer,esegui makeStuff
			takeStuff();

	wait(NULL);
}


void makeStuff()
{
	shared_memory = (int*) shmat(segment_id,NULL,0);
	while(1)
	{
	if (counter == BUFSIZE-1) continue; //si blocca se il buffer è pieno
		//FAI QUALCOSA
	counter ++;
	printf("\n CREA C: [%d]\n",counter);
	}
}

void takeStuff()
{	
	while(1)
{
	shared_memory = (int*) shmat(segment_id,NULL,0);
	while (counter == 0); //si blocca se il buffer è vuoto
		//FAI QUALCOSA
	counter --;
	printf("\nPRESO C: [%d]\n",counter);

}
}
