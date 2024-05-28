#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "clsString.h"
#include "clsDate.h"
#include "clsPerson.h"
#include "global.h"
using  namespace  std;


class clsBankClient : public clsPerson
{
private:

	enum enMode { emptyMode = 0, updateMode = 1, addNewMode = 2 };
	enMode  _mode;

	string  _accountNumber;
	string  _pinCode;
	double  _accountBalance;
	bool   _markedForDelete = false;

	struct stLogTransfer;

	static clsBankClient _convertLineToObject(string line, string  separator = "#//#")
	{
		vector<string> vClient;
		vClient = clsString::Split(line, separator);

		return  clsBankClient(enMode::updateMode, vClient[0], vClient[1], vClient[2], vClient[3], vClient[4],
								vClient[5], stod(vClient[6]));
	}

	static string _convertClientObjectToLine(clsBankClient client, string separator = "#//#")
	{
		string clientRecord = "";

		clientRecord += client.fristName + separator;
		clientRecord += client.lastName + separator;
		clientRecord += client.email + separator;
		clientRecord += client.phone + separator;
		clientRecord += client.getAccountNumber() + separator;
		clientRecord += client.pinCode + separator;
		clientRecord += to_string(client.accountBalance);

		return clientRecord;
	}

	string _logTransferToString(clsBankClient destinationClient, string userName, double amount, string separator = "#//#")
	{
		string dataRecord = "";

		dataRecord += clsDate::GetSystemDateTimeString() + separator;
		dataRecord += _accountNumber + separator;
		dataRecord += destinationClient.getAccountNumber() + separator;
		dataRecord += to_string(amount) + separator;
		dataRecord += to_string(accountBalance) + separator;
		dataRecord += to_string(destinationClient.accountBalance) + separator;
		dataRecord += userName;

		return dataRecord;
	}

	static stLogTransfer _convertLofTransferToObject(string line,string separator = "#//#")
	{
		stLogTransfer transfer;

		vector<string> dataLine = clsString::Split(line, separator);

		transfer.date = dataLine[0];
		transfer.sourceAccountNumber = dataLine[1];
		transfer.destinationAccountNumber = dataLine[2];
		transfer.amount = stod(dataLine[3]);
		transfer.sourceBalance = stod(dataLine[4]);
		transfer.destinationBalance = stod(dataLine[5]);
		transfer.userName = dataLine[6];
		
		return transfer;
	}

	static clsBankClient _getEmptyClientObject()
	{
		return clsBankClient(enMode::emptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _loadClientDataFromFile()
	{
		vector<clsBankClient> vClient;

		fstream myFile;

		myFile.open("Clients.txt", ios::in);//  read only mode

		if (myFile.is_open())
		{
			string line;
			while (getline(myFile, line))
			{
				clsBankClient client = _convertLineToObject(line);
				vClient.push_back(client);
			}

			myFile.close();

		}
		return vClient;
	}

	static void _saveClientDataToFile(vector <clsBankClient>& vClient)
	{
		fstream  myFile;
		myFile.open("Clients.txt", ios::out);  //  write mode

		string dataLine;
		if (myFile.is_open())
		{
			for (clsBankClient c : vClient)
			{
				if (c._markedForDelete == false)
				{
					dataLine = _convertClientObjectToLine(c);
 				}
			}
			myFile.close();
		}
	}

	 void _update()
	{
		vector <clsBankClient> _vClient;
		_vClient = _loadClientDataFromFile();

		for (clsBankClient& c : _vClient)
		{
			if (c.getAccountNumber() == getAccountNumber())
			{
				c = *this;
				break;
			}
		}
		_saveClientDataToFile(_vClient);
	}
	    
	 void _addDateLineToFile(string dataLine)
	 {
		 fstream myFile;
		 myFile.open("Clients.txt", ios::out | ios::app);

		 if (myFile.is_open())
		 {
			
			 myFile << dataLine << endl;
		 }
		 myFile.close();
	 }

	 void _addNew()
	 {
		 _addDateLineToFile(_convertClientObjectToLine(*this));
	 }

public:

	struct stLogTransfer
	{
		string date;
		string sourceAccountNumber;
		string destinationAccountNumber;
		double amount;
		double sourceBalance;
		double destinationBalance;
		string userName;
	};

	clsBankClient(enMode  mode, string fristName, string lastName, string email, string  phone
		, string accountNumber, string pinCode, double accountBalance) :
		clsPerson(fristName, lastName, email, phone)
	{
		_mode = mode;
		_accountNumber = accountNumber;
		_pinCode = pinCode;
		_accountBalance = accountBalance;
	}

	bool isEmpty()
	{
		return  (_mode == enMode::emptyMode);
	}

	string getAccountNumber()
	{
		return  _accountNumber;
	}

	void setPinCode(string  pinCode)
	{
		_pinCode = pinCode;
	}

	string getPinCode()
	{
		return  _pinCode;
	}

	__declspec(property(get = getPinCode, put = setPinCode))  string pinCode;


	void setAccountBalance(double accountBalance)
	{
		_accountBalance = accountBalance;
	}

	double getAccountBalance()
	{
		return  _accountBalance;
	}

	__declspec(property(get = getAccountBalance, put = setAccountBalance))  double  accountBalance;


	static clsBankClient find(string accountNumber)
	{

		fstream  myFile;
		myFile.open("Clients.txt", ios::in);  //read  only  mode


		if (myFile.is_open())
		{
			string  line;
			while (getline(myFile, line))
			{
				clsBankClient  client = _convertLineToObject(line);
				if (client.getAccountNumber() == accountNumber)
				{
					myFile.close();
					return  client;
				}
			}
			myFile.close();
		}
			return _getEmptyClientObject();
	}

	static clsBankClient find(string accountNumber, string pinCode)
	{
		fstream  myFile;
		myFile.open("Clients.txt", ios::in);  //read  only  mode


		if (myFile.is_open())
		{
			string  line;
			while (getline(myFile, line))
			{
				clsBankClient  client = _convertLineToObject(line);
				if (client.getAccountNumber() == accountNumber && client.pinCode == pinCode);
				{
					myFile.close();
					return  client;
				}
			}
			myFile.close();

		}
		return _getEmptyClientObject();
	}

	static bool isClientExist(string accountNumber)
	{
		clsBankClient  client = clsBankClient::find(accountNumber);
		return (!client.isEmpty());
	}

	enum enSaveResults { svFailedEmptyObject = 0,  svSucceeded = 1, svFailedAccountNumberExists = 2};

	enSaveResults save()
	{
		switch (_mode)
		{
		case enMode::emptyMode:
			return enSaveResults::svFailedEmptyObject;

		case enMode::updateMode:
			_update();
			return enSaveResults::svSucceeded;
			break;

		case  enMode::addNewMode:
			
			if (clsBankClient::isClientExist(_accountNumber))
			{
				return enSaveResults::svFailedAccountNumberExists;
			}
			else
			{
				_addNew();

				_mode = enMode::updateMode;
				return enSaveResults::svSucceeded;
			}
		}
	}

	static clsBankClient getAddNewClientObject(string accountNumber)
	{
		return clsBankClient(enMode::addNewMode, "", "", "", "", accountNumber, "", 0);
	}

	bool deleted()
	{
		vector<clsBankClient> vClient;
		vClient = _loadClientDataFromFile();

		for (clsBankClient& c : vClient)
		{
			if (c.getAccountNumber() == _accountNumber)
			{
				c._markedForDelete = true;
				break;
			}
		}
		_saveClientDataToFile(vClient);
		
		*this = _getEmptyClientObject();
		return  true;
	}

	static vector <clsBankClient> getClientList()
	{
		return _loadClientDataFromFile();
	}

	static double totalBalances( )
	{
		vector <clsBankClient> vClient = clsBankClient::getClientList();

		double totalBalances = 0;
		for (clsBankClient client : vClient)
		{
			totalBalances += client.accountBalance;
		}
		return totalBalances;

	}

	void deposit(double amount)
	{
		_accountBalance += amount;
		save();
	}

	bool withDraw(double amount)
	{
		if (amount > _accountBalance)
		{
			return false;
		}
		else
		{
			_accountBalance -= amount;
			save();
			return true;
		}
	
	}

	bool transfer(double amount, clsBankClient& destinationClient, string userName)
	{
		if (amount > accountBalance)
		{
			return false;
		}

		withDraw(amount);
		destinationClient.deposit(amount);
		logTransferIntoFile(destinationClient, userName ,  amount);
		return true;
	}

	void logTransferIntoFile(clsBankClient destinationClient, string userName, double amount)
	{
		string dataLine = _logTransferToString(destinationClient, userName, amount);

		fstream myFile;
		myFile.open("LogTransfer.txt", ios::out | ios::app);

		if (myFile.is_open())
		{
			myFile << dataLine << endl;

			myFile.close();
		}
	}

   	static vector<stLogTransfer>  getTransferList()
	{
		vector<stLogTransfer> vTransfer;
		fstream myFile;

		myFile.open("LogTransfer.txt", ios::in);

		if (myFile.is_open())
		{
			string line;
			stLogTransfer transfer;
			while (getline(myFile, line))
			{
				transfer = _convertLofTransferToObject(line);
				vTransfer.push_back(transfer);
			}
			myFile.close();
		}
		return vTransfer;
	}
};

