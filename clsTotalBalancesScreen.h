#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsUtil.h"

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{

	static void printClientRecordBalanceLine(clsBankClient client)
	{
		cout << setw(25) << left << "" << "| " << setw(15) << left << client.getAccountNumber();
		cout << "| " << left << setw(40) << client.fullName();	
		cout << "| " << left << setw(12) << client.accountBalance;
	}

public:

	static void showTotalBalances()
	{
		vector <clsBankClient> vClient = clsBankClient::getClientList();

		string title = "\tTotal Balances List";
		string subTitle = "\t\t (" + to_string(vClient.size()) + ") client (s).";

		_drawScreenHeader(title, subTitle);

		cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		cout << setw(25) << left << "" << "| " << left << setw(15) << "Accout Number";
		cout << "| " << left << setw(40) << "Client Name";
		cout << "| " << left << setw(12) << "Balance";
		cout << setw(25) << left << "" << "\t\t_______________________________________________________";
		cout << "__________________________\n" << endl;

		double totalBalance = clsBankClient::totalBalances();
		if (vClient.size() == 0)
		{
			cout << "\n\t\t\t No Clients Available";
		}
		else
		{
			for (clsBankClient client : vClient)
			{
				printClientRecordBalanceLine(client);
				cout << endl;

			}

			cout << setw(25) << left << "" << "\n\t\t_______________________________________________________";
			cout << "__________________________\n" << endl;

			cout << "\n\t\t\t\t\t\t Total Balance = " << totalBalance << endl;
			cout << "\t\t\t\t\t\t( " << clsUtil::numberToText(totalBalance) << ") \n";


		}

	}

//	void showTotalBalances()
//{
//	vector <clsBankClient> vClient = clsBankClient::getClientList();
//
//	cout << "\n\t\t\t\t\t Balance list (" << vClient.size() << ") client(s)." << endl;
//	cout << "_______________________________________________________________________________________________________\n\n";
//	cout << "| " << left << setw(15) << "Account Number";
//	cout << "| " << left << setw(45) << "Client Name";	
//	cout << "| " << left << setw(30) << "Account Balance";
//	cout << "\n_______________________________________________________________________________________________________\n";
//
//	double totalBalance = clsBankClient::totalBalances();
//	if (vClient.size() == 0)
//	{
//		cout << "\n\t\t\t No Clients Available";
//	}
//	else
//	{
//		for (clsBankClient client : vClient)
//		{
//			printClientRecordBalanceLine(client);
//			cout << endl;
//	
//		}
//		cout << "\n_______________________________________________________________________________________________________\n";
//
//		cout << "\n\t\t\t\t\t\t Total Balance = " << totalBalance << endl;
//		cout << "\t\t\t\t\t\t( " << clsUtil::numberToText(totalBalance) << ") \n";
//
//
//	}
//
//}

};

