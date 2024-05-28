#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsListCurrencyScreen.h"
#include "clsInputValidate.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrency.h"
#include "clsCalculatorScreen.h"
using namespace std;

class clsCurrencyScreen : protected clsScreen
{
	enum enOption { cList = 1, cFind = 2, cUpdate = 3, cCalculator = 4, cCurrencyMenu = 5 };

	static short _readMainMenuOption()
	{
		short number;
		cout << setw(37) << left << "\t\t\t\t\tChoose what do you want? [1-5]";
		short  choice = clsInputValidate::readIntNumberBetween(1, 5, "Invalid Number, enter again\n");
		return choice;
	}

	static void _showListCurrenciesScreen()
	{
		//cout << "\n\t\t\t List screen will be here soon";
		clsListCurrencyScreen::showCurrencyList();
	}

	static void _showFindCurrencyScreen()
	{
		//cout << "\n\t\t\t List screen will be here soon";
		clsFindCurrency::showFindCurrencyScreen();
	}

	static void _showUpdateCurrencyScreen()
	{
		//cout << "\n\t\t\t List screen will be here soon";
		clsUpdateCurrency::showUpdateCurrecnyScreen();
	}
	
	static void _showCurrencyCalculatorScreen()
	{
		//cout << "\n\t\t\t List screen will be here soon";
		clsCalculatorScreen::showCurrencyCalculatorScreen();
	}

	static void _goBackToCurrencyMainMenu()
	{
		cout << "\n\n\t\tpress any key to  go back to  main menu......\n";
		system("pause>0");
		showCurrencyMainMenu();
	}

	static void _performMainMenuOption(enOption choice)
	{
		switch (choice)
		{
		case enOption::cList:
			system("cls");
			_showListCurrenciesScreen();
			_goBackToCurrencyMainMenu();
			break;

		case enOption::cFind:
			system("cls");
			_showFindCurrencyScreen();
			_goBackToCurrencyMainMenu();
			break;

		case  enOption::cUpdate:
			system("cls");
			_showUpdateCurrencyScreen();
			_goBackToCurrencyMainMenu();
			break;

		case enOption::cCalculator:
			system("cls");
			_showCurrencyCalculatorScreen();
			_goBackToCurrencyMainMenu();
			break;

		case enOption::cCurrencyMenu:
			system("cls");
			//_goBackToCurrencyMainMenu();
			break;
		}
	}


public:

	static void showCurrencyMainMenu()
	{
		if (!checkAccessRights(clsUsers::enPermission::pCurrency))
		{
			return; // will out from the function 
		}

		system("cls");
		clsScreen::_drawScreenHeader("\t    Currency Exchange Main Screen");
		cout << setw(37) << left << " " << "======================================\n";
		cout << setw(37) << left << " " << "\t\t Currency Exchange Menu" << endl;
		cout << setw(37) << left << " " << "======================================\n";
		cout << setw(37) << left << " " << "\t[1] List Currencies\n";
		cout << setw(37) << left << " " << "\t[2] Find Currencies\n";
		cout << setw(37) << left << " " << "\t[3] Update Currencies\n";
		cout << setw(37) << left << " " << "\t[4] Currency Calculator \n";
		cout << setw(37) << left << " " << "\t[5] Main menu\n";
		cout << setw(37) << left << " " << "======================================\n";
		_performMainMenuOption((enOption)_readMainMenuOption());
	}
};

