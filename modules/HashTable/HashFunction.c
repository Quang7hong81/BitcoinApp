#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableTypes.h"
#include "HashTableInterface.h"
#include "../List/DoubleListInterface.h"
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

//This function checks if we have to rehash the table and rehashes it if needed
void Rehash(HTHash Hash)
{
	int i,prevMax;
	HTList *tempTable;
	ListNode cur;
	tempTable=Hash->Table;
	prevMax=Hash->MaxLength;
	
	Hash->MaxLength=2*prevMax;
	//Create a new table twice the length of the previous one
	Hash->Table=malloc(Hash->MaxLength*sizeof(HTList));

	for(i=0; i<Hash->MaxLength; i++) Hash->Table[i]=NULL;
	//Now we must reHash the table for every item on it
	Hash->Count=0;
	for(i=0; i<prevMax; i++)
	{
		if(!ListIsEmpty(tempTable[i]))
		{
			cur=ListGetHead(tempTable[i]);
			while(cur!=NULL)
			{
				HTInsert(Hash,cur->Data.Key,cur->Data.Item);
				cur=ListGetNext(cur);
			}
		}
		ListDestroy(tempTable[i]);
	}

	free(tempTable);
}

