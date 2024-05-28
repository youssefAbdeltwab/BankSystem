#pragma once
#include <iostream>
#include "clsUsers.h"
#include "clsScreen.h"
#include "clsInputValidate.h"



using namespace std;
class clsUpdateUserScreen : protected clsScreen
{
	static int _readPermissionToSet()
	{
		char answer = 'no';
		int permission = 0;

		cout << "\n\n Do you want to give user full access : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}

		cout << "\n\n Do you want to give user access to : \n";

		cout << "\nshow client list  : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pShowclientList;
		}

		cout << "\nAdd client : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pAddClient;
		}
		cout << "\nDelete client : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pDeleteClietn;
		}

		cout << "\nUpdate client : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pDeleteClietn;
		}

		cout << "\nFind client : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pFindClient;
		}

		cout << "\nTransactions : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pTrancaction;
		}

		cout << "\nManage users : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pMangeUsers;
		}

		return permission;
	}


	static void _readuserInfo(clsUsers& user)
	{
		cout << "\nenter Frist Name  : ";
		user.fristName = clsInputValidate::readString();

		cout << "\nenter Last name : ";
		user.lastName = clsInputValidate::readString();

		cout << "\nenter Email : ";
		user.email = clsInputValidate::readString();

		cout << "\nenter  Phone  : ";
		user.phone = clsInputValidate::readString();

		cout << "\nenter Password : ";
		user.password = clsInputValidate::readString();

		cout << "\nenter user permission : ";
		user.permission = _readPermissionToSet();
	}

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

	static void showUpdateUserScreen()
	{

		_drawScreenHeader("\t Update User Screen");

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
		_print(user1);



		cout << "Are you sure you want to Update this user? (y or N)";
		cin >> answer;


		if (answer == 'y' || answer == 'Y')
		{
			cout << "\n\nUpdate user Info:";
			cout << "\n____________________\n";


			_readuserInfo(user1);

			clsUsers::enSaveResults SaveResult;

			SaveResult = user1.save();

			switch (SaveResult)
			{
			case  clsUsers::enSaveResults::svSucceeded:
			{
				cout << "\nUser Updated Successfully :-)\n";
				_print(user1);
				break;
			}
			case clsUsers::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError User was not saved because it's Empty";
				break;

			}

			}
		}
		else
		{
			cout << "\nUser hasn't updated\n";
		}
	}
};

