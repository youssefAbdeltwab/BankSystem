#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsInputValidate.h"
#include "clsScreen.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
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


	static void deleteClient()
	{
		if (!checkAccessRights(clsUsers::enPermission::pDeleteClietn))
		{
			return; // will out from the function 
		}

		string AccountNumber = "";
		char answer = 'n';
	
		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::readString();
	
		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::readString();
		}
	
		clsBankClient client = clsBankClient::find(AccountNumber);
	
		_print(client);
	
		cout << "\n\nAre you sure you want to delete client ? (y or  n)";
		cin >> answer;
	
		if (answer == 'y' || answer == 'Y')
		{
			if (client.deleted())	
			{
				cout << "\nclient has deleted successfully\n";
				_print(client);
			}
			else
			{
				cout << "\nError Client not deleted";
			}
		}
		else
			cout << "\n\nClient not Deleted\n\n";
	}
	
};

