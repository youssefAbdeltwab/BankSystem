#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsScreen.h"

class clsFindCurrency : protected clsScreen
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

	static void _showResults(clsCurrency &currency)
	{

		if (!currency.isEmpty())
		{
			cout << "\nCurrency found :-)\n";

			_printCurrencyCard(currency);
		}
		else
		{
			cout << "\nCurrency NOT found :-)";

		}
	}

public:

	static void showFindCurrencyScreen()
	{
		_drawScreenHeader("\t  Find Currency Screen");

		
		short answer = 0;

		cout << "\nFind by : [1] Code or [2] Country  :  ";
		answer = clsInputValidate::readIntNumberBetween(1, 2, "\nplease enter right choice");

		if (answer == 1)
		{
			string currencyCode = "";

			cout << "\nPlease enter Currency Code : ";
			currencyCode = clsInputValidate::readString();

			clsCurrency currency1 =  clsCurrency::findByCode(currencyCode);
			_showResults(currency1);

		}
		else if (answer == 2)
		{
			string country = "";

			cout << "\nPlease enter Country Name : ";
			country = clsInputValidate::readString();

			clsCurrency currency1 = clsCurrency::findByCountry(country);
			_showResults(currency1);
		}
		
	}
};

