#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsBankClient.h"
using namespace std;

class clsTransferScreen : protected clsScreen
{
	static string _readAccountNumber()
	{
		string accountNumber = "";

		cout << "\nPlease enter Account Number to Transfer from :  ";
		accountNumber = clsInputValidate::readString();

		while (!clsBankClient::isClientExist(accountNumber))
		{
			cout << "\nAccount number is not found, choose another one: ";
			accountNumber = clsInputValidate::readString();
		}
		return accountNumber;
	}

	static double _readAmount(clsBankClient sourceClient)
	{
		double  amount = 0;

		cout << "\nEnter transfer amount?  ";
		amount = clsInputValidate::readDoubleNumber();

		while (amount > sourceClient.accountBalance)
		{
			cout << "\nAccout Balance of account number [" << sourceClient.getAccountNumber()
				<< "] is less the the Transfer amount you enter, the amount shouldn't exceed : "
				<< sourceClient.accountBalance << "\nEnter another amount ?  ";
			amount = clsInputValidate::readDoubleNumber();
		}
		return amount;
	}
	
	static void _print(clsBankClient client)
	{
		cout << "\nClient Card :  ";
		cout << "\n_________________________";
		cout << "\nFull Name      : " << client.fullName();
		cout << "\nAccount Number : " << client.getAccountNumber();
		cout << "\nBalance        : " << client.accountBalance;
		cout << "\n_________________________\n";
	}


public:
	static void showTansferScreen()
	{
		char answer = 'n';

		_drawScreenHeader("       Transfer Screen ");

		clsBankClient sourceClient = clsBankClient::find(_readAccountNumber());
		_print(sourceClient);


		clsBankClient destinationClient = clsBankClient::find(_readAccountNumber());
		_print(destinationClient);

		double amount = _readAmount(sourceClient);
		
		cout << "\nAre you sure you want to perform this operation? (y or n)  ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			if (sourceClient.transfer(amount, destinationClient, currentUser.userName))
			{
				cout << "\n\nTransfer done successfully \n";

			}
			else
			{
				cout << "\n\nTransfer failed \n";

			}
			//sourceClient.logTransferIntoFile(destinationClient, amount);
			_print(sourceClient);
			_print(destinationClient);
		}
		else
		{
			cout << "\n\nTransaction doesn't perform\n\n";
		}

	}
};

