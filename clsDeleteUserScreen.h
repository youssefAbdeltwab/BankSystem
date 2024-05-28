#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"


using namespace std;

class clsDeleteUserScreen :protected clsScreen
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
		cout << "\nUsername       : " << user.userName;
		cout << "\nPassword       : " << user.password;
		cout << "\npermission     : " << user.permission;
		cout << "\n_________________________\n";
	}

public:

	static void showDeleteUserScreen()
	{
		string userName = "";
		char answer = 'no';
		_drawScreenHeader("Delete User Screen");



		cout << "\nPlease enter userName : ";
		userName = clsInputValidate::readString();

		while (!(clsUsers::isUserExist(userName)))
		{
			cout << "\nUsername[ " << userName << " ] isn't exit, enter another one : ";
			userName = clsInputValidate::readString();
		}
		
		clsUsers user = clsUsers::find(userName);

		_print(user);

		cout << "\n\nAre you sure you want to delete user ? (y or  n)";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			if (user.deleted())
			{
				cout << "\nUser has deleted successfully\n\n";
				_print(user);
			}
			else
			{
				cout << "\nError User not deleted";
			}
		}
		else
			cout << "\n\nUser not Deleted\n\n";
	}

	
};

