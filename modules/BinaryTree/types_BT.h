#pragma once

struct itemstruct{
	char* UserID;
	char* BitcoinID;
	unsigned int Amount;
};
typedef struct itemstruct BTItem;
typedef struct treenode *BTNode;
typedef struct BT *BinaryTree;
//Declarations of the structures needed
struct treenode{
	BTItem item;
	struct treenode *left;
	struct treenode *right;
	struct treenode *parent;
};

struct BT{
	BTNode root;
	int elements;

};

typedef void(*visit)(BTNode Node);

#define STRING 0

#ifndef EMPTY
	#define EMPTY NULL
#endif
