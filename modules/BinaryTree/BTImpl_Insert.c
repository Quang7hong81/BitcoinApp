//###################################//
//          INSERT FUNCTIONS         //
//###################################//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_BT.h"

//function that will assign the data to the given node
void assignData(BTNode Node,BTItem item)
{
	Node->item.UserID=malloc(strlen(item.UserID)+1);
	strcpy(Node->item.UserID,item.UserID);

	Node->item.BitcoinID=malloc(strlen(item.BitcoinID)+1);
	strcpy(Node->item.BitcoinID,item.BitcoinID);

	Node->item.Amount=item.Amount;
}
//function that return "true" if the tree is empty and is used as an inside function in this file
static int isEmpty(BinaryTree Tree)
{
	return (Tree->elements==0);
}
//function that changes the item value of the node with the item value that we give
void BTChange(BinaryTree Tree,BTNode Node,BTItem Item)
{
	if(!isEmpty(Tree) && Node!=NULL)
	{
		assignData(Node,Item);
	}
}
//insert a root to the empty tree header
void BTInsertRoot(BinaryTree Tree,BTItem Item)
{
	BTNode newRoot;
	if(isEmpty(Tree))
	{
		Tree->elements++;
		//create the new root-node
		newRoot=malloc(sizeof(struct treenode));
		//initialize the values properly
		newRoot->left= newRoot->right= newRoot->parent=EMPTY;
		assignData(newRoot,Item);
		//make it the root of the tree structure
		Tree->root=newRoot;
	}
}
//function that creates a left child to the node that the user gives us
void BTInsertLeft(BinaryTree Tree,BTNode Node,BTItem Item)
{
	BTNode newNode;
	if(!isEmpty(Tree))
	{
		if(Node->left==EMPTY)
		{
			Tree->elements++;
			//create the new node
			newNode=malloc(sizeof(struct treenode));
			//initialize the values properly
			newNode->left= newNode->right= EMPTY;
			newNode->parent=Node;
			assignData(newNode,Item);
			//make it the left child of the Node
			Node->left=newNode;
		}
	}
}
//function that creates a right child to the node that the user gives us
void BTInsertRight(BinaryTree Tree,BTNode Node,BTItem Item)
{
	BTNode newNode;
	if(!isEmpty(Tree))
	{
		if(Node->right==EMPTY)
		{
			Tree->elements++;
			//create the new node
			newNode=malloc(sizeof(struct treenode));
			//initialize the values properly
			newNode->left= newNode->right= EMPTY;
			newNode->parent=Node;
			assignData(newNode,Item);
			//make it the right child of the Node
			Node->right=newNode;
		}
	}
}
