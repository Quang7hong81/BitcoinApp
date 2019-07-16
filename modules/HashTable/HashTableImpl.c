#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTableTypes.h"
#include "HashFun.h"
#include "DoubleListInterface.h"
#define INIT_SIZE 27

DataType data={NULL,NULL};

void Data(HTItem Item,HTKey Key)
{
	data.Item=Item;
	data.Key=Key;
}

HTHash HTCreate(Hash_NewNode NewNode,Hash_FreeNode FreeNode)
{
	HTHash HashTable;
	int i;

	HashTable=malloc(sizeof(struct hashtable));
	HashTable->Table=malloc(INIT_SIZE*sizeof(HTList));
	HashTable->Count=0;
	HashTable->MaxLength=INIT_SIZE;
	HashTable->LFactor=0.0;
	HashTable->FreeNode=FreeNode;
	HashTable->NewNode=NewNode;

	for(i=0; i<INIT_SIZE; i++)
	{
		HashTable->Table[i]=NULL;
	}

	return HashTable;
}

int HTSize(HTHash Hash)
{
	return Hash->Count;
}

Boolean HTGet(HTHash Hash,HTKey Key, HTItem *Item)
{
	ListNode node=NULL;
	data.Item=NULL;
	data.Key=Key;

	//Get the hash position of the key-item
	int position;
	position=HashF(Hash,Key);
	//Now that we have the position we must find the node in the position
	if(!ListIsEmpty(Hash->Table[position]))
	{
		if((node=ListSearch(Hash->Table[position],data,compare))!=NULL)
		{
			//if found return true and change the item pointer to point at the item of the node
			*Item=ListGetItem(node);
			
			return True;
		}
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
		Data(Item,Key); //initiallize the global variable "data"
		//Now hash the key using the function HashKey
		int position;
		position=HashF(Hash,Key);

		//Then we can create a list if it doesn't exist
		//or just add the node to the existing list of the position in the table

		//Check if the position is empty 
		if(Hash->Table[position] == NULL)
		{
			Hash->Table[position]=ListCreate(Hash->NewNode,Hash->FreeNode);	
		}
		if(ListSearch(Hash->Table[position],data,compare) == NULL)//if the item does not exist in the list add it
			ListInsertLast(Hash->Table[position],&data);

		Hash->Count++;
		SetLFac(Hash);
		if(0.6 - Hash->LFactor < 0.0)
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
		ListNode node=NULL;
		data.Item=NULL;
		data.Key=Key;
		//re-hash so the position of the key is found 
		int position;
		position=HashF(Hash,Key);
		
		//Now we have to search for the key in the list so we call a search function from the list module
		//and we delete the node it returns to us
		if(!ListIsEmpty(Hash->Table[position])){
			if((node=ListSearch(Hash->Table[position],data,compare)) != NULL)
			{
				ListRemove(Hash->Table[position],node);
				Hash->Count--;
			}
		}
		
	}
}



void HTVisit(HTHash Hash,Visit visit)
{
	int i;
	ListNode node;
	for(i=0; i<Hash->MaxLength; i++)
	{
		printf("Position %d : ",i );
		if(!ListIsEmpty(Hash->Table[i]))
		{
			node=ListGetHead(Hash->Table[i]);
			visit(Hash->Table[i],ListGetKey(node),ListGetItem(node));
		}
		else
		{
			printf("Empty\n");
		}
	}

}

void HTDestroy(HTHash Hash)
{
	int i;
	for(i=0; i<Hash->MaxLength; i++)
	{
			ListDestroy(Hash->Table[i]);
	}
	free(Hash->Table);
	free(Hash);
	//Also free the values of the data variable

}
