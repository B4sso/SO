#include <stdio.h>
#include <stdlib.>
#include <unistd.>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
//exec reinizializza il text segment con il programma che verrà chiamato
/*
	Un processo che chiama l'exec viene rimpiazzato dal nuovo programma.
	Il pid rimane lo stesso.
	
		l (lista di argomento)
		execlp,execl .. richiede un puntatore null a fine argomenti
			
		p (indica un vettore di argomenti)
		prende un file dal PATH. Se il file è assente, allora bisogna indicare il pathname completo del file
		
		e (array al posto di path)
		envp array invece di usare l'enviroment
		
int execl (const char*path,const char*arg0,....,(char*)0)

execl("/bin/echo","echo","la","capra","campa",NULL);
				   Il primo argomento viene ignorato (è come se scrivessimo nella shell "echo")
				   
printf("ayy") <--- non viene mai eseguito

	PRINTA A SCHERMO: la capra campa
	
execlp("echo","echo","ayy","lmaoo",NULL);


SEGNALE: è un interrupt software che permette di gestire eventi asincroni.
		CTRL C genera un segnale diinterruzione, gestito dal sistema operativo, che killa il processo
		correntemente in esecuzione sulla shell.
		
		Ogni segnale ha un nome che inizia con SIG
		Ad ogni segnale corrisponde ad un int > 0
		
		Chi riceve il segnale, non ha idea di cosa o chi l'abbia inviato. Vi sono azioni di default
		che vengono processate ad ogni segnale.
		

		IGNORARE IL SEGNALE: (Tutti tranne 2 possono essere ignorati: SIGKILL e SIGSTOP)
		
		CATTURARE IL SEGNALE.
		
		
		SIGABRT (il processo che la genera termina abnormalmente)
		SIGCHLD (corrisponde al pid del processo terminato)
		SIGCONT (continua un processo fermo)
		SIGFPE (Ex: quando proviamo a fare una divisione per 0)
		SIGILL (istruzione illegale, ex floating point senza hardware con la virgola)
		SIGINT (quando viene terminato in runtime il processo)
		SIGALRM (da systemcall alarm)
		SIGSEGV (indirizzo fuori dal suo spazio indirizzi)
		SIGSTOP
		SIGKILL
		SIGTERM (da kill)
		SIGUSER1,SIGUSR2
		(definiti dall'utenti. utilizzati in maniera impropria per la ipc)
		
void (*signal(int signo,void(*func)(int)))(int);


SIG_ERR se errore
il puntatore al gestore se OK
*/

		
		
		
		
		
		
		
		

