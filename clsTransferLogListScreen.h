#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"


using namespace std;
class clsTransferLogListScreen : protected clsScreen
{

	static void _printLogTransfer(clsBankClient::stLogTransfer transfer)
	{
		 cout <<  setw(8) <<  left << " " << "| " <<  setw(23) <<  left << transfer.date;
		 cout << "| " <<  left <<  setw(8) << transfer.sourceAccountNumber;
		 cout << "| " <<  left <<  setw(8) << transfer.destinationAccountNumber;
		 cout << "| " <<  left <<  setw(8) << transfer.amount;
		 cout << "| " <<  left <<  setw(10) << transfer.sourceBalance;
		 cout << "| " <<  left <<  setw(10) << transfer.destinationBalance;
		 cout << "| " <<  left <<  setw(8) << transfer.userName;

	}

public:

	static void showTransferListScreen()
	{
		vector <clsBankClient::stLogTransfer> vTransfer = clsBankClient::getTransferList();

		string title = "\Transfer Log List Screen";
		string subtitle = "\t ( " + to_string(vTransfer.size()) + " ) Records(s).";

		_drawScreenHeader(title, subtitle);

		cout <<  setw(8) <<  left << "\t_____________________________________________________________________________________________________________\n\n";
		cout <<  setw(8) <<  left << "" << "| " << setw(23) <<  left << "Date/Time ";
		cout << "| " <<  left <<  setw(8) << "S.Account";
		cout << "| " <<  left <<  setw(8) << "D.Account";
		cout << "| " <<  left <<  setw(8) << "Amount";
		cout << "| " <<  left <<  setw(10) << "S.Balance";
		cout << "| " <<  left <<  setw(10) << "D.Balance";
		cout << "| " <<  left <<  setw(8) << "User";
		cout <<  setw(8) <<  left << "\n\t_____________________________________________________________________________________________________________\n";

		if (vTransfer.size() == 0)
		{
			cout << "\n\t\t\t No Users Available";
		}
		else
		{
			for (clsBankClient::stLogTransfer transfer : vTransfer)
			{
				_printLogTransfer(transfer);
				cout << endl;
			}
		}
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________\n\n\n";
	}



	
};

