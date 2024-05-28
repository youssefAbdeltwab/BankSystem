#pragma once
#include <iostream>
#include "clsUsers.h"
#include "global.h"
#include "clsDate.h"
using namespace std;

class clsScreen
{

protected:

	static void _drawScreenHeader(string title, string subtitle = "")
	{
		cout << "\n\t\t\t\t__________________________________________\n";
		cout << "\n\t\t\t\t   " << title << endl;

		if (subtitle != "")
		{
			cout << "\t\t\t\t\t" << subtitle << endl;
		}
		cout << "\t\t\t\t__________________________________________\n\n";

		//string user = currentUser;
		
		cout << "\t\t\t\tUser: " << currentUser.userName << endl;
		cout << "\t\t\t\tDate: ";

		clsDate date;
		date.Print();
		cout << endl;
		
	}

	static bool checkAccessRights(clsUsers::enPermission permission)
	{
		if (!currentUser.checkAccessPermission(permission))
		{
			cout << "\n\t\t\t\t_____________________________________________\n";
			cout << "\n\t\t\t\t\t" << "Access Denied! contact your admin." << endl;
			cout << "\n\t\t\t\t_____________________________________________\n\n\n";
			return false;
		}
		else
		{
			return true;
		}
	}
};

