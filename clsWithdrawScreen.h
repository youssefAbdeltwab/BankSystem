#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsWithdrawScreen : clsScreen
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

	static void ShowWithdrawScreen()
	{
		string AccountNumber = "";
		char answer = 'n';
		double amount;

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			AccountNumber = clsInputValidate::readString();
		}

		clsBankClient client1 = clsBankClient::find(AccountNumber);
		_print(client1);

		cout << "\nplease enter withdraw amount";
		amount = clsInputValidate::readDoubleNumber();

		cout << "\n\nAre you sure you want to perform this tancsaction? (y or n)";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			if (client1.withDraw(amount))
			{
				cout << "\n\nWithdraw done successfully\n";
				cout << "\nNew balance is : " << client1.accountBalance<< endl << endl;
			}
			else
			{
				cout << "\n\nAccount Balance is insufficient to withdraw : " << amount;
				cout << "\nAccount Balance is : " << client1.accountBalance<< endl << endl;
			}
			
		}
		else
		{
			cout << "\n\nTransaction doesn't perform\n\n";
		}

	}
};

