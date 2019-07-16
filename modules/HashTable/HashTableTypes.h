#pragma once
typedef void* HTItem;
typedef char* HTKey;
typedef struct data_type{
	HTItem Item;
	HTKey Key;
}DataType;

typedef struct hashtable *HTHash;

int compare(DataType A, DataType B);
typedef void (*VisitList)(DataType data);

typedef enum{False,True} Boolean;
#ifndef LIST_HASH
#define LIST_HASH
#include "DoubleListTypes.h"
#endif
typedef List_NewNode Hash_NewNode;
typedef List_FreeNode Hash_FreeNode;

typedef List HTList;
typedef void(*Visit)(HTList HTHash,HTKey Key,HTItem Item);
struct hashtable{
	HTList *Table;
	float LFactor;
	int Count;
	int MaxLength;
	Hash_FreeNode FreeNode;
	Hash_NewNode NewNode;
};
