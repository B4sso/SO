#include <stdio.h>
#include <stdlib.h>
#include "newShm.h"
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/ipc.h> //Libreria mancante


		// SHARED MEMORY CONTROL BLOCK (scb)
		 /*
			Permette una certa implementazione di polimorfismo
			 TYPE: INT - 0, CHAR 1, FLOAT 2	, ITEM 3
			 SEGMENT_ID: generato dal sistema tramide smhget
		  */
typedef int item;
struct scb {
	int type;
	int nelem;
	int segment_id;
}scb;

static int generateId (int);

shm newShm (int type,int nelem)
{
	if (type > 3 || type < 0)
	{
		fprintf(stderr,"Parametro idx0 non riconosciuto");
		return NULL;
	}
	shm tempBlock = malloc ( sizeof(struct scb));	
	if (tempBlock == NULL)
	{
		fprintf(stderr,"Blocco non allocato");
		return NULL;
	}

	int temp_segment_id;
	int temp_size;
	switch(type)
	{
		case INT:
		temp_size = (sizeof(int)) * nelem;
		temp_segment_id = generateId(temp_size);
		break;
		
		case FLOAT:
		temp_size = (sizeof(float)) * nelem;
		temp_segment_id = generateId(temp_size);
		break;

		case CHAR:
		temp_segment_id = generateId(nelem);
		break;

		case ITEM:
		temp_size = (sizeof(item)) * nelem;
		temp_segment_id = generateId(temp_size);
		break;

		default: break;
	}
	tempBlock->type = type;
	tempBlock->nelem = nelem;
	tempBlock->segment_id = temp_segment_id;
	return tempBlock;

}

static int generateId (int size)
{
	if (size <= 0) return -1; //la dimensione del segmento deve essere > 0 
	int segment_id; //id segmento
	segment_id = shmget(IPC_PRIVATE,size,S_IRUSR|S_IWUSR); //composizione riferimento
	return segment_id;
}
