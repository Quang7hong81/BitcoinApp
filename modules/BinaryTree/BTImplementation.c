#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_BT.h"

//Create a BTS function
BinaryTree BTCreate(int maxelem)
{
	BinaryTree Tree;
	Tree=malloc(sizeof(struct BT));
	//initializing the extra data needed
	Tree->root=EMPTY; //the tree header is EMPTY
	Tree->elements=0;
	return Tree;
}
//Get the height of the tree recursively
int getHeightRecursively(BTNode root)
{
	int leftHeight,rightHeight;
	if(root==EMPTY)
		return 0;
	else
	{
		leftHeight=getHeightRecursively(root->left);
		rightHeight=getHeightRecursively(root->right);
	}

	if(leftHeight > rightHeight) return (leftHeight+1);
	else return (rightHeight+1);
}
int BTisNil(BTNode Node);
//get the height of the BST by calling the recursive function(see as following)
int BTHeight(BinaryTree Tree)
{
	BTNode root;
	int height;
	root=Tree->root;
	if(BTisNil(Tree->root)) 
	{
		return 0;
	}
	//recursively get the height of the tree
	height=getHeightRecursively(root);
	return height;
}
//Function that returns the number of the nodes 
int BTSize(BinaryTree Tree)
{
	return Tree->elements;
}
//function that return "true" if the tree is empty
int BTisNil(BTNode Node)
{
	return (Node==EMPTY);
}
//function that returns the root of the tree
BTNode BTGetRoot(BinaryTree Tree)
{
	return Tree->root;
}
//function that returns the parent of the given node (if it exists)
BTNode BTGetParent(BinaryTree Tree,BTNode Node)
{
	if(!BTisNil(Tree->root)) 
	{
		if(Tree->root != Node)
		{
			return Node->parent;
		}
	}
	return EMPTY;
}
//function that returns the nodes left child (if it exists)
BTNode BTGetChildLeft(BinaryTree Tree,BTNode Node)
{
	if(!BTisNil(Tree->root))
	{
		if(Node->left!=EMPTY)
		{
			return Node->left;
		}
	}
	return EMPTY;
}
//function that returns the nodes left child (if it exists)
BTNode BTGetChildRight(BinaryTree Tree,BTNode Node)
{
	if(!BTisNil(Tree->root))
	{
		if(Node->right!=EMPTY)
		{
			return Node->right;
		}
	}
	return EMPTY;
}
//get the item that the given node contains
BTItem BTGetItem(BTNode Node)
{
		if(Node!=NULL)
		{
			return Node->item;
		}
}
