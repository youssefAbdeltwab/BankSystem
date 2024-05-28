#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"	
#include "clsInputValidate.h"
#include "clsClientListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionScreen.h"
#include "clsManageUsersScreen.h"
#include "global.h"
#include "clsLogRegisterScreen.h"
#include "clsCurrencyScreen.h"
using namespace std;

class clsMainScreen : protected clsScreen
{
	enum  enOption { show = 1, add = 2, deleted = 3, update = 4, find = 5,
					transaction = 6, manageUsers = 7, loginRegister = 8, currency = 9, logOut = 10 };

	static short _readMainMenuOption()
	{
		short number;
		cout << setw(37) << left <<  "\t\t\t\t\tChoose what do you want? [1-10]";
		short  choice =clsInputValidate::readIntNumberBetween(1,10, "Invalid Number, enter again\n");
		return choice;
	}

	static void  _goBackToMainMenu()
	{
		cout << "\t\tpress any key to  go back to  main menu......\n";
		system("pause>0");
		showMainMenu();
	}

	static void  _showAllClientsScreen()
	{
		clsClientListScreen::showClientsList();
	}

	static void  _showAddClientScreen()
	{
		clsAddNewClientScreen::AddNewClient();
	}

	static void  _showDeleteClientScreen()
	{
		clsDeleteClientScreen::deleteClient();
	}

	static void  _showUpdateClientScreen()
	{
		clsUpdateClientScreen::UpdateClient();
	}

	static void  _showFindClientScreen()
	{
		clsFindClientScreen::findClient();
	}

	static void  _showtransactionMenu()
	{
		clsTransactionScreen::showTransactionMenu();
	}

	static void  _showManageUsersMenu()
	{
		//cout << "show client screen will be here soon\n";
		clsManageUsersScreen::showUsersMenu();
	}

	static void  _showLogRegisterScreen()
	{
		clsLogRegisterScreen::showLogRegisterScreen();
	}

	static void  _showCurrencyScreen()
	{
		clsCurrencyScreen::showCurrencyMainMenu();
	}

	static void  _logout()
	{
		clsUsers::find("", "");
	//	cout << "show client screen will be here soon\n";
	
	}

	static void _performMainMenuOption(enOption choice)
	{
		switch (choice)
		{
		case enOption::show:
			system("cls");
			_showAllClientsScreen();
			_goBackToMainMenu();
			break;

		case enOption::add:
			system("cls");
			_showAddClientScreen();
			_goBackToMainMenu();
			break;

		case  enOption::deleted:
			system("cls");
			_showDeleteClientScreen();
			_goBackToMainMenu();
			break;

		case enOption::update:
			system("cls");
			_showUpdateClientScreen();
			_goBackToMainMenu();
			break;

		case enOption::find:
			system("cls");
			_showFindClientScreen();
			_goBackToMainMenu();
			break;

		case enOption::transaction:
			system("cls");
			_showtransactionMenu();
			_goBackToMainMenu();
			break;

		case enOption::manageUsers:
			system("cls");
			_showManageUsersMenu();
			_goBackToMainMenu();
			break;

		case enOption::loginRegister:
			system("cls");
			_showLogRegisterScreen();
			_goBackToMainMenu();
			break;

		case enOption::currency:
			system("cls");
			_showCurrencyScreen();
			_goBackToMainMenu();
			break;

		case enOption::logOut:
			system("cls");
			_logout ();
			break;
		}
	}

public:

	static void showMainMenu()
	{
		system("cls");
		clsScreen::_drawScreenHeader("\t    Main Screen");
		cout << setw(37) << left << " " << "======================================\n";
		cout << setw(37) << left << " " << "\t\t Main Menu Screen" << endl;
		cout << setw(37) << left << " " << "======================================\n";
		cout << setw(37) << left << " " << "\t[1] Show Client Cist\n";
		cout << setw(37) << left << " " << "\t[2] Add New Client\n";
		cout << setw(37) << left << " " << "\t[3] Delete Client\n";
		cout << setw(37) << left << " " << "\t[4] Update Client info \n";
		cout << setw(37) << left << " " << "\t[5] Find Client\n";
		cout << setw(37) << left << " " << "\t[6] Transactios\n";
		cout << setw(37) << left << " " << "\t[7] Manage Users\n";
		cout << setw(37) << left << " " << "\t[8] Login Register\n";
		cout << setw(37) << left << " " << "\t[9] Currency Exchange\n";
		cout << setw(37) << left << " " << "\t[10] Logout\n";
		cout << setw(37) << left << " " << "======================================\n";
		_performMainMenuOption((enOption)_readMainMenuOption());
	}
};

