#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsPerson.h"
#include <vector>


using  namespace  std;


class  clsUsers : public clsPerson
{
	enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
	
	enMode _mode;
	string _userName;
	string _password;
	int    _permission;
	struct stLoginRegisterRecord;
	
	bool _markForDelete = false;

	string _registUserIntoString(string separator = "#//#")
	{
		string dataRecord = "";

		dataRecord += clsDate::GetSystemDateTimeString() + separator;
		dataRecord += userName + separator;
		dataRecord += clsString::encryptText(password) + separator;
		dataRecord += to_string(permission);

		return dataRecord;
	}

	static stLoginRegisterRecord _registerUserInttoObject(string line, string  separator = "#//#")
	{
		stLoginRegisterRecord LoginRegisterRecord;

		vector<string> LoginRegisterDataLine =  clsString::Split(line, separator);
		
		LoginRegisterRecord.date = LoginRegisterDataLine[0];
		LoginRegisterRecord.userName = LoginRegisterDataLine[1];
		LoginRegisterRecord.password = clsString::decryptText(LoginRegisterDataLine[2]);
		LoginRegisterRecord.permission = stoi(LoginRegisterDataLine[3]);

		return LoginRegisterRecord;
	}

	static clsUsers _convertLineToObject(string line, string  separator = "#//#")
	{
		vector <string> vUsers;
		vUsers = clsString::Split(line, separator);
		return clsUsers( enMode::updateMode, vUsers[0], vUsers[1], vUsers[2], vUsers[3], 
						 vUsers[4], vUsers[5], stoi(vUsers[6]));
	}

	static string _convertUserObjectToLine(clsUsers user, string separator = "#//#")
	{
		string userRecord = "";
		userRecord += user.fristName + separator;
		userRecord += user.lastName + separator;
		userRecord += user.email + separator;
		userRecord += user.phone + separator;
		userRecord += user.userName + separator;
		userRecord += user.password + separator;
		userRecord += to_string(user.permission);
		return userRecord;
	}

	static clsUsers _getEmptyUserObject()
	{
		return clsUsers( enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsUsers> _loadUserDataFromFile(string fileName)
	{
		vector<clsUsers> vUser;
		fstream myFile;
		myFile.open(fileName, ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline( myFile, line))
			{
				clsUsers user =  _convertLineToObject(line);
				vUser.push_back(user);
			}
			myFile.close();
		}
		return vUser;
	}

	static void _saveClientDataToFile(vector <clsUsers> vUser)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out);// write mode

		if (myFile.is_open())
		{
			string dataLine;

			for (clsUsers user : vUser)
			{
				if (user._markForDelete == false)
				{
					dataLine = _convertUserObjectToLine(user);
					myFile << dataLine << endl;
				}

			}
			myFile.close();
		}

	}

	 void _addDataToFile(string dataLine)
	{
		fstream myFile;
		myFile.open("Users.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;

			myFile.close();
		}
	}

	 void _addNew()
	{
		_addDataToFile(_convertUserObjectToLine(*this));
	}

	 void _update()
	 {
		 vector<clsUsers> vUser = _loadUserDataFromFile("User.txt");

		 for (clsUsers& user : vUser)
		 {
			 if (user.userName == userName)
			 {
				 user = *this;
				 break;
			 }
		 }
		 _saveClientDataToFile(vUser);

	 }

public :

	struct stLoginRegisterRecord
	{
		string date;
		string userName;
		string password;
		int    permission;
	};

	clsUsers(enMode mode, string fristName, string lastName, string email, string phone
		,string userName, string password, int permission)
		: clsPerson(fristName, lastName, email, phone)
	{
		_mode = mode;
		_userName = userName;
		_password = password;
		_permission = permission;
	}

	bool isEmpty()
	{
		return (_mode == enMode::emptyMode);
	}

	string getUserName()
	{
		return  _userName;
	}

	void setUserName(string userName)
	{
		_userName = userName;
	}

	__declspec(property(get = getUserName, put = setUserName))  string userName;


	 
	void setPassword(string  password)
	{
		_password = password;
	}

	string getPassword()
	{
		return  _password;
	}

	__declspec(property(get = getPassword, put = setPassword))  string password;

	void setPermissinon(int  permission)
	{
		_permission = permission;
	}

	int getPermission()
	{
		return  _permission;
	}

	__declspec(property(get = getPermission, put = setPermissinon))  int permission;


	static clsUsers find(string userName)
	{
		fstream myFile;

		myFile.open("Users.txt", ios::in);
		
		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsUsers user = _convertLineToObject(line);
				if (user.userName == userName)
				{
					myFile.close();
					return user;
				}
			}
			myFile.close();
		}
		return _getEmptyUserObject();
	}

	static clsUsers find(string userName, string password)
	{
		fstream myFile;

		myFile.open("Users.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsUsers user = _convertLineToObject(line);
				if (user.userName == userName  && user.password == password)
				{
					myFile.close();
					return user;
				}
			}
			myFile.close();
		}
		return _getEmptyUserObject();
	}

	static bool isUserExist(string userName)
	{
		clsUsers user = clsUsers::find(userName);
		return (!user.isEmpty());
	}

	enum enPermission {
		pAllList = -1, pShowclientList = 1, pAddClient = 2, pDeleteClietn = 4, pUpdateClient = 8, pFindClient = 16,
		pTrancaction = 32, pMangeUsers = 64, pLogRegister = 128, pCurrency = 256
	};

	static clsUsers getAddNewUserObject(string userName)
	{
		return clsUsers(enMode::addNewMode, "", "", "", "", userName, "", 0);
	}

	enum enSaveResults { svFailedEmptyObject = 0, svSucceeded = 1, svFailedAccountNumberExists = 2};

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::emptyMode:
			if (isEmpty())
			{
				return enSaveResults::svFailedEmptyObject;
			}
		case enMode::updateMode:

			_update();
			return enSaveResults::svSucceeded;
			break;
			
		case enMode::addNewMode:
			
			if (clsUsers::isUserExist(_userName))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_addNew();
				_mode = enMode::updateMode;
				return enSaveResults::svSucceeded;
				break;
			}
		}
	}

	bool deleted()
	{
		vector<clsUsers> vUser = _loadUserDataFromFile("User.txt");

		for (clsUsers& user : vUser)
		{
			if (user.userName == userName)
			{
				user._markForDelete = true;
				break;
			}
		}
		_saveClientDataToFile(vUser);
		*this = _getEmptyUserObject();
		return true;
	}

	static vector<clsUsers> getUsersList()
	{
		return _loadUserDataFromFile("Users.txt");
	}

	static vector<stLoginRegisterRecord> getLogRegisterList()
	{
		vector< stLoginRegisterRecord> vLoginRegisterRecord;
		fstream myFile;
		myFile.open("LoginRegister.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			stLoginRegisterRecord LoginRegisterRecord;
			while (getline(myFile, line))
			{
				LoginRegisterRecord = _registerUserInttoObject(line);
				vLoginRegisterRecord.push_back(LoginRegisterRecord);
			}
			myFile.close();
		}

		return vLoginRegisterRecord;
	}

	bool checkAccessPermission(enPermission permission)
	{
		if (this->permission == enPermission::pAddClient)
			return true;
		if ((this->permission & permission) == permission)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void registerLogIn()
	{
		string dataLine = _registUserIntoString();

		fstream myFile;
		myFile.open("LoginRegister.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;

			myFile.close();
		}
	}


};


