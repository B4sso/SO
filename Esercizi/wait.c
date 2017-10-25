#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h>

const int BUFSIZE = 10;
const char BUFA[] = "Nonflushing ayylmaoo. Process A\n"; //Essendo costante, il buffer non subisce flush.
const char BUFB[] = "Nonflushing ayyylmaoo. Process B.\n";
const int IDA = 0; //Identificativo processo A "Producer"
const int IDB = 1; //Identificativo processo B "Consumer"

static int pnew(void);
static int* shmake(void);
void producer(int*[],int*,int*);
void consumer(int*[],int*,int*);

int main (int argc, char* argv[])
{
    pid_t pA,pB;
    int* shm_pointer = shmake(); //Alloca ed inizializza una porzione di memoria condivisa a 0int
    int* ready[2] ={&(shm_pointer[0]),&(shm_pointer[1])}; /*
    														Per registrare il turno e lo  stato REDY\NOT READY  dei processi
    													  	porziono la memoria in più settori logici, dove:
    													  	 |TURN: Logica booleana di permesso d'entrata in sez. critica.
    													  	 |READY[2]: Richiesta d'entrata nella sezione critica, dove
    													  	 		READY[IDA] = TRUE significa che il processo A
    													  	 					vuole entrare in sezione critica.
    													  	 |BUFFER: Contatore
    													  	 
    													  	*/
    int* turn = &(shm_pointer[2]);
    int* buffer = &(shm_pointer[3]);
    if ((pA = pnew()) == 0) producer (ready,turn,buffer);
    else
    {
      if ((pB = pnew()) == 0) 
      {
        printf("aspettooo");
        consumer(ready,turn,buffer);  
      }
        else
        {
            wait(NULL);  
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
        fprintf(stderr,"lol\n");
        exit(-1);
    }

}

void producer(int*ready[],int*turn,int*buffer)
{
    do{
    *ready[IDA] = 1;
    *turn = IDB;
    while (*ready[IDB] == 1 && *turn == IDB){printf("ayy");};
    *buffer = *buffer + 1;
    printf(BUFA); //Non c'è problema di flushing, dato che il processo concorrente non metterà in buffer nulla prima che ready[IDA] sia 0
    ready[IDA] = 0;      
    }while(1);
}


void consumer(int*ready[],int*turn,int*buffer)
{
    do{
    *ready[IDB] = 1;
    *turn = IDA;
     printf("%d",*ready[IDA]);
    while (*ready[IDA] == 1 && *turn == IDA ) {};
    *buffer = *buffer -1;
    printf(BUFB);
    *ready[IDB] = 0;
    }while(1);
}









