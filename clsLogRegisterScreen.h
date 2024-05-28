#pragma once
#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsDate.h"

using namespace std;


class clsLogRegisterScreen : protected clsScreen
{

	static void _printuserRecordline(clsUsers::stLoginRegisterRecord LoginRegisterRecord)
	{
		cout << setw(8) <<left << " " <<  "| " << setw(38) << left << clsDate::GetSystemDateTimeString();
		cout << "| " << left << setw(20) << LoginRegisterRecord.userName;
		cout << "| " << left << setw(20) << LoginRegisterRecord.password;
		cout << "| " << left << setw(10) << LoginRegisterRecord.permission;
	}

public:

	static void showLogRegisterScreen()
	{
		if (!checkAccessRights(clsUsers::enPermission::pLogRegister))
		{
			return; // will out from the function 
		}

		vector <clsUsers::stLoginRegisterRecord> vLoginRegisterRecord = clsUsers::getLogRegisterList();

		string title = "\tLogin Register List Screen";
		string subtitle = "\t ( " + to_string(vLoginRegisterRecord.size()) + " ) Records(s).";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left << "\t_____________________________________________________________________________________________________________\n\n";
		cout << setw(8) << left << " " << "| " << setw(38) << left << "Date/Time ";
		cout << "| " << left << setw(20) << "UserName";
		cout << "| " << left << setw(20) << "Password";
		cout << "| " << left << setw(10) << "Permissions";
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________\n";

		if (vLoginRegisterRecord.size() == 0)
		{
			cout << "\n\t\t\t No Users Available";
		}
		else
		{
			for (clsUsers::stLoginRegisterRecord login : vLoginRegisterRecord)
			{
				_printuserRecordline(login);
				cout << endl;
			}
		}
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________\n\n\n";
	}


};

