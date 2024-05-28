#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsDate.h"
#include "clsString.h"
#include "clsUtil.h"

using namespace std;


class clsInputValidate
{
public:

	static bool isNumberBetween(short number, short from, short to)
	{
		if (number >= from && number <= to)
			return true;
		else
			return false;
	}

	static bool isNumberBetween(int number, int from, int to)
	{
		if (number >= from && number <= to)
			return true;
		else
			return false;
	}

	static bool isNumberBetween(float number, float from, float to)
	{
		if (number >= from && number <= to)
			return true;
		else
			return false;
	}

	static bool isNumberBetween(double number, double from, double to)
	{
		if (number >= from && number <= to)
			return true;
		else
			return false;
	}

	static bool isDateBetween(clsDate date, clsDate from, clsDate to)
	{
		// to > from
		if (clsDate::IsDate1AfterDate2(date, from) || clsDate::IsDate1EqualDate2(date, from)
			&&
			(clsDate::IsDate1BeforeDate2(date, to) || clsDate::IsDate1EqualDate2(date, to)))
		{
			return true;
		}

		//from > to
		if (clsDate::IsDate1AfterDate2(date, to) || clsDate::IsDate1EqualDate2(date, to)
			&&
			(clsDate::IsDate1BeforeDate2(date, from) || clsDate::IsDate1EqualDate2(date, from)))
		{
			return true;
		}
		return false;

	}

	static int  readIntNumber(string errorMesssage = "Invalid Number, please enter a valid Number\n")
	{
		int number;
		while(!(cin>> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMesssage;
		}
		return number;
	}

	static int  readIntNumberBetween(int from, int to, string errorMessage ="number is not between the two number, enter again \n")
	{
		int number = readIntNumber();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = readIntNumber();
		}
		return number;
	}
	
	static double readDoubleNumber(string errorMesssage = "Invalid Number, please enter a valid Number\n")
	{
		double number;
		while (!(cin >> number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << errorMesssage;
		}
		return number;
	}

	static double  readDoubleNumberBetween(double from, double to, string errorMessage = "number is not between the two number, enter again \n")
	{
		double number = readIntNumber();
		while (!isNumberBetween(number, from, to))
		{
			cout << errorMessage;
			number = readIntNumber();
		}
		return number;
	}

	static bool isValideDate(clsDate date)
	{
		return clsDate::IsValidDate(date);
	}

	static string readString()
	{
		string  s1;
		getline(cin  >>  ws, s1);
		return  s1;
	}

};

