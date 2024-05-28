#pragma once
#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"



using namespace std;
class clsFindUserScreen : protected clsScreen
{

	static void _print(clsUsers user)
	{
		cout << "\nUser Card :  ";
		cout << "\n_________________________";
		cout << "\nFrist Name     : " << user.fristName;
		cout << "\nLast Name      : " << user.lastName;
		cout << "\nFull Name      : " << user.fullName();
		cout << "\nEmail          : " << user.email;
		cout << "\nPhone          : " << user.phone;
		cout << "\nUser Name      : " << user.userName;
		cout << "\nPassword       : " << user.password;
		cout << "\nPermission     : " << user.permission;
		cout << "\n_________________________\n";
	}

public:

	static void showFindUserScreen()
	{

		_drawScreenHeader("\t Find User Screen");

		string userName = "";
		char answer = 'no';

		cout << "\nPlease Enter username : ";
		userName = clsInputValidate::readString();

		while (!clsUsers::isUserExist(userName))
		{
			cout << "\nUsername[ " << userName << " ] isn't exit, enter another one : ";
			userName = clsInputValidate::readString();
		}

		clsUsers user1 = clsUsers::find(userName);
	

		
		if (!user1.isEmpty())
		{
			cout << "\n\nUser is found";
			_print(user1);
		}
		else
		{
			cout << "\n\nUser NOT found";
		}
	}
};

