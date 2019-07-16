#pragma once
typedef struct listheader *List;
typedef struct listnode *ListNode;
typedef struct data_type DataType;
typedef ListNode (*List_NewNode)(DataType *data);
typedef void (*List_FreeNode)(ListNode Node);
struct listheader{
	ListNode Head;
	ListNode Tail;
	List_FreeNode FreeNode;
	List_NewNode NewNode;
	int ElemCount;
};
	#include "HashTableTypes.h"
	typedef HTItem* ItemType;
	typedef HTKey KeyType;

struct listnode{
	DataType Data;
	ListNode Next;
	ListNode Prev;
};

typedef int (*Compare)(DataType A, DataType B);
