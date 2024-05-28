#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"

using namespace std;

class clsDepositScreen : clsScreen
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

	static void ShowDepositScreen()
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
		
		cout << "\nplease enter deposit amount";
		amount = clsInputValidate::readDoubleNumber();

		cout << "\n\nAre you sure you want to perform this transaction? (y or n)";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			client1.deposit(amount);
			cout << "\nDeposit done successfully\n";
			cout << "\nNew balance is : " << client1.accountBalance << endl;
		}
		else
		{
			cout << "\n\nTransaction doesn't perform\n";
		}

	}
};

