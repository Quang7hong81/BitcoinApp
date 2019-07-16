#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types_BT.h"

static int isEmpty(BinaryTree Tree)
{
	return (Tree->elements==0);
}
//check for the relation between the parent and the Node-child
static int isLeft(BTNode parent,BTNode child)
{
	return (parent->left==child);
}
static int isRight(BTNode parent,BTNode child)
{
	return (parent->right==child);
}
//check if the node given is  a leaf
static int isLeaf(BTNode Node)
{
	return(Node->left==NULL && Node->right==NULL);
}
//Remove a leaf (function)
void BTRemove(BinaryTree Tree,BTNode Node)
{
	BTNode parent;
	if(!isEmpty(Tree))
	{
		if(isLeaf(Node))
		{
			Tree->elements--;
			//break the relationship between the parent and child node and then delete the second
			parent = Node->parent;
			if(parent!=NULL) //the only node with no parent is the root node
			{
				if(isRight(parent,Node)) 
					parent->right=NULL;
				else if(isLeft(parent,Node)) 
					parent->left=NULL; 
			}
			else
			{
				Tree->root=NULL;
			}
			#if STRING==1
				free(Node->item);
			#endif
			free(Node);
		}
	}
}
//recursive destructions of the nodes
void DeleteRec(BTNode root)
{
	if(root==NULL) return;
	DeleteRec(root->left);
	DeleteRec(root->right);
	
	free(root->item.UserID);
	free(root->item.BitcoinID);
	free(root);
}
//Destroy the tree recursively
void BTDestroy(BinaryTree Tree)
{
	BTNode root;

	root = Tree->root;

	DeleteRec(root);
	free(Tree);
	Tree=NULL;
}

//###################################//
//          PRINT FUNCTIONS          //
//###################################//
//visit Function
void Visit(BTNode Node)
{
	BTItem item=Node->item;
	printf("%s,%s,%d\n",item.UserID,item.BitcoinID,item.Amount );
}
//Recursive print of the trees
void PreOrderR (BTNode root,visit Visit)
{
	if(root==NULL) return;
	Visit(root);
	PreOrderR(root->left,Visit);
	PreOrderR(root->right,Visit);
}
void PostOrderR(BTNode root,visit Visit)
{
	if(root==NULL) return;
	PostOrderR(root->left,Visit);
	PostOrderR(root->right,Visit);
	Visit(root);
}
void InOrderR(BTNode root,visit Visit)
{
	if(root==NULL) return;
	InOrderR(root->left,Visit);
	Visit(root);
	InOrderR(root->right,Visit);
}
//Funcions that call the recursive printing functions
void BTPreOrder(BinaryTree Tree,visit Visit)
{
	if(isEmpty(Tree)) printf("Empty Tree\n");
	else PreOrderR(Tree->root,Visit);
	printf("\n");
}
void BTPostOrder(BinaryTree Tree,visit Visit)
{
	if(isEmpty(Tree)) printf("Empty Tree\n");
	else PostOrderR(Tree->root,Visit);
	printf("\n");
}
void BTInOrder(BinaryTree Tree,visit Visit)
{
	if(isEmpty(Tree)) printf("Empty Tree\n");
	else InOrderR(Tree->root,Visit);
	printf("\n");
}


void push(BTNode *nodes,BTNode cur, int *cnt)
{
	nodes[*cnt]=cur;
	(*cnt)++;
}

BTNode pop(BTNode *nodes,int *cnt)
{
	BTNode cur;

	cur=nodes[*cnt];
	(*cnt)++;
	return cur;
}
void BTLevelOrder(BinaryTree Tree,visit Visit)
{
	//we will use a queue in order to store the nodes of each level and then print it
	BTNode *nodes=malloc(sizeof(BTNode)*(Tree->elements+1));
	BTNode cur;
	int start,end,i;
	start=end=0;
	for(i=0; i<Tree->elements+1; i++) nodes[i]=NULL;
	if(isEmpty(Tree)) 
		printf("Empty Tree\n");
	else
	{
		push(nodes,Tree->root,&end);
		while((cur=pop(nodes,&start))!=NULL)
		{
			Visit(cur);
			if(cur->left!=NULL)
			{
				push(nodes,cur->left,&end);
			}
			if(cur->right!=NULL)
			{
				push(nodes,cur->right,&end);
			}
		}
	}
	free(nodes);
	printf("\n");
}
