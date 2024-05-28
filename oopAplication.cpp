#include <iostream>
#include "clsLogin.h"
using namespace std;



int main()
{
	while (true)
	{
		if (clsLoginScreen::showLoginScreen() == false)
		{
			break;
		}

	}
	//system("pause>0");
	return  0;
}
