#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "DoubleListTypes.h"

List ListCreate(List_NewNode NewNode,List_FreeNode FreeNode)
{
	List myList;
	myList=malloc(sizeof(struct listheader));

	myList->Head=NULL;
	myList->Tail=NULL;
	myList->ElemCount=0;
	myList->FreeNode=FreeNode;
	myList->NewNode=NewNode;

	return myList;
}

ListNode ListGetHead(List list)
{
	return list->Head;
}

ListNode ListGetTail(List list)
{
	return list->Tail;
}

ListNode ListGetNext(ListNode node)
{
	if(node) return node->Next;

	return NULL;
}

Boolean ListIsEmpty(List list)
{
	if(list!=NULL)
	{
		if(list->Head==NULL){ 
			return True;
		}
		else{ 
			return False;
		}
	}
	//If the list is not even created then we return False since we dont have a list yet
	return True;
}

ListNode ListSearch(List list, DataType data, Compare compare)
{
	if(!ListIsEmpty(list))
	{
		ListNode cur;
		cur=list->Head;
		while(cur!=NULL)
		{
			if(!compare(cur->Data,data)){
				return cur;
			}

			cur=cur->Next;
		}
	}
	//At this point the loop pis completed and the item was not found
	return NULL;
}

void ListInsertLast(List list, DataType *data)
{
	ListNode cur;
		list->ElemCount++;
		if(list->Head==NULL)
		{
			list->Head=list->NewNode(data);
			list->Tail=list->Head;
		}
		else
		{
			cur=list->Tail;

			//add a node at the end of the list
			cur->Next=list->NewNode(data);
			//make it the tail of the list
			list->Tail=cur->Next;
			//set the newNode's prev pointer properly
			list->Tail->Prev=cur;
		}
}

void ListInsertFirst(List list,DataType *data)
{
	list->ElemCount++;
	
		if(ListIsEmpty(list))
		{
			list->Head=list->NewNode(data);
			list->Tail=list->Head;
		}
		else
		{
			ListNode newNode;
			newNode=list->NewNode(data);
			//link the newNode before the head of the list
			newNode->Next=list->Head;
			//link the previous head with the newNode properly
			list->Head->Prev=newNode;
			//make the newNode Head of the list
			list->Head=newNode;
		}
	
}

void ListRemoveLast(List list)
{
	if(!ListIsEmpty(list))
	{
		ListNode cur,prev;
		cur=list->Tail;
		prev=cur->Prev;
		list->ElemCount--;
		
		//Check if cur is head of the list
		if(list->Head==cur)
		{
			list->Head=NULL;
		}
		else
		{
			prev->Next=NULL;
		}
		list->Tail=prev; //if prev is NULL(only one node in list) then we go empty
						 //else we just shorten the list by one node at the end and move the list's tail one node back
		list->FreeNode(cur);
	}
}

void ListRemoveFirst(List list)
{
	if(!ListIsEmpty(list))
	{
		ListNode cur,next;
		list->ElemCount--;

		cur = list->Head;
		next=cur->Next;
		if(cur==list->Tail) //if we only have one to the list then delete it and set tail and head to empty
		{
			list->Tail=NULL;
		}
		else //else we just set the Prev pointer of the second to the head node to NULL
		{
			next->Prev=NULL;
		}
		list->Head=next;
		list->FreeNode(cur);
	}
}

void ListRemove(List list, ListNode node)
{
	ListNode prev,next;

	if(node)
	{
		if(node==list->Head) ListRemoveFirst(list);
		else if(node==list->Tail) ListRemoveLast(list);
		else
		{
			prev=node->Prev;
			next=node->Next;

			prev->Next=next;
			next->Prev=prev;

			///Now that we dettached the node from the list we can delete it
			list->FreeNode(node);
		}
	}
}

void ListChange(List list, ListNode node,DataType newData)
{
	if(node){
		free(node->Data.Item);
		free(node->Data.Key);

		node->Data.Item=malloc(strlen(newData.Item)+1);
		strcpy(node->Data.Item,newData.Item);
		
		node->Data.Key=malloc(strlen(newData.Key)+1);
		strcpy(node->Data.Key,newData.Key);
	}
}

ItemType ListGetItem(ListNode node)
{
	if(node) return node->Data.Item;
	return NULL;
}

KeyType ListGetKey(ListNode node)
{
	if(node) return node->Data.Key;
	return NULL;
}


void ListPrint(List list, VisitList visitNode)
{
	ListNode cur;
	if(list!=NULL)
	{
		cur=list->Head;
		while(cur!=NULL)
		{
			visitNode(cur->Data);
			cur=cur->Next;
		}

		printf("\n");
	}
}

void ListDestroy(List list)
{
	ListNode cur,next;
	if(list!=NULL)
	{
		cur=list->Head;
		while(cur!=NULL)
		{
			next=cur->Next;
			list->FreeNode(cur);
			cur=next;
		}

		free(list);
	}
}