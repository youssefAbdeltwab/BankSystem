#pragma once
#include <iostream>
#include  <string>
#include "clsString.h"
#include  "clsDate.h"

using  namespace  std;


class clsPerson
{
private:

	string  _fristName;
	string  _lastName;
	string  _email;
	string  _phone;

public:

	clsPerson(string fristName,  string  lastName, string email, string phone)
	{
		_fristName = fristName;
		_lastName  = lastName;
		_email = email;
		_phone = phone;
	}

	void setFristName(string fristName)
	{
		_fristName = fristName;
	}  

	string getFristName()
	{
		return  _fristName;
	}

	__declspec(property(get = getFristName, put = setFristName))  string  fristName;

	void setLastName(string lastNane)
	{
		_lastName = lastNane;
	}

	string getLastName()
	{
		return  _lastName;
	}

	__declspec(property(get = getLastName, put = setLastName))  string  lastName;


	void setEmail(string email)
	{
		_email = email;
	}

	string getEmail()
	{
		return  _email;
	}

	__declspec(property(get = getEmail, put = setEmail))  string  email;


	void   setPhone(string phone)
	{
		_phone = phone;
	}

	string getPhone()
	{
		return  _phone;
	}

	__declspec(property(get = getPhone, put = setPhone))  string  phone;

	
	string fullName()
	{
		return  _fristName + " " + _lastName;
	}




};

