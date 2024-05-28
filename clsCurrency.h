#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "clsString.h"

using namespace std;

class clsCurrency
{
	enum enMode { emptyMode = 0, updateMode = 1};
	enMode _mode;

	string _country;
	string _currencyCode;
	string _currencyName;
	float  _rate;

	static clsCurrency _convertLineToObject(string line, string separator = "#//#")
	{
		vector <string> vCurrency; 
		vCurrency = clsString::Split(line, separator);

		return clsCurrency(enMode::updateMode, vCurrency[0], vCurrency[1], vCurrency[2], stof(vCurrency[3]));
	}

	static string  _convertObjectToLine(clsCurrency currency, string separator = "#//#")
	{
		string dataRecord = "";

		dataRecord += currency.country() + separator;
		dataRecord += currency.currencyCode() + separator;
		dataRecord += currency.currencyName() + separator;
		dataRecord += to_string(currency.rate());

		return dataRecord;
	}
	
	static clsCurrency _getEmptyCurrencyObject()
	{
		return clsCurrency(enMode::emptyMode, "", "", "", 0);
	}

	static vector<clsCurrency> _loadDataFromFile()
	{
		vector<clsCurrency> vCurrency;
		fstream myFile;

		myFile.open("Currencies.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsCurrency currency = _convertLineToObject(line);
				vCurrency.push_back(currency);
			}

			myFile.close();
		}
		return vCurrency;
	}

	static void _saveDateToFile(vector<clsCurrency> & vCurrency )
	{
		fstream myFile;
		
		myFile.open("Currencies.txt", ios::out);

		string dataLine;
		if (myFile.is_open())
		{
			for (clsCurrency& currency : vCurrency) 
			{
			 	dataLine = _convertObjectToLine(currency);
				myFile << dataLine << endl;
			}
			myFile.close();
		} 
	}

	void _update()
	{
		vector<clsCurrency> vCurrency = _loadDataFromFile();

		for (clsCurrency& currency : vCurrency)
		{
			if (currency.currencyCode() == currencyCode())
			{
				currency = *this;
				break;
			}
			
		}
		_saveDateToFile(vCurrency);

	}

public	:

	clsCurrency(enMode mode , string country, string currencyCode, string currencyName, float rate)
	{
		_mode = mode;
		_country = country;
		_currencyCode = currencyCode;
		_currencyName = currencyName;
		_rate = rate;
	}

	bool isEmpty()
	{
		return (_mode == enMode::emptyMode);
	}

	string country()
	{
		return _country;
	}

	string currencyCode()
	{
		return _currencyCode;
	}

	string currencyName()
	{
		return _currencyName;
	}

	void updateRate(float newRate)
	{
		_rate = newRate;
		_update();
	}

	float rate()
	{
		return _rate;
	}

	//__declspec(property(get = rate, put = setRate))  float rate;


	static clsCurrency findByCode(string currencyCode)
	{
		currencyCode = clsString::UpperAllString(currencyCode);

		fstream myFile;

		myFile.open("Currencies.txt", ios::in);

		string dataLine;
		if (myFile.is_open())
		{

			string dataLine;
			while (getline(myFile, dataLine))
			{
				clsCurrency currency = _convertLineToObject(dataLine);
				if (currency.currencyCode() == currencyCode)
				{
					myFile.close();
					return currency;
				}
			}
			myFile.close();
		}
		return _getEmptyCurrencyObject();
	}

	static clsCurrency findByCountry(string country)
	{
		country = clsString::UpperAllString(country);

		//vector<clsCurrency> vCurrency = _loadDataFromFile();
		fstream myFile;

		myFile.open("Currencies.txt", ios::in);

		string dataLine;
		if (myFile.is_open())
		{
			while (getline(myFile, dataLine))
			{
				clsCurrency currency = _convertLineToObject(dataLine);
				if (clsString::UpperAllString(currency.country()) == country)
				{
					myFile.close();
					return currency;
				}
			}
			myFile.close();
		}
	}

	static bool isCurrencyExist(string currencyCode)
	{
		clsCurrency currency = findByCode(currencyCode);
			return(!currency.isEmpty());
	}

	static vector<clsCurrency> getCurrenciesList()
	{ 
		return _loadDataFromFile();
	}

	double convertToUSD(double amount)
	{
		return (double)(amount / rate());
	}

	double convertToOtherCurrecny(double amount, clsCurrency OtherCurrency)
	{
		double amountInUSD = convertToUSD(amount);

		if (OtherCurrency.currencyCode() == "USD")
		{
			return amountInUSD;
		}

		return (double)(amountInUSD * OtherCurrency.rate());
	}
};


