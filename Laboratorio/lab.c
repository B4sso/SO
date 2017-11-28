#include <sys/types.h>// Contiene le primitive system data types
			//La maggior parte di essi finisce in _t | ex: off_t, dev_t
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> 
			//pid_t getpid(void) -> pid_t: analogo di un intero, id processo
			//pid_t getppid(void) -> pid_t: id processo parent


/*
	wait - aspetta la terminazione di uno dei figli
	pid_t wait (int *statloc);
			|STATLOC: stato di terminazione del figlio terminato per primo.

	wait (NULL); se non utilizziamo la variabile di stato
	wait (&statloc); se utilizziamo la variabile di stato
*/
int main() {
pid_t a = fork();
pid_t b;
if (a > 0) 
	{
		b = fork();	
	}

if (a == 0)
	{
		int i;
		printf("PID A: %d \n",getpid());
		for (i=1;i<51;)
		{
			printf("[%d]",i);
			i++;
		}
		exit(0);
	} else
if (b == 0)
	{
		int i;
		printf("\nPID B: %d \n",getpid());// /n pulisce il buffer di output
		for (i=101;i<151;)
		{
			printf("[%d]",i);
			i++;
		}
		exit(0);

	}


wait(NULL);
wait(NULL);
printf("\n\nPADRE \n");
printf("Figlio A: %d\n",a);
printf("Figlio B: %d\n",b);

}

