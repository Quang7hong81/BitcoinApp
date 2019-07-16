CFLAGS += -I$(MODULES)/HashTable/
CFLAGS += -I$(MODULES)/List/
CFLAGS += -I$(MODULES)/BinaryTree/

	OBJS += $(MODULES)/HashTable/HashFunction.o
	OBJS += $(MODULES)/HashTable/HashTableImpl.o
	OBJS += $(MODULES)/List/DoubleListImpl.o
	OBJS += $(MODULES)/BinaryTree/BTImplementation.o
	OBJS += $(MODULES)/BinaryTree/BTImpl_Insert.o
	OBJS += $(MODULES)/BinaryTree/BTImpl_Remove_Print.o	
	OBJS += $(MODULES)/BinaryTree/BT_extension.o
