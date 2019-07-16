#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_BT.h"
#include "DoubleListTypes.h"
#include "DoubleListInterface.h"
#include "Construct_Destruct.h"
ListNode NEW_Int(DataType *data)
{
	ListNode newNode=malloc(sizeof(struct listnode));

	newNode->Data.Item=malloc(sizeof(int*));
	memcpy(newNode->Data.Item,data->Item,sizeof(data->Item));

	newNode->Data.Key=malloc(strlen(data->Key)+1);
	strcpy(newNode->Data.Key,data->Key);
	int* item=newNode->Data.Item;

	newNode->Prev=NULL;
	newNode->Next=NULL;

	return newNode;
}

void FREE_Int(ListNode Node)
{
	if(Node)
	{
		free(Node->Data.Item);
		free(Node->Data.Key);
		free(Node);
	}
}
//This code is specified and documented extensions That Help with various operations
static BTNode GetChildrenR(BTNode,List);
//One of them is to get all the Children for Bitcoin Owners Printing
List BTGetAllChildren(BinaryTree Tree)
{
	List Children=ListCreate(NEW_Int,FREE_Int); //Create the List

	//Now we will call a recursive function that will get us the children and add it to the List
	GetChildrenR(Tree->root,Children);

	return Children;
}
int stringCompare(DataType A, DataType B){return strcmp(A.Key,B.Key);}
static BTNode GetChildrenR(BTNode root,List Children)
{
	if(root==NULL) return NULL;

	if(root->left == NULL && root->right == NULL)
	{
		ListNode cur;
		//if the "root" left and right CHILDREN are NULL then its a leaf
		//so add it to the Children List
		DataType data;

		data.Key=root->item.UserID;
		if(root->item.Amount > 0)
		{
			if((cur=ListSearch(Children,data,stringCompare)) == NULL)
			{
				data.Item=&(root->item.Amount);
				ListInsertLast(Children,&data);
			}
			else
			{
				int *a=cur->Data.Item;
				*a= *a + root->item.Amount;
			}
		}
	}
	GetChildrenR(root->left,Children);
	GetChildrenR(root->right,Children);
}