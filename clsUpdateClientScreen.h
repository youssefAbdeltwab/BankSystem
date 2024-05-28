#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


using namespace std;
class clsUpdateClientScreen : clsScreen
{
	static void _readClientInfo(clsBankClient& client)
	{
		cout << "\nenter Frist Name  : ";
		client.fristName = clsInputValidate::readString();

		cout << "\nenter Last name : ";
		client.lastName = clsInputValidate::readString();

		cout << "\nenter Email : ";
		client.email = clsInputValidate::readString();

		cout << "\nenter  Phone  : ";
		client.phone = clsInputValidate::readString();

		cout << "\nenter Pin Code  : ";
		client.pinCode = clsInputValidate::readString();

		cout << "\nenter Client Balance : ";
		client.accountBalance = clsInputValidate::readDoubleNumber();
	}

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

	static void UpdateClient()
	{
		if (!checkAccessRights(clsUsers::enPermission::pUpdateClient))
		{
			return; // will out from the function 
		}


		_drawScreenHeader("\t Update Client Screen");

		string AccountNumber = "";
		char answer = 'no';

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::readString();
		}

		clsBankClient Client1 = clsBankClient::find(AccountNumber);
		_print(Client1);



		cout << "Are you sure you want to Update this client? (y or N)";
		cin >> answer;


		if (answer == 'y' || answer == 'Y')
		{
			cout << "\n\nUpdate Client Info:";
			cout << "\n____________________\n";


			_readClientInfo(Client1);

			clsBankClient::enSaveResults SaveResult;

			SaveResult = Client1.save();

			switch (SaveResult)
			{
			case  clsBankClient::enSaveResults::svSucceeded:
			{
				cout << "\nAccount Updated Successfully :-)\n";
				_print(Client1);
				break;
			}
			case clsBankClient::enSaveResults::svFailedEmptyObject:
			{
				cout << "\nError account was not saved because it's Empty";
				break;

			}

			}
		}
		else
		{
			cout << "client hasn't update\n";
		}
	}
};

