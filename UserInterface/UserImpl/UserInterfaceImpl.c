#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "StructTypes.h"
#include "BitcoinApp.h"

#define ERROR -1
static int Start=1;
//Implementation of the Clients Utillity functions
void PrintMenu(void)
{
	if(Start==1)
	{
		Initialize();
		Start=0;
	}
	printf("\t===Menu===\n");

	printf("1.Create a User\n");
	printf("2.Create a Bitcoin\n");
	printf("3.Check User's Amount\n");
	printf("4.Make a Transfer\n");
	printf("5.Print Sender Transactions\n");
	printf("6.Print Receiver Transactions\n");
	printf("7.Print Bitcoin Owners\n");
	printf("8.Print Bitcoin's Transaction History\n");
	printf("\nPress 0 to Exit\n");
}

//Get the Option and return it
int GetChoice(void)
{
	int choice;
	choice=getchar();

	if(choice < '0' || choice > '9')
	{
		printf("Error:Wrong input.Please try again\n");
		return ERROR; //-1 is the value for ERROR
	}
	char ch;
	int counter = 0;
	while((ch=getchar()) != '\n' && ch != EOF){
		if(ch!=' ' && ch!='\t')
			counter++;
	}

	if(counter!=0) 
	{
		printf("Please type a number between 0 and 8 and nothing more\n"); 
		return ERROR;
	}

	return (choice-48);
}
static int GetInt(void)
{
	int returnNumber=0;
	char ch;

	while((ch = getchar()) != '\n' && ch!= EOF)
	{
		if(ch>='0' && ch<='9')
		{
			returnNumber = returnNumber*10 + (ch - 48) ;
		}
		else
		{
			return ERROR;
		}
	}

	return returnNumber;
}
//String building function
static char* GetString(void)
{
	char* returnString=malloc(sizeof(char));
	int pos=0;
	char ch;
	while((ch=getchar()) != '\n' && ch != EOF)
		{
			//we extend the string that we wanna return to the user to get the next letter
			returnString[pos]=ch;
			//we copy the current read character to the proper position 
			pos++;
			returnString=realloc(returnString,sizeof(char)*pos + 1); 
		}
	return returnString; 
}

int Act(int option)
{
	char *UserName=NULL;
	char* BitcoinID=NULL;
	char* BitcoinOwner=NULL;
	char* Username=NULL;
	char* Sender=NULL;
	char* Receiver=NULL;
	int CashAmount = 0, Amount = 0;
	switch(option)
	{
		case 0:
			Terminate();
			return 0;
		break;
		case 1:
			printf("Type the new User Name: ");
			UserName=GetString();

			//Now we must create the user.So we just use the Create User function and let this function do teh job for us
			CreateUser(UserName);
			free(UserName);
		break;
		case 2:
			printf("Please Enter : BitcoinID, BitcoinOwner, Cash Amount with that specific order.\n");
			//TO BE CONTINUED
			
			//Get the BitcoinID
			printf("BitcoinID: ");
			BitcoinID = GetString();

			//Get the BitcoinOwner
			printf("\nBitcoinOwner: "); 
			BitcoinOwner = GetString();

			//Get the Cash Amount to initialize the BitcoinTree
			printf("\nCash Amount: ");
			CashAmount = GetInt();

			while(CashAmount < 0)
			{
				printf("Please don't type letters just a number. The result could be unexpected.Try again:\n");
				CashAmount = GetInt();
			}
			//Create the BitcoinTree
			CreateBitcoin(BitcoinID, BitcoinOwner, CashAmount);
			free(BitcoinID);
			free(BitcoinOwner);
			printf("\n");
		break;
		case 3:
			printf("Enter the Username: ");
			//Get Username
			Username = GetString();

			printf("\n%s's Balance: %d\n", Username, GetUserAmount(Username));
			free(Username);
		break;
		case 4:
			printf("Enter the Sender: ");
			//Get Sender's Name
			Sender = GetString();

			printf("\nEnter Receiver: ");
			//Get the Receiver's Name
			Receiver = GetString();

			printf("\nAmount to Transfer: ");
			//Get the Amount to Transfer
			Amount = GetInt();
			while(Amount < 0)
			{
				printf("Please don't type letters just a number. The result could be unexpected.Try again:\n");
				Amount = GetInt();
			}
			//Get the Transaction Done
			Transfer(Sender, Receiver, Amount);
			free(Sender);
			free(Receiver);
		break;
		case 5:
			printf("Enter the Sender's Name: "); //Get the sender name 
			Sender = GetString();
			printf("\n");
			//print the sender transaction lists
			PrintSent(Sender);
			free(Sender);
		break;
		case 6:
			printf("Enter the Receiver's Name: ");
			//Get the Receiver's Name 
			Receiver = GetString();
			printf("\n");

			//Print the Reiceiver's transaction list
			PrintReceived(Receiver);
			free(Receiver);
		break;
		case 7:
			printf("Enter the Bitcoin's ID: ");
			//Get the bitcoin ID
			BitcoinID = GetString();
			printf("\n");

			//Print the Owners' list
			PrintBitcoinOwners(BitcoinID);
			free(BitcoinID);
		break;
		case 8:
			printf("Enter the Bitcoin's ID: ");
			//Get the bitcoin's ID
			BitcoinID = GetString();
			printf("\n");

			//Print the Bitcoin's Transaction List
			PrintBitcoinHistory(BitcoinID);
			free(BitcoinID);
		break;
		default: printf("Wrong Option: Type a number from 0 to 8.\n");
	}	
	return 1;
}