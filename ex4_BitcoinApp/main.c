#include "userInterface.h"

int main(void)
{
	Initialize();
	CreateUser("A");
	CreateUser("B");
	CreateUser("C");

	CreateBitcoin("1","A",10);
	CreateBitcoin("2","B",20);
	CreateBitcoin("3","C",200);

	printf("User A has %d$\n",GetUserAmount("A") );
	printf("User B has %d$\n",GetUserAmount("B") );
	printf("User C has %d$\n",GetUserAmount("C") );

	Transfer("B","A",10);
	Transfer("A","C",3);
	Transfer("B","C",2);
	Transfer("C","B",2);
	Transfer("C","A",50);
	Transfer("A","B",17);
	printf("PrintSent A:\n");
	PrintSent("A");
	printf("PrintSent B:\n");
	PrintSent("B");
	printf("PrintSent C:\n");
	PrintSent("C");

	printf("\nPrintReceived A:\n");
	PrintReceived("A");
	printf("PrintReceived B:\n");
	PrintReceived("B");
	printf("PrintReceived C:\n \n");
	PrintReceived("C");

	printf("User A has %d$\n",GetUserAmount("A") );
	printf("User B has %d$\n",GetUserAmount("B") );
	printf("User C has %d$\n \n",GetUserAmount("C") );


	PrintBitcoinOwners("1");
	PrintBitcoinOwners("2");
	PrintBitcoinOwners("3");

	PrintBitcoinHistory("1");
	PrintBitcoinHistory("2");
	PrintBitcoinHistory("3");
	Terminate();
	return 0;

}
