#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"


using namespace std;

class clsAddNewClientScreen : clsScreen
{

	static void _readClientInfo(clsBankClient& client)
	{
		cout << "\nenter Frist Name : ";
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

	static void AddNewClient()
	{

		if (!checkAccessRights(clsUsers::enPermission::pAddClient))
		{
			return; // will out from the function 
		}

		string AccountNumber = "";

		cout << "\nPlease Enter client Account Number: ";
		AccountNumber = clsInputValidate::readString();

		while (clsBankClient::isClientExist(AccountNumber))
		{
			cout << "\nAccount number is already exists, choose another one: ";
			AccountNumber = clsInputValidate::readString();
		}

		clsBankClient newClient = clsBankClient::getAddNewClientObject(AccountNumber);

		_readClientInfo(newClient);

		clsBankClient::enSaveResults  saveResults;

		saveResults = newClient.save();

		switch (saveResults)
		{
		case clsBankClient::enSaveResults::svSucceeded:
			cout << "\nclient has add successfully";
			_print(newClient);
			break;

		case  clsBankClient::enSaveResults::svFailedEmptyObject:
			cout << "\nError client is empty";
			break;

		case  clsBankClient::enSaveResults::svFailedAccountNumberExists:
			cout << "\n Account number is already exist";
			break;
		}
	}

};

