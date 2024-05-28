#pragma once
#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
using namespace std;

class clsListUserSCreen : protected clsScreen
{
	static void _printuserRecordline(clsUsers user)
	{
		cout << "| " << left << setw(15) << user.userName;
		cout << "| " << left << setw(22) << user.fullName();
		cout << "| " << left << setw(12) << user.phone;
		cout << "| " << left << setw(20) << user.email;
		cout << "| " << left << setw(10) << user.password;
		cout << "| " << left << setw(12) << user.permission;
	}

public:

	static void showListUsersScreen()
	{
		vector <clsUsers> vUser = clsUsers::getUsersList();

		string title = "\tUsers List Screen";
		string subtitle = "\t ( " + to_string(vUser.size()) + " ) user(s).";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left << "_____________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(15) << "Usename ";
		cout << "| " << left << setw(22) << "Full Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "Password";
		cout << "| " << left << setw(12) << "Permissions";
		cout << setw(8) << left << "\n_____________________________________________________________________________________________________________\n";

		if (vUser.size() == 0)
		{
			cout << "\n\t\t\t No Users Available";
		}
		else
		{
			for (clsUsers user : vUser)
			{
				_printuserRecordline(user);
				cout << endl;
			}
		}
		cout << setw(8) << left << "\n_____________________________________________________________________________________________________________\n\n\n";
	}

};

