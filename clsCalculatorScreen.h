#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsCalculatorScreen : protected clsScreen
{
	static void _printCurrencyCard(clsCurrency currency, string message = "\n Currency Card")
	{
		cout << message;
		cout << "\n_________________________";
		cout << "\nCountry        : " << currency.country();
		cout << "\nCode           : " << currency.currencyCode();
		cout << "\nName           : " << currency.currencyName();
		cout << "\nRate(1$)       : " << currency.rate();
		cout << "\n_________________________\n";
	}

	static clsCurrency _getCurrency(string message)
	{
		string currencyCode = "";
		cout << message;
		currencyCode = clsInputValidate::readString();

		while (!clsCurrency::isCurrencyExist(currencyCode))
		{
			cout << "\nCurrency NOT Found, choose another Currency : ";
			currencyCode = clsInputValidate::readString();

		}
		clsCurrency currecny = clsCurrency::findByCode(currencyCode);
		return currecny;
	}

	static double _readAmount()
	{
		double amount = 0;

		cout << "\nEnter amount to Exchange : ";
		amount == clsInputValidate::readIntNumber();
		return amount;
	}

	static void _printCalculatorResults(double amount, clsCurrency currencyFrom, clsCurrency currencyTo)
	{
		_printCurrencyCard(currencyFrom, "\n Converting From : ");

		double amountInUSD = currencyFrom.convertToUSD(amount);

		cout << endl << amount << " " << currencyFrom.currencyCode() << " = " << amountInUSD << "USD" << endl;

		if (currencyTo.currencyCode() == "USD")
		{
			return;
		}

		cout << "\nConverting From USD To : \n";
		_printCurrencyCard(currencyTo, "\n To : ");

		double amountInCurrencyTo = currencyFrom.convertToOtherCurrecny(amount, currencyTo);

		cout << endl << amount << " " << currencyFrom.currencyCode() << " = " << amountInCurrencyTo << currencyTo.currencyCode() << endl;


	}

public:

	static void showCurrencyCalculatorScreen()
	{
		char Continue = 'n';

		while (Continue == 'y' || Continue == 'Y')
		{

			_drawScreenHeader("\t  Currency Calculator Screen");
			clsCurrency currencyFrom = _getCurrency("\nPlease enter currency1 code : ");
			clsCurrency currencyTo = _getCurrency("\nPlease enter currency2 code : ");

			double amount = _readAmount();

			_printCalculatorResults(amount, currencyFrom, currencyTo);

			cout << "\nDo you want to perform another exchange? (y or n )?  ";
			cin >> Continue;

		}

	}
};

