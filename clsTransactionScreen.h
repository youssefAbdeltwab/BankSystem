#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsMainScreen.h"
#include "clsDepositScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogListScreen.h"

using namespace std;

class clsTransactionScreen : clsScreen
{

	enum  enTransaction { deposit = 1, withdraw = 2, totalBalance = 3, transfer = 4, transferList = 5,  mainMenue = 6 };

	static int _readTransactionMenuOption()
	{
		cout << setw(37) << left << "" << "Choice what do you want? [1-6]";
		int choice = clsInputValidate::readIntNumberBetween(1, 6);
		return choice;
	}

	static void _showDepositScreen()
	{
		//cout << "Deposit screen will be here soon.....\n";
		clsDepositScreen::ShowDepositScreen();
	}

	static void _showWithDrawScreen()
	{
		//cout << "withdraw screen will be here soon.....\n";
		clsWithdrawScreen::ShowWithdrawScreen();
	}

	static void _showTotalBalanceScreen()
	{ 
		//cout << "total Balances screen will be here soon.....\n";
		clsTotalBalancesScreen::showTotalBalances();
	}

	static void _showTransferScreen()
	{
		//cout << "total Balances screen will be here soon.....\n";
		clsTransferScreen::showTansferScreen();
	}

	static void _showTransferLogListScreen()
	{
		//cout << "total Balances screen will be here soon.....\n";
		clsTransferLogListScreen::showTransferListScreen();
	}

	static void _goBackToTransactionMenu()
	{
		cout << "\t\tpress any key to  go back to  main menu......\n";
		system("pause>0");
		showTransactionMenu();
	}
	
	static void _preformTransactionMenuOption(enTransaction choice)
	{
		switch (choice)
		{
		case enTransaction::deposit:
			system("cls");
			_showDepositScreen();
			_goBackToTransactionMenu();
			break;

		case enTransaction::withdraw:
			system("cls");
			_showWithDrawScreen();
			_goBackToTransactionMenu();
			break;

		case  enTransaction::totalBalance:
			system("cls");
			_showTotalBalanceScreen();
			_goBackToTransactionMenu();
			break;

		case  enTransaction::transfer:
			system("cls");
			_showTransferScreen();
			_goBackToTransactionMenu();
			break;

		case  enTransaction::transferList:
			system("cls");
			_showTransferLogListScreen();
			_goBackToTransactionMenu();
			break;

		case enTransaction::mainMenue:
			system("cls");
			//clsMainScreen::showMainMenu();
			break;
		}
	}

public:

	static void showTransactionMenu()
	{
		if (!checkAccessRights(clsUsers::enPermission::pTrancaction))
		{
			return; // will out from the function 
		}

		system("cls");
		_drawScreenHeader("\t Transaction Screen");

		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << "\t      Transaction Main Screen\n";
		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << "\t[1] Deposit\n";
		cout << setw(37) << left << "" << "\t[2] Withdraw\n";
		cout << setw(37) << left << "" << "\t[3] Total Balance\n";
		cout << setw(37) << left << "" << "\t[4] Transfer\n";
		cout << setw(37) << left << "" << "\t[5] Transfer Log List\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu\n";
		cout << setw(37) << left << "" << "======================================\n";
		_preformTransactionMenuOption((enTransaction)_readTransactionMenuOption());
	}
};

