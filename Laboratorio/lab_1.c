#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

#define A_IDX 0
#define B_IDX 1

int main() {
int segment_id; //Riferimento assoluto al segmento allocato
int* shared_memory;//Puntatore ad int che ospiterà il riferimento
const int size = 4*sizeof(int);//Size del segmento di memoria
segment_id = shmget (IPC_PRIVATE,size,S_IRUSR|S_IWUSR);//ID segmento

/*
	ESERCIZIO:
	Processo padre deve creare due processi figli (A,B) e rimanere in attesa del loro
	termine. Poi, stampa il pid_A (PROCESS ID PROCESSO A) ed il pid_B
	
	PROCESSO A: Deve stampare il pid_A e stampare i numeri da 0 a 50
	PROCESSO B: Deve stampare il pid_B e stampare i numeri da 101 a 150


	LOGICA DELLA SOLUZIONE:
	Dato che non ho idea di come sincronizzare i processi, A e B vengono organizzati
	in maniera gerarchica: 
				PADRE -> PROCESSO B -> PROCESSO A
	Nell'implementazione il padre rimane in attesa del solo processo B, mentre B rimane
	in attesa del processo A. Logicamente PADRE crea e rimane in attesa di due processi, quindi
	la traccia viene rispettata.
	
	PID_A e PID_B verranno immagazzinati in una porzione di memoria condivisa, dato che PID_A
	è trasparente a PADRE.

	

*/

pid_t b = fork();
if (b < 0)
	{
		fprintf(stderr,"Processo non generato.");
		exit(1);
	}
shared_memory = (int*) shmat(segment_id,NULL,0);
if (b == 0)
	{
		shared_memory[B_IDX] = getpid(); //La memorizzazione di PID B in shm
							// è ridondante
		pid_t a = fork();
		if (a < 0)
		{
			fprintf(stderr,"Processo non generato.");
			exit(2);
		}
		int i;
		if (a == 0) 
		{

			printf("PID A: %d \n",getpid());
			for (i=1;i<51;)
			{
				printf("[%d]",i);
				i++;
			}
			shared_memory[A_IDX] = getpid();
			exit(0);

	         } else {wait(NULL);}
		int *shared_memory = (int*) shmat(segment_id,NULL,0);
		printf("\nPID B: %d \n",getpid());// /n pulisce il buffer di output
		for (i=101;i<151;)
		{
			printf("[%d]",i);
			i++;
		}
		exit(0);

	}


wait(NULL);
printf("\n\nPADRE \n");
printf("ID PROCESSO A: %d \n",shared_memory[A_IDX]);
printf("\nID PROCESSO B: %d \n",shared_memory[B_IDX]);
shmdt(shared_memory); //Elimina il segmento dallo spazio indirizzi
shmctl (segment_id,IPC_RMID,NULL); //Elimina il segmento dal sys

}

