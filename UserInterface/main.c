#include "userInterface.h"

int main(void)
{
	int action;
	do
	{
		PrintMenu();
		action = Act(GetChoice());
	}while( action!= 0);

	return 0;
}
