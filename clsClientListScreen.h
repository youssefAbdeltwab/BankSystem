#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"


using namespace std;

class clsClientListScreen : protected clsScreen
{

	static void _printClientRecordline(clsBankClient client)
	{
		cout << "| " << left << setw(15) << client.getAccountNumber();
		cout << "| " << left << setw(22) << client.fullName();
		cout << "| " << left << setw(12) << client.phone;
		cout << "| " << left << setw(20) << client.email;
		cout << "| " << left << setw(10) << client.pinCode;
		cout << "| " << left << setw(12) << client.accountBalance;
	}

public:

	static void showClientsList()
	{

		if (!checkAccessRights(clsUsers::enPermission::pShowclientList))
		{
			return; // will out from the function 
		}


		vector <clsBankClient> vClient = clsBankClient::getClientList();

		string title = "\tClient list Screen";
		string subtitle =  "\t  ("  + to_string(vClient.size()) +  ") client (s).";

		_drawScreenHeader(title, subtitle);

		cout << setw(8) << left <<  "_____________________________________________________________________________________________________________\n\n";
		cout << "| " << left << setw(15) << "Account Number";
		cout << "| " << left << setw(22) << "Client Name";
		cout << "| " << left << setw(12) << "Phone";
		cout << "| " << left << setw(20) << "Email";
		cout << "| " << left << setw(10) << "pin Code";
		cout << "| " << left << setw(12) << "Account Balance";
		cout << setw(8) << left <<"\n_____________________________________________________________________________________________________________\n";

		if (vClient.size() == 0)
		{
			cout << "\n\t\t\t No Clients Available";
		}
		else
		{
			for (clsBankClient client : vClient)
			{
				_printClientRecordline(client);
				cout << endl;
			}
		}
		cout << setw(8) << left << "\n_____________________________________________________________________________________________________________\n\n\n";
	}


};

