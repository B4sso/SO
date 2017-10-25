#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

const int BUFSIZE = 10;
const char BUFA[] = "Eseguo A\n"; //Essendo costante, il buffer non subisce flush.
const char BUFB[] = "Eseguo B\n";
const int IDA = 0; //Identificativo processo A "Producer"
const int IDB = 1; //Identificativo processo B "Consumer"

static int pnew(void);
static int* shmake(void);
void producer(int*[],int*,int*,int);
void consumer(int*[],int*,int*,int);

/*
    Il programma deve generare due processi pA e pB.
    Il processo pA "Produttore" dovrà aggiornare la variabile condivisa int buffer a buffer+1
    Il processo pB "Consumatore" dovrà aggiornare la variabile condivisa int buffer a buffer-1
    
    
    Il risultato atteso dovrà essere:
    
    Eseguo A
    Contatore: 1
    
    Eseguo B
    Contatore: 0
    
    etc..
    
    
    Il problema è che senza controllo sulla postcondizione (ovvero il valore di flag == true)
    se il processo B dovesse essere eseguito per primo, avremo un risultato del tipo:
    
    Eseguo B
    Contatore: -1
    
    Eseguo B
    Contatore: -2
    
    Eseguo B
    Contatore: -3
    
    ....
    
    Eseguo B
    Contatore: -n
    
    Eseguo A
    Contatore: -n + 1
    
    Eseguo A
    Contatore: -n + 2
    
    .....
    
    Eseguo A
    Contatore: 1
    
    Eseguo B
    Contatore: 0
    
    Eseguo A
    Contatore: 1
    
    Eseguo B
    Contatore: 0
        
    etc..
    
    
    Come mai? C'è mutua esclusione ed attesa limitata, ma la legge del progresso non viene rispettata.

*/




int main (int argc, char* argv[])
{
    pid_t pA,pB;
    int flag = (argc > 1);
    int* shm_pointer = shmake(); //Alloca ed inizializza una porzione di memoria condivisa a 0int
     /*
    		Per registrare il turno e lo  stato REDY\NOT READY  dei processi
    	  	partiziono la memoria condivisa in più settori logici, dove:
    		  |TURN: Logica booleana di permesso d'entrata in sez. critica.
    	      |READY[2]: Richiesta d'entrata nella sezione critica, dove
		  	 		READY[IDA] = TRUE significa che il processo A
		  	 					  vuole entrare in sezione critica.
	  	      |BUFFER: Logica binaria
    
    */
    													  	 
    int* ready[2] ={&(shm_pointer[0]),&(shm_pointer[1])};													 
    int* turn = &(shm_pointer[2]);
    int* buffer = &(shm_pointer[3]);
    if ((pA = pnew()) == 0) producer (ready,turn,buffer,flag);
    else
    {
      if ((pB = pnew()) == 0) 
      {
        consumer(ready,turn,buffer,flag);  
      }
        else
        {
            
            fprintf(stderr,"Ciao, sono un processo che non avrebbe dovuto terminare. ID: %c\n",(wait(NULL) == pA)?('A'):('B'));
            fprintf(stderr,"Ciao, sono un processo che non avrebbe dovuto terminare. ID: %d\n",(wait(NULL) == pA)?('A'):('B'));    
            return 0;
        }
    
    }
}

static int* shmake(void)
{
    int segment_id = shmget (IPC_PRIVATE,512,S_IRUSR|S_IWUSR);
    int* shm_pointer = (int*) shmat(segment_id,NULL,0);
    for (int i = 0; i<10; i++) shm_pointer[i] = 0;	
	return shm_pointer;
}

static int pnew(void)
{
    pid_t temp = fork();
    if (temp < 0) 
    {
        fprintf(stderr,"Creazione processo fallita.\n");
        abort();
    }

}

void producer(int*ready[],int*turn,int*buffer,int flag)
{
    do{
    *ready[IDA] = 1;
    *turn = IDB;
    while (*ready[IDB] == 1 && *turn == IDB && *buffer > 0);
    if (flag)
     if (*buffer > 0)
        {
            *ready[IDA] = 0;
            continue;
        }
    *buffer = *buffer + 1; //Produttore-Consumatore viene implementato con una logica binaria.
    printf(BUFA); //Non c'è problema di flushing, dato che il processo concorrente non metterà in buffer nulla prima che ready[IDA] sia 0
    printf("Contatore: [%d]\n\n",*buffer);
    *ready[IDA] = 0;  // ERRORE ready era scritto come ready[IDA] = 0. Azzeravo la variabile puntatore.
                        //Sono una capra.    
    }while(1);
}


void consumer(int*ready[],int*turn,int*buffer,int flag)
{
    do{
    *ready[IDB] = 1;
    *turn = IDA;
    while (*ready[IDA] == 1 && *turn == IDA);
    if (flag)
     if (*buffer <= 0)
        {
            *ready[IDB] = 0;
            continue;
        }
    *buffer = *buffer -1;
    printf(BUFB);
    printf("Contatore: [%d]\n\n",*buffer);
    *ready[IDB] = 0;
    }while(1);
}









