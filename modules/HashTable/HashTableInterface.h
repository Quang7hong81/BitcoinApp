HTHash HTCreate(Hash_NewNode NewNode,Hash_FreeNode FreeNode);
int HTSize(HTHash Hash);
void HTInsert(HTHash Hash,HTKey Key,HTItem Item);
void HTRemove(HTHash Hash,HTKey Key);
Boolean HTGet(HTHash Hash,HTKey Key, HTItem *Item);
void HTVisit(HTHash Hash,Visit visit);
void HTDestroy(HTHash Hash);