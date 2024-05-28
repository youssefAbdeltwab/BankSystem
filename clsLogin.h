#pragma once
#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "global.h"
#include "clsMainScreen.h"
#include "clsDate.h"
using namespace std;

class clsLoginScreen : protected clsScreen
{

	static bool _login()
	{
		bool loginFailed = false;
		string userName, password;
		short counter = 3;

		do
		{
			if (loginFailed)
			{
				cout << "\nInvalid username/password\n";
				counter--;
				cout << "You have " << counter << " trial(s) to login. \n\n";
				

				if (counter == 0)
				{
					cout << "You are locked after 3 Trials\n";
					return false ; // will stop systeme
				}
			}

			cout << "Enter username :  ";
			cin >> userName;

			cout << "Enter password :  ";
			cin >> password;

			currentUser = clsUsers::find(userName, password);

			loginFailed = currentUser.isEmpty();

		} while (loginFailed);

		currentUser.registerLogIn();

		clsMainScreen::showMainMenu();
		return true;
	}

public:

	static bool showLoginScreen()
	{
		
	    system("cls");
		_drawScreenHeader("\t          LOGIN SCREEN ");
		return _login();
		
	}
};

