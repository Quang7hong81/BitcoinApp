#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "StructTypes.h"
#include "HashTableTypes.h"
#include "DoubleListTypes.h"
#include "types_BT.h"
#include "Construct_Destruct.h"
#include "HashTableInterface.h"
#include "DoubleListInterface.h"
#include "BTInterface.h"
void Initialize(void)
{
	End=0;
	//We have included the new_item_constructor and node Destructor functions in the Construct_Destruct.h
	Bitcoins = HTCreate(NEW_Tree,FREE_Tree);
	Wallets = HTCreate(NEW_List,FREE_List); //This functions should just add a pointer to the node they take as an item so that we have immediate access to it
	SenderHash = HTCreate(NEW_List,FREE_List);//Transaction Hash (Key is the sender) (List of sender transactions)
	ReceiverHash = HTCreate(NEW_List,FREE_List);//Transaction Hash (Key is the receiver)(List of receiver transactions)
}
void CreateUser(char* UserID)
{
	//To create a user we must just add an empty wallet to the Wallets HashTable
	Wallet newWallet;
	newWallet=ListCreate(NEW_BTNode,FREE_BTNode);

	HTInsert(Wallets,UserID,newWallet);

}
void CreateBitcoin(char* BitcoinID,char* UserID,int Amount)
{
	//We must just create a new Empty Bitcoin Tree and then add it to the Bitcoins's Hash
	BitcoinTree newBitcoin;
	BTItem item;
	item.UserID=UserID;
	item.BitcoinID=BitcoinID;
	item.Amount=Amount;
	void* *wallet=malloc(sizeof(Wallet*));
	if(HTGet(Wallets,UserID,wallet)==True)
	{
		newBitcoin = BTCreate(1);
		BTInsertRoot(newBitcoin,item);

		HTInsert(Bitcoins,BitcoinID,newBitcoin);

		DataType data;
		data.Key=UserID;
		data.Item=BTGetRoot(newBitcoin);

		ListInsertLast(*wallet,&data);
	}
	else
	{
		printf("The user '%s' doesn't exist\n",UserID );
	}
	free(wallet);
}
int GetUserAmount(char* UserID)
{
	void* *userWallet=malloc(sizeof(List*)); // The item is a list of leaf bitcoin tree nodes
	int Balance=0;
	if(HTGet(Wallets,UserID,userWallet) == True)
	{
		if(!ListIsEmpty(*userWallet))
		{
			BTItem item;
			ListNode cur;
			cur=ListGetHead(*userWallet);
			
			do
			{
				void* node=ListGetItem(cur);//The item of the list is a BTNode
				item = BTGetItem(node);	//The item of the BTNode is the Bitcoin Part Details (userID,bitcoinID,Amount)
				Balance += item.Amount;
			}while((cur=ListGetNext(cur)) != NULL);
		}
	}
	free(userWallet);
	return Balance;
}
Boolean Transfer(char *fromUserID, char *toUserID, int Amount)
{
	int isValid=0;
	void* *sender=malloc(sizeof(Wallet*)),**receiver=malloc(sizeof(Wallet*));
	if(HTGet(Wallets,fromUserID,sender) == True && HTGet(Wallets,toUserID,receiver) == True)
	{
		//Both wallets exist now we got to check if the sender has enough money to make the transaction
		int senderAmount=GetUserAmount(fromUserID);

		//Now we just check the result of the subtraction of the two numbers
		if(Amount - senderAmount > 0) {free(sender); free(receiver);return False; }//If senderAmount < Amount to be sent then the transaction is invalid
		else isValid = 1;
	}

	if(isValid==1)
	{
		//We must do the transaction in parts we will create two new nodes in the sender tree 
		//and then if the amount of this bit coin aint enough ,procceed to another
		//At the same time we must delete the parent node from senders wallet and then Insert the new Nodes we created at the proper wallet 
		ListNode senderNode;
		senderNode=ListGetHead(*sender);
		Transaction *senderTrans=malloc(sizeof(Transaction));
		senderTrans->ID=1;
		senderTrans->Date=time(NULL);
		senderTrans->Details=ListCreate(NEW_BTNode,FREE_BTNode);

		Transaction *receiverTrans=malloc(sizeof(Transaction));
		receiverTrans->ID=1;
		receiverTrans->Date=1;
		receiverTrans->Details=ListCreate(NEW_BTNode,FREE_BTNode);
		DataType data;
		void* *bitcoin=malloc(sizeof(BinaryTree*));
		do
		{
			void* node;
			node=ListGetItem(senderNode);
			BTItem item=BTGetItem((BTNode) node),tempItem; 
			
			
			//Create the left node and add it to the bitcoin Tree and the toUser.Wallet
			if(Amount < item.Amount) tempItem.Amount=Amount;//The Amount is less than the amount if the first bitcoinPart the user possesses
			else tempItem.Amount=item.Amount;
			tempItem.BitcoinID=item.BitcoinID;
			tempItem.UserID=toUserID;
			
			if(HTGet(Bitcoins,item.BitcoinID,bitcoin) == True) BTInsertLeft(*bitcoin,node,tempItem);
			//Also add this node to the Wallet of toUser
			data.Item=BTGetChildLeft(*bitcoin,node);
			data.Key=toUserID;
			ListInsertLast(*receiver,&data);
			//Also add the "node" to the transasction node list of the receiver
			data.Item=node;
			data.Key=toUserID;
			ListInsertLast(receiverTrans->Details,&data);

			//Do the same for the right child 
			if(Amount < item.Amount) tempItem.Amount=item.Amount - Amount;//The Amount is less than the amount of the first bitcoinPart the user possesses
			else tempItem.Amount=0;
			tempItem.BitcoinID=item.BitcoinID;
			tempItem.UserID=fromUserID;
			if(HTGet(Bitcoins,item.BitcoinID,bitcoin) == True) BTInsertRight(*bitcoin,node,tempItem);
			//Now we must delete the parent Node from the Wallet and then Add the right node to it
			ListNode next=ListGetNext(senderNode);
			ListRemove(*sender,senderNode);
			data.Item=BTGetChildRight(*bitcoin,node);
			data.Key=fromUserID;
			ListInsertLast(*sender,&data);
			senderNode=next;
			data.Item=node;
			data.Key=fromUserID;
			//Also add the "node" to the transasction node list of the sender
			ListInsertLast(senderTrans->Details,&data);
			Amount-=item.Amount;
		}while(Amount>0);

		//Now we must include "node" BTNode to the sender's and receiver's transaction lists
		void* *list=malloc(sizeof(List*)); //List respresents the Transaction Lists list that it is used to store the transaction lists(i.e. a node of list: {ID,DateDetails})
		///////////////////////////TO BE CONTINUED//////NOT FINISHED/////////////////////////////////////////
		//Get the list of transactions for the sender(if it doesn't exist create one)
		if(HTGet(SenderHash,fromUserID,list) == False)
		{
			List TransactionList=ListCreate(NEW_Transaction,FREE_Transaction); //Create a newTransactionList is it doesn't exist
			HTInsert(SenderHash,fromUserID,TransactionList);
			HTGet(SenderHash,fromUserID,list);
		}
		//At this point list points to the proper senderTransactionsList so just add the "node" as another item of the list
		data.Item=senderTrans;
		data.Key=fromUserID;
		ListInsertLast(*list,&data);
			//Do the same for the Receiver of the Amount
		if(HTGet(ReceiverHash,toUserID,list) == False)
		{
			List TransactionList=ListCreate(NEW_Transaction,FREE_Transaction); //Create a newTransactionList is it doesn't exist
			HTInsert(ReceiverHash,toUserID,TransactionList);
			HTGet(ReceiverHash,toUserID,list);
		}
		//At this point list points to the proper senderTransactionsList so just add the "node" as another item of the list
		data.Item=receiverTrans;
		data.Key=toUserID;
		ListInsertLast(*list,&data);
		free(list);
		free(bitcoin);
	}
	free(sender);
	free(receiver);
	return True;
}
void VisitSent(DataType data)
{
	//data.Item is a BTNode
	BTNode node=data.Item;
	void* *Tree=malloc(sizeof(BinaryTree*));
	BTItem item=BTGetItem(node);
	printf("%s -> ",item.UserID );
	if(HTGet(Bitcoins,item.BitcoinID,Tree) == True) node = BTGetChildLeft(*Tree,node);
	//we now acknowledge the receiver which is the one that changes each time 
	item=BTGetItem(node);
	printf("%s : %d\n",item.UserID,item.Amount); 
	free(Tree);
}
void PrintSent(char* UserID)
{
	//we will search for the List of transactions in the senderHash and we will print : userSent->userReceived "amount"
	void* *senderTrans=malloc(sizeof(List*));
	if(HTGet(SenderHash,UserID,senderTrans) == True)
	{
		//If the transaction data exist then we got the transaction list
		ListNode cur;
		cur=ListGetHead(*senderTrans);

		do
		{
			Transaction *trans=cur->Data.Item;
			ListPrint(trans->Details,VisitSent);
		}while((cur=ListGetNext(cur)) != NULL);
	}
	free(senderTrans);
}
void VisitReceived(DataType data)
{
	BTNode node=data.Item;
	void* *Tree=malloc(sizeof(BinaryTree));
	BTItem item=BTGetItem(node);
	printf("%s -> ",item.UserID );
	if(HTGet(Bitcoins,item.BitcoinID,Tree) == True) node = BTGetChildLeft(*Tree,node);
	//we now acknowledge the sender which is the one that changes each time
	item=BTGetItem(node);
	printf("%s : %d\n",item.UserID,item.Amount); 
	free(Tree);
}

void PrintReceived(char* UserID)
{
	void* *receiverTrans=malloc(sizeof(List*));
	if(HTGet(ReceiverHash,UserID,receiverTrans) == True)
	{
		ListNode cur;
		cur=ListGetHead(*receiverTrans);

		
		do
		{
			Transaction *trans=cur->Data.Item;
			ListPrint(trans->Details,VisitReceived);
		}while((cur=ListGetNext(cur)) != NULL);
	}
	free(receiverTrans);
}

void PrintBitcoinOwners(char* BitcoinID) 
{
	//We got to get all the owners at the current state for the Given Bitcoin 
	//So we will get the BitcoinTree from the Bitcoins HashTable
	//Firstly we will create a list that we will place only the children of the bitcoin tree
	void **bitcoin=malloc(sizeof(BitcoinTree));
	
	if(HTGet(Bitcoins,BitcoinID,bitcoin) == True)
	{
		List CurrentState;
		//The item of the list will be pointers to BitcoinTree Nodes  
		//Now we will call a recursive function That will Save the Children Nodes of the Tree (extension to our Binary Tree Module) but wont keep replicas (sums up the Amounts)
		CurrentState=BTGetAllChildren(*bitcoin); 
		//Now we must print the list
		printf("BitcoinID:%s Owners: \n",BitcoinID );
	
		void VisitOwner(DataType Data)
		{
			int*item=Data.Item;
			if(*item > 0)
			{
				printf("%s : %d$ \n",Data.Key,*item );
			}
		}
		ListPrint(CurrentState,VisitOwner);
		ListDestroy(CurrentState);//Free the list after the creation
	}	
free(bitcoin);
}
void PrintBitcoinHistory(char* BitcoinID)
{
	//To get the Bitcoin History I must get all the Internal Nodes of the BitcoinTree
	//and print the transaction between the parent and the left child each time

	//We will do this in level order (using BTLevelOrder)
	void **bitcoin=malloc(sizeof(BitcoinTree));

	if(HTGet(Bitcoins,BitcoinID,bitcoin) == True)
	{
		//if the Bitcoin exists:

		void VisitTransaction(BTNode Node)
		{
			BTNode left=BTGetChildLeft(*bitcoin,Node);
			if(left!=NULL && left->item.Amount > 0)
			{
				printf("%s -> %s : %d$\n",Node->item.UserID,left->item.UserID,left->item.Amount );
			}
		}
		printf("BitcoinID:%s History:\n",BitcoinID );
		BTLevelOrder(*bitcoin,VisitTransaction);
	}
	free(bitcoin);
}
void Terminate(void)
{
	End=1;
	HTDestroy(Bitcoins);
	HTDestroy(Wallets);
	HTDestroy(ReceiverHash);
	HTDestroy(SenderHash);
}