#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"

using namespace std;

class clsListCurrencyScreen : protected clsScreen
{

	static void _printCurrencyRecordline(clsCurrency currency)
	{
		cout << setw(8) << left << "" <<  "| " << setw(30) << left << currency.country();
		cout << "| " << setw(8)  << left << currency.currencyCode();
		cout << "| " << setw(45) << left << currency.currencyName();
		cout << "| " << setw(10) << left << currency.rate();
	}


public: 

	static void showCurrencyList()
	{
		vector<clsCurrency> vCurrency = clsCurrency::getCurrenciesList(); 

		string title = "\tCurrencies List Screen";
		string subTitle = "\t(" + to_string(vCurrency.size()) + ") currency";

		_drawScreenHeader(title, subTitle);

		cout << setw(8) << left << "" << "\n\t_____________________________________________________________________________________________________________\n\n";
		cout << setw(8) << left << "" << "| " << setw(30) << left << "Country";
		cout << "| " << left << setw(8) << "Code";
		cout << "| " << left << setw(45) << "Name";
		cout << "| " << left << setw(10) << "Rate(1$)";
		cout << setw(8) << left << "\n\t_____________________________________________________________________________________________________________\n";


		if (vCurrency.size() == 0)
		{
			cout << "\n\t\tNo available currency";
		}
		else
		{
			for (clsCurrency currency : vCurrency)
			{
				_printCurrencyRecordline(currency);
				cout << endl;
			}
		}
		
		cout << setw(8) << left << "\n_____________________________________________________________________________________________________________\n\n\n";

	}
};

