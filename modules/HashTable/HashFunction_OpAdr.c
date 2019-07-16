#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableTypes_OpAdr.h"
#include "HashTableInterface.h"

void SetLFac(HTHash Hash)
{
	float occupied;
	float length;
	occupied=(float)Hash->Count;
	length=Hash->MaxLength;

	Hash->LFactor=(float)occupied / length ;
}
//Hashing function
int HashF(HTHash Hash,HTKey Key)
{
	//We know that the key is a string so we will take advantage of it
	int max=Hash->MaxLength;
	int hashKey,i,pos,length;
	length=strlen(Key);
	hashKey=1;
	for(i=0; i<length; i++) hashKey=(hashKey*Key[i])%(max+length);
	pos = 0;
	for(i=0; Key[i]!='\0'; i++)
	{
	    pos = hashKey*(Key[i] + 1) % max;
	}


	return pos;
}

void Rehash(HTHash Hash)
{
	int i,prevMax;
	DataType *tempTable;
	int *prevVisited;

	tempTable=Hash->Table;
	prevMax=Hash->MaxLength;
	Hash->MaxLength=2*prevMax;

	//Create a new table twice the length of the previous one
	Hash->Table=malloc(Hash->MaxLength*sizeof(DataType));
	prevVisited=Hash->Visited;
	Hash->Visited=malloc(Hash->MaxLength*sizeof(int));
	
	Hash->Count=0;
	for(i=0; i<Hash->MaxLength; i++)
	{
		Hash->Table[i].Item=NULL;
		Hash->Table[i].Key=NULL;
		Hash->Visited[i]=0;
	}
	//Now we must reHash the table for every item on it
	for(i=0; i<prevMax; i++)
	{
		if(prevVisited[i]==1)
		{
			HTInsert(Hash,tempTable[i].Key,tempTable[i].Item);
			free(tempTable[i].Item);
			free(tempTable[i].Key);
		}
	}

	free(prevVisited);
	free(tempTable);

}