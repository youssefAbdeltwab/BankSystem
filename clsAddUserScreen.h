#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUsers.h"
#include "clsInputValidate.h"


using namespace std;

class clsAddUserScreen : clsScreen
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

		cout << "\nLogin Register : ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUsers::enPermission::pLogRegister;
		}

		return permission;
	}

	static void _readUserInfo(clsUsers& user)
	{

		cout << "\nenter Frist Name  : ";
		user.fristName = clsInputValidate::readString();

		cout << "\nenter Last name : ";
		user.lastName = clsInputValidate::readString();

		cout << "\nenter Email : ";
		user.email = clsInputValidate::readString();

		cout << "\nenter Phone  : ";
		user.phone = clsInputValidate::readString();


		cout << "\nplease enter password  : ";
		user.password = clsInputValidate::readString();

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
		cout << "\nUsername       : " << user.userName;
		cout << "\nPassword       : " << user.password;
		cout << "\npermission     : " << user.permission;
		cout << "\n_________________________\n";
	}


public:

	static void ShowAddUserScreen()
	{
		string userName = "";		

		_drawScreenHeader("Add New User Screen");

		
		cout << "\nplease enter userName : ";
		userName = clsInputValidate::readString();

		while (clsUsers::isUserExist(userName))
		{
			cout << "\nUsername[ " << userName << " ] is already exit, enter another one : ";
			userName = clsInputValidate::readString();
		}

		clsUsers user = clsUsers::getAddNewUserObject(userName);

		_readUserInfo(user);

		clsUsers::enSaveResults  saveResults;

		saveResults = user.save();

		switch (saveResults)
		{
		case clsUsers::enSaveResults::svSucceeded:

			cout << "\nuser has add successfully";
			_print(user);
			break;

		case  clsUsers::enSaveResults::svFailedEmptyObject:
			cout << "\nError user is empty";
			break;

		case  clsUsers::enSaveResults::svFailedAccountNumberExists:
			cout << "\\nusername is already exist";
			break;
		}
	}
};

