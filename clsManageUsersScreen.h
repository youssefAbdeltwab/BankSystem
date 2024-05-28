#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsMainScreen.h"
#include "clsAddUserScreen.h"
#include "clsListUserSCreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
	enum  enUsers { showUsers = 1, addUser = 2, deleteUser = 3, updateUsers = 4, findUsers =5, mainMenu = 6};

	static int _readUsersMainMenuOption()
	{
		cout << setw(37) << left << "" << "choose what do you want? [1-6]  ";
		int choice = clsInputValidate::readIntNumberBetween(1, 6);
		return choice;
	}
	
	static void _showListUsersScreen()
	{
		//cout << "\t list Users screen will be here soon\n";
		clsListUserSCreen::showListUsersScreen();
	}

	static void _addUserScreen()
	{
	//	cout << "\t add User screen will be here soon\n";
		clsAddUserScreen::ShowAddUserScreen();
	}

	static void _deleteUserScreen()
	{
		//cout << "\t delete User screen will be here soon\n";
		clsDeleteUserScreen::showDeleteUserScreen();
	}

	static void _updateUserScreen()
	{
		//cout << "\t update Users screen will be here soon\n";
		clsUpdateUserScreen::showUpdateUserScreen();
	}

	static void _findUserScreen()
	{
		//cout << "\t find Users screen will be here soon\n";
		clsFindUserScreen::showFindUserScreen();
	}

	static void _mainMenu()
	{
		cout << "\t main menu screen will be here soon\n";
	}

	static void _goBackToUsersMenu()
	{
		cout << "\t\t press any key to go back to main menu......\n";
		system("pause>0");
		showUsersMenu();
	}

	static void _performUsersMenuOption(enUsers choice)
	{
		switch (choice)
		{
		case enUsers::showUsers:
			system("cls");
			_showListUsersScreen();
			_goBackToUsersMenu();
			break;

		case enUsers::addUser:
			system("cls");
			_addUserScreen();
			_goBackToUsersMenu();
			break;

		case  enUsers::deleteUser:
			system("cls");
			_deleteUserScreen();
			_goBackToUsersMenu();
			break;

		case  enUsers::updateUsers:
			system("cls");
			_updateUserScreen();
			_goBackToUsersMenu();
			break;

		case  enUsers::findUsers:
			system("cls");
			_findUserScreen();
			_goBackToUsersMenu();
			break;

		case enUsers::mainMenu:
			system("cls");
			//clsMainScreen::showMainMenu();
			break;
		}
	}


public:

	static void showUsersMenu()
	{
		if (!checkAccessRights(clsUsers::enPermission::pMangeUsers))
		{
			return; // will out from the function 
		}

		system("cls");
		_drawScreenHeader("\t Manage User Menu Screen");

		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << "\t      Manage Users Main Screen\n";
		cout << setw(37) << left << "" << "======================================\n";
		cout << setw(37) << left << "" << "\t[1] List users\n";
		cout << setw(37) << left << "" << "\t[2] Add user\n";
		cout << setw(37) << left << "" << "\t[3] Delete user\n";
		cout << setw(37) << left << "" << "\t[4] Update user\n";
		cout << setw(37) << left << "" << "\t[5] Find user\n";
		cout << setw(37) << left << "" << "\t[6] Main Menu\n";
		cout << setw(37) << left << "" << "======================================\n";
		_performUsersMenuOption((enUsers)_readUsersMainMenuOption());
	}


};

