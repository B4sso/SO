#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

pid_t newp(void); /*	Per leggibilità, implementiamo la fork() in una funzione wrapper
				   *	che ci consentirà di gestirne gli errori in modo compatto.
				   */
int main()	
{
	pid_t A,B,C;
	A = newp();
	//A stampa il PID PROCESSO PADRE
	if (A == 0) printf("PID PROCESSO PADRE: %d\n",getppid()); //ERRORE: precedentemente era: getpid(). Svista.
	else{
			//B stampa PADRE.PID + B.PID
			B = newp();
			if (B == 0) printf("PADRE.PID + B.PID = %d\n",getppid() + getpid());
			else{
					//C stampa C.PID
					if (C == 0) printf("C.PID = %d\n",getpid());
						else{	
								/*
								* ERRORE: La prima versione implementava 3 x printf("messaggio %d",wait(NULL));
								* La traccia non richiedeva una stampa "FIFO": il padre avrebbe dovuto
								* attendere la terminazione di tutti e tre i processi figli per poi eseguire
								* l'ultima istruzione.									
								* L'output a video rimane invariato, con l'implementazione corrente di Ubuntu (data 10/2017).
								*/
								wait(NULL);
								wait(NULL);
								wait(NULL);

								printf("Figlio %d TERMINATO\n",A);
								printf("Figlio %d TERMINATO\n",B);
								printf("Figlio %d TERMINATO\n",C);
								return 0;
							}}}

}

pid_t newp(void)
{
	pid_t temp = fork();
	if (temp < 0) abort(); //Se temp < 0, abort verrà sempre eseguita sul padre
	return temp; //Se temp >= 0, ritorna.
}

