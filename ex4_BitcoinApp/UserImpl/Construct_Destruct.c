#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructTypes.h"
#include "HashTableTypes.h"
#include "DoubleListTypes.h"
#include "types_BT.h"
#include "HashTableInterface.h"
#include "DoubleListInterface.h"
#include "BTInterface.h"
int compare (DataType A, DataType B)
{
	return strcmp(A.Key,B.Key);
}
ListNode NEW_Tree(DataType *data)
{
	ListNode newNode;
	newNode=malloc(sizeof(struct listnode));

	newNode->Data.Key=malloc(strlen(data->Key)+1);
	strcpy(newNode->Data.Key,data->Key);

	newNode->Data.Item=data->Item;

	newNode->Next=newNode->Prev=NULL;
	return newNode;
}

void FREE_Tree(ListNode Node)
{
	if(!End)
	{
		free(Node->Data.Key);
		free(Node);
	}
	else
	{
		free(Node->Data.Key);
		BTDestroy((BinaryTree) Node->Data.Item); //since we've reached the termination stage we must clear all the memory from the tree
		free(Node);
	}
}
////////////////////////
ListNode NEW_List(DataType *data)
{
	ListNode newNode;
	newNode=malloc(sizeof(struct listnode));

	newNode->Data.Key=malloc(strlen(data->Key)+1);
	strcpy(newNode->Data.Key,data->Key);

	newNode->Data.Item=data->Item; //just pass the already created list as an item 
	
	newNode->Next=newNode->Prev=NULL;
	return newNode;
}
void FREE_List(ListNode Node)
{
	if(!End)
	{
		free(Node->Data.Key);
		free(Node);
	}
	else
	{
		//The Key of the list is a string so free it
		free(Node->Data.Key);
		//The item of the node is another list so free it 
		ListDestroy(Node->Data.Item); //Free the list of BTNodes
		free(Node);
	}
}
///////////////////////////
ListNode NEW_Transaction(DataType *data)
{
	ListNode newNode;
	newNode=malloc(sizeof(struct listnode));

	newNode->Data.Key=malloc(strlen(data->Key)+1);
	strcpy(newNode->Data.Key,data->Key);

	newNode->Data.Item=data->Item; //We allocated the memory for the transaction struct in ourselves

	newNode->Next=newNode->Prev=NULL;
	return newNode;
}

void FREE_Transaction(ListNode Node)
{
	if(!End)
	{
		free(Node->Data.Key);
		free(Node);
	}
	else
	{
		free(Node->Data.Key);
		Transaction *trans=Node->Data.Item;
		ListDestroy(trans->Details);
		free(Node->Data.Item);
		free(Node);
	}
}
ListNode NEW_BTNode(DataType *data)
{
	ListNode newNode;
	newNode=malloc(sizeof(struct listnode));

	newNode->Data.Key=malloc(strlen(data->Key)+1);
	strcpy(newNode->Data.Key,data->Key);

	newNode->Data.Item=data->Item; //We allocated the memory for the transaction struct in ourselves

	newNode->Next=newNode->Prev=NULL;
	return newNode;
}
void FREE_BTNode(ListNode Node)
{
	//The data.item part is a BTNode that'll be deleted by the BTDestroy
	free(Node->Data.Key);
	free(Node);
}