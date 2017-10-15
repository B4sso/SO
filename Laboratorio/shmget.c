#include <stdio.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h> //Libreria mancante

int main()
{
	int segment_id; //id segmento
	char* shared_memory; //puntatore al segmento
	const int size = 4096; // dimensione segmento

	segment_id = shmget(IPC_PRIVATE,size,S_IRUSR|S_IWUSR);
	/*
		int shmget(key_t key, size_t size, int shmflg); 

             shm_perm.cuid and shm_perm.uid are set to the effective user
              ID of the calling process.

              shm_perm.cgid and shm_perm.gid are set to the effective group
              ID of the calling process.

              The least significant 9 bits of shm_perm.mode are set to the
              least significant 9 bit of shmflg.

              shm_segsz is set to the value of size.

              shm_lpid, shm_nattch, shm_atime, and shm_dtime are set to 0.

              shm_ctime is set to the current time.
		
		Le macro S_IRUSR | S_IWUSR semplicemente definiscono la sezione permessi dei bit
		di controllo del riferimento che si andrà a generare, abilitando lettura e scrittura
		IL BITWISE OR serve a sommare le macro a livello bit, così da avere una flag in grado
		di abilitare sia lettura che scrittura.

	*/

	shared_memory = (char*) shmat(segment_id,NULL,0); // annessione segmento
	sprintf(shared_memory,"Hi :D");
	shmdt(shared_memory); //Elimina il segmento dallo spazio indirizzi
	shmctl (segment_id,IPC_RMID,NULL); //Elimina il segmento dal sys

	return 0;
}
