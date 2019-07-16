#pragma once
#include "HashTableTypes.h"
#include "DoubleListTypes.h"
#include "types_BT.h"
//Here we will declare the Tree type we will use to store bitcoin IDs and the data they contain
//Also we will declare the global variables that we will use to store :
//1.transactions (from/to the user) with two separate hash tables
//2.Wallets of the users with a Hash Table
//3.Bitcoin Trees
short int End; //Global variable that will determine the New and Free functionality
typedef List Wallet;//The list that will contain BTNodes that are leaves and will allow us to find the Balance of the userID we check
typedef BinaryTree BitcoinTree; //The Tree type that we will save each bitcoin data
typedef struct{
	int ID;
	unsigned int Date;
	List Details; //The list of parent nodes that will contain the parts of the bitcoins that the user (detailed in the BTNode's userID) 
				  //is the receiver/sender (depends in which hash it's included)
} Transaction;
HTHash Bitcoins;//Bitcoin trees hash That will contain bitcoin trees
HTHash Wallets; //wallet-lists hash
HTHash ReceiverHash;//Hash that will contain the transactions that the user is the receiver 
HTHash SenderHash; //Hash that will contain the transactions that the use is the sender
