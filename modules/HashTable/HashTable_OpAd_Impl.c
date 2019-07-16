#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableTypes_OpAdr.h"
#include "HashFun.h"
#define INIT_SIZE 27
/*
void Data(DataType *data,HTItem Item,HTKey Key)
{
	
	if(isString==1)
	{
		char *item;
		item=malloc(strlen(Item)+1);
		strcpy(item,Item);
		data->Item=item;
	}
	else
	{
		data->Item=malloc(sizeof(Item));
		data->Item=memcpy(data->Item,Item,sizeof(Item));
	}

	data->Key=malloc(strlen(Key)+1);
	strcpy(data->Key,Key);
}
*/
HTHash HTCreate(Hash_NewNode NewNode,Hash_FreeNode FreeNode)
{
	HTHash HashTable;
	int i;
	HashTable=malloc(sizeof(struct hashtable));
	HashTable->Table=malloc(INIT_SIZE*sizeof(DataType));
	HashTable->Visited=malloc(INIT_SIZE*sizeof(int));
	HashTable->Count=0;
	HashTable->MaxLength=INIT_SIZE;
	HashTable->LFactor=0.0;
	HashTable->NewNode=NewNode;
	HashTable->FreeNode=FreeNode;

	for(i=0; i<INIT_SIZE; i++)
	{
		HashTable->Table[i].Item=NULL;
		HashTable->Table[i].Key=NULL;
		HashTable->Visited[i]=0;
	}

	return HashTable;
}

int HTSize(HTHash Hash)
{
	return Hash->Count;

}

Boolean HTGet(HTHash Hash,HTKey Key, HTItem *Item)
{
	//Get the hash position of the key-item
	int position;
	position=HashF(Hash,Key);

	while(Hash->Visited[position] == 1)
	{
		if(compare(Hash->Table[position].Key,Key) == 0)
		{
			*Item=Hash->Table[position].Item;
			return True;
		}
		//decrease the counter if the position of the table is occupied
		position--;

		if(position < 0) position=Hash->MaxLength-1;

		
	}
	return False;
}
void HTRemove(HTHash Hash,HTKey Key);

void HTInsert(HTHash Hash,HTKey Key,HTItem Item)
{
	HTItem item;
	if(HTGet(Hash,Key,&item) == True) HTRemove(Hash,Key);
	if(HTGet(Hash,Key,&item)==False)
	{
		int position;
		position=HashF(Hash,Key);

		while(Hash->Visited[position]==1)
		{
			//decrease the counter if the position of the table is occupied
			position--;

			if(position < 0) position=Hash->MaxLength-1;
		}

		//After the loop we ensured that the position is empty so we just place the item
		Hash->NewNode(&(Hash->Table[position]),Item,Key);
		Hash->Visited[position]=1;

		Hash->Count++;
		SetLFac(Hash);
		if(0.5 - Hash->LFactor < 0.0)
		{
			Rehash(Hash);
		}
	}
}

void HTRemove(HTHash Hash,HTKey Key)
{
	HTItem item;
	if(HTGet(Hash,Key,&item)==True)
	{
		int position,Found=0;
		position=HashF(Hash,Key);
		
		while(Hash->Visited[position]==1)
		{
			if(compare(Hash->Table[position].Key,Key) == 0)
			{
				Found=1;
				Hash->Visited[position]=0;
			
				Hash->FreeNode(&(Hash->Table[position])); 
				Hash->Table[position].Item=NULL; 
				Hash->Table[position].Key=NULL;

				Hash->Count--;
			}
			//decrease the counter if the posiiton of the table is occupied
			position--;

			if(position < 0) position=Hash->MaxLength-1;	
		}
	}
}


void HTVisit(HTHash Hash,Visit visit)
{
	int i;
	for(i=0; i<Hash->MaxLength; i++)
	{
		printf("Position %d : ",i );
		if(Hash->Visited[i] == 1)
		{
			visit(Hash,Hash->Table[i].Key,Hash->Table[i].Item);
		}
		printf("\n");
	}
}

void HTDestroy(HTHash Hash)
{
	int i;
	for (i=0; i<Hash->MaxLength; i++)
	{
		if(Hash->Visited[i]==1)
		{
			Hash->FreeNode(&(Hash->Table[i]));
		}
	}

	free(Hash->Table);
	free(Hash->Visited);
	free(Hash);
}