#pragma once
typedef void* HTItem;
typedef char* HTKey;
typedef struct hashtable *HTHash;

typedef struct {
	HTItem Item;
	HTKey Key;
}DataType;

typedef enum{False,True} Boolean;

typedef void (*Hash_NewNode)(DataType *data,HTItem Item, HTKey Key);
typedef void (*Hash_FreeNode)(DataType *data);
int compare(HTKey A, HTKey B);
typedef void(*Visit)(HTHash HTHash, HTKey Key,HTItem Item);

struct hashtable{
	DataType *Table;
	int *Visited;
	float LFactor;
	int Count;
	int MaxLength;
	Hash_FreeNode FreeNode;
	Hash_NewNode NewNode;
};