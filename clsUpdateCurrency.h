#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsUpdateCurrency : protected clsScreen
{
	static void _printCurrencyCard(clsCurrency currency)
	{
		cout << "\nCurrency Card :  ";
		cout << "\n_________________________";
		cout << "\nCountry        : " << currency.country();
		cout << "\nCode           : " << currency.currencyCode();
		cout << "\nName           : " << currency.currencyName();
		cout << "\nRate(1$)       : " << currency.rate();
		cout << "\n_________________________\n";
	}


public:

	static void showUpdateCurrecnyScreen()
	{
		_drawScreenHeader("\t  Update Currency Screen");
		string currencyCode = "";
		char answer = 'n';
		float newRate = 0;


		cout << "\nPlease enter Currency Code : ";
		currencyCode = clsInputValidate::readString();

		while (!clsCurrency::isCurrencyExist(currencyCode))
		{
			cout << "\nCurrency NOT Found, choose another Currency : ";
			currencyCode = clsInputValidate::readString();

		}

		clsCurrency currency1 = clsCurrency::findByCode(currencyCode);
		_printCurrencyCard(currency1);

		cout << "\nAre you sure you want to update the Currency rate? (y or n) :  ";
		cin >> answer;

		if (answer == 'y' || answer == 'Y')
		{
			cout << "\nUpdate Currency Rate: ";
			cout << "\n_________________________\n";
			cout << "\nEnter New rate :  ";
			newRate = clsInputValidate::readDoubleNumber();
			currency1.updateRate(newRate);

			_printCurrencyCard(currency1);

		}
	}
};

