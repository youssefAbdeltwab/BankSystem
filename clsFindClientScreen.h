#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

class clsFindClientScreen : protected clsScreen
{
	static void _print(clsBankClient client)
	{
		cout << "\nClient Card :  ";
		cout << "\n_________________________";
		cout << "\nFrist Name     : " << client.fristName;
		cout << "\nLast Name      : " << client.lastName;
		cout << "\nFull Name      : " << client.fullName();
		cout << "\nEmail          : " << client.email;
		cout << "\nPhone          : " << client.phone;
		cout << "\nAccount Number : " << client.getAccountNumber();
		cout << "\nPassword       : " << client.pinCode;
		cout << "\nBalance        : " << client.accountBalance;
		cout << "\n_________________________\n";
	}

public:

	static void findClient()
	{
		if (!checkAccessRights(clsUsers::enPermission::pFindClient))
		{
			return; // will out from the function 
		}


		_drawScreenHeader("\t Find Client Screen");

		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::readString();
		}

		clsBankClient Client1 = clsBankClient::find(AccountNumber);

		if (!Client1.isEmpty())
		{
			cout << "\nClient found\n";
			_print(Client1);
		}
		else
		{
			cout << "\nClient NOT found\n";
		}

	}

};

