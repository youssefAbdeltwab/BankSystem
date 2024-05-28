#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<iomanip>
#include "bankUsers.h"

using  namespace std;
 namespace bank

{
	 void mainMenu();
	 void transactionMenu();
	 void goBackToTransactionMenu();

	 enum  enOption { show = 1,  add = 2, deleted = 3, update = 4, find = 5, transaction = 6,   exit = 7};
	 enum  enTransaction  { deposit = 1, withdraw = 2, totalBalance = 3, mainMenue = 4 };
	 const  string clientFileName = "clients.txt";

	 struct stClientData {

		 string AccountNumber;
		 string PinCode;
		 string ClientName;
		 string CllientPhone;
		 double AccountBalance;
		 bool   markForDelete = false;

	 };

	 string  tab(short  numberOfTabs)
	 {
		 string  t = "";

		 for (short i = 0; i < numberOfTabs; i++)
		 {
			 t = t + "\t";
			 cout << t;
		 }
		 return  t;
	 }

	 string convertAllStringToLowerCase(string  s1)
	 {
		 for (int i = 0; i < s1.length(); i++)
		 {
			 if (s1[i] != ' ')
			 {
				 s1[i] = tolower(s1[i]);
			 }
			 return s1;

		 }
	 }

	 vector <string> splitString(string s1, string delim)
	 {
		 vector <string> vString;

		 short pos = 0;
		 string sWord;
		 while ((pos = s1.find(delim)) != std::string::npos)
		 {
			 sWord = s1.substr(0, pos);
			 if (sWord != " ")
			 {
				 vString.push_back(sWord);
			 }
			 s1.erase(0, pos + delim.length());
		 }

		 if (s1 != " ")
		 {
			 vString.push_back(s1);
		 }

		 return vString;
	 }
	 
	 string convertRecodToLine(stClientData clientData, string separator = "#//#")
	 {
		 string stringInLine;

		 stringInLine += clientData.AccountNumber + separator;
		 stringInLine += clientData.PinCode + separator;
		 stringInLine += clientData.ClientName + separator;
		 stringInLine += clientData.CllientPhone + separator;
		 stringInLine += to_string(clientData.AccountBalance);

		 return  stringInLine;
	 }

	 stClientData convertLineDateToRecord(string  s1, string  separator = "#//#")
	 {
		 stClientData  client;
		 vector<string> vClientData;

		 vClientData = splitString(s1, separator);

		 client.AccountNumber = vClientData[0];
		 client.PinCode = vClientData[1];
		 client.ClientName = vClientData[2];
		 client.CllientPhone = vClientData[3];
		 client.AccountBalance = stod(vClientData[4]);//  casting  to double

		 return client;
	 }

	 void printClientRecordData(stClientData clientData)
	 {
		 cout << "| " << setw(15) << left << clientData.AccountNumber;
		 cout << "| " << setw(10) << left << clientData.PinCode;
		 cout << "| " << setw(40) << left << clientData.ClientName;
		 cout << "| " << setw(12) << left << clientData.CllientPhone;
		 cout << "| " << setw(12) << left << clientData.AccountBalance;
	 }

	 bool clientExistByAccountNumber(string fileName, string accountNumber)
	 {
		 vector<stClientData> vClient;
		 fstream myFile;
		 myFile.open(fileName, ios::in);// read mode

		 if (myFile.is_open())
		 {
			 string line;
			 stClientData client;

			 while (getline(myFile, line))
			 {
				 client = convertLineDateToRecord(line);
				 if (client.AccountNumber == accountNumber)
				 {
					 myFile.close();
					 return true;
				 }
				 vClient.push_back(client);

			 }
			 myFile.close();
		 }
		 return  false;
	 }

	 stClientData readNewClinetDate()
	 {
		 stClientData NewClient;

		 cout << "Enter Account Number? ";
		 getline(cin >> ws, NewClient.AccountNumber);

		 while (clientExistByAccountNumber(clientFileName, NewClient.AccountNumber))
		 {
			 cout << "client with account number [" << NewClient.AccountNumber << "] already exist , enter another account number  ";
			 getline(cin >> ws, NewClient.AccountNumber);
		 }

		 cout << "Enter pincode? ";
		 getline(cin, NewClient.PinCode);

		 cout << "Enter name? ";
		 getline(cin, NewClient.ClientName);

		 cout << "Enter phone? ";
		 getline(cin, NewClient.CllientPhone);

		 cout << "Enter balance? ";
		 cin >> NewClient.AccountBalance;

		 return NewClient;

	 }

	 void addDataLineToFile(string fileName, string  stDataLine)
	 {
		 fstream myFile;

		 myFile.open(fileName, ios::out | ios::app);

		 if (myFile.is_open())
		 {
			 myFile << stDataLine << endl;
			 myFile.close();
		 }
	 }

	 void addNewClient()
	 {
		 stClientData clientData;
		 clientData = readNewClinetDate();
		 addDataLineToFile(clientFileName, convertRecodToLine(clientData));
	 }

	 void addClients()
	 {
		 string addAgin = "yes";
		 do
		 {
			// system("cls");
			 cout << "add new client : \n\n";
			 addNewClient();
			 cout << "\nClient add successfully, Do you want to add new client?  yes/no ";
			 cin >> addAgin;

		 } while (convertAllStringToLowerCase(addAgin) == "yes");
	 }

	 vector <stClientData> loadDataFromFileToVector(string fileName)
	 {
		 vector<stClientData> vClientData;
		 fstream myFile;

		 myFile.open(fileName, ios::in);// read mode

		 if (myFile.is_open())
		 {
			 string line;
			 stClientData client;

			 while (getline(myFile, line))
			 {
				 client = convertLineDateToRecord(line);
				 vClientData.push_back(client);
			 }
			 myFile.close();
		 }
		 return vClientData;
	 }

	 string readClientAccountNumber()
	 {
		 string accountNumber = " ";
		 cout << "please enter client account number\n";
		 cin >> accountNumber;
		 return accountNumber;
	 }

	 void printClientsData(vector<stClientData> vClients)
	 {
		 cout << "\n\t\t\t\tclient list(" << vClients.size() << ")client (s)\n";
		 cout << "___________________________________________________________________________________\n";
		 cout << "| " << left << setw(15) << "Account Number";
		 cout << "| " << left << setw(10) << "Pin Code";
		 cout << "| " << left << setw(40) << "Client Name";
		 cout << "| " << left << setw(12) << "Phone";
		 cout << "| " << left << setw(12) << "Balance";
		 cout << "\n___________________________________________________________________________________\n";

		 for (stClientData client : vClients)
		 {
			 printClientRecordData(client);
			 cout << endl;
		 }

		 cout << "\n_______________________________________________________";
		 cout << "_________________________________________\n" << endl;
	 }

	 bool findClientByAccountNumber(stClientData& client, string accountNumber)
	 {
		 vector<stClientData> vClientData = loadDataFromFileToVector(clientFileName);
		
			 for (stClientData& c : vClientData)
			 {
				 if (c.AccountNumber == accountNumber)
				 {
					 client = c;
					 return true;
				 }
			 }  
		 return false;
	 }

	 void printClientsData(stClientData client, string accountNumber)
	 {
		 if (!findClientByAccountNumber(client, accountNumber))
		 {
			 cout << "\nclient with account number (" << accountNumber << ") is  not found!\n";

		 }
		 else
		 {
			 cout << "\nThe following are the client details  \n";
			 cout << "___________________________________________________________________________________\n";
			 cout << "| " << left << setw(15) << "Account Number";
			 cout << "| " << left << setw(10) << "Pin Code";
			 cout << "| " << left << setw(40) << "Client Name";
			 cout << "| " << left << setw(12) << "Phone";
			 cout << "| " << left << setw(12) << "Balance";
			 cout << "\n___________________________________________________________________________________\n";


			 printClientRecordData(client);
			 cout << endl;


			 cout << "\n_______________________________________________________";
			 cout << "_________________________________________\n" << endl;
		 }
	 }

	 bool markClientForDeleteByAccountNumber(vector <stClientData>& vClient, string accountNumber)
	 {
		 for (stClientData& c : vClient)
		 {
			 if (c.AccountNumber == accountNumber)
			 {
				 c.markForDelete = true;
				 return  true;
			 }
		 }
		 return  false;
	 }

	 vector<stClientData> saveClientDataToFile(string fileName, vector<stClientData>& vClient)
	 {
		 fstream  myFile;
		 myFile.open(fileName, ios::out);//  write  mode
		 string dataLine;

		 if (myFile.is_open())
		 {
			 for (stClientData& c : vClient)
			 {
				 if (c.markForDelete == false)
				 {
					 dataLine = convertRecodToLine(c);
					 myFile << dataLine << endl;
				 }
			 }
		 }
		 myFile.close();
		 return  vClient;

	 }

	 bool deleteClientByAccountNumber(vector<stClientData>& vClient, string accountNumber)
	 {
		 stClientData client;
		 string answer = "no";
		
		 if (findClientByAccountNumber(client, accountNumber))
		 {
			 printClientsData(client, accountNumber);


			 cout << "\n Are you wnat to delete account Number? (yes or no) ";
			 cin >> answer;


			 if (convertAllStringToLowerCase(answer) == "yes")
			 {
				 
					 markClientForDeleteByAccountNumber(vClient, accountNumber);
					 saveClientDataToFile(clientFileName, vClient);

					 //refresh  Clients
					 vClient = loadDataFromFileToVector(clientFileName);

					 cout << "\nclient has successfully deleted\n\n\n\n";
					 return  true;
			 }
			 else
			 {
				 cout << "\n client with account number (" << accountNumber << ") is  not found!\n\n\n";
				 return  false;
			 }
		 }
	 }

	 stClientData changeClinetDate(string accounNumber)
	 {
		 stClientData clieent;

		 clieent.AccountNumber = accounNumber;

		 cout << "\nEnter pincode? ";
		 getline(cin >> ws, clieent.PinCode);

		 cout << "Enter name? ";
		 getline(cin, clieent.ClientName);

		 cout << "Enter phone? ";
		 getline(cin, clieent.CllientPhone);

		 cout << "Enter balance? ";
		 cin >> clieent.AccountBalance;

		 return clieent;

	 }

	 bool updateClientByAccountNumber(vector<stClientData>& vClient, string accountNumber)
	 {
		 stClientData client;
		 string answer = "no";
		
			 if (findClientByAccountNumber(client, accountNumber))
			 {
				 printClientsData(client, accountNumber);
				 cout << "\n Are you wnat to update this client?( yes || no) ";
				 cin >> answer;


				 if (convertAllStringToLowerCase(answer) == "yes")
				 {
				
						 for (stClientData& c : vClient)
						 {
							 if (c.AccountNumber == accountNumber)
							 {
								 c = changeClinetDate(accountNumber);
								 break;
							 }
						 }
						 saveClientDataToFile(clientFileName, vClient);

						 cout << "\nclient has successfully updated\n\n\n\n\n";
						 return  true;
				 }
			 }
			 else
			 {
				 cout << "\n client with account number (" << accountNumber << ") is  not found!\n\n\n\n";
				 return  false;
			 }

	 }

	 void printClientBalance(stClientData clientData)
	 {
		 cout << "| " << setw(15) << left << clientData.AccountNumber;
		 cout << "| " << setw(10) << left << clientData.ClientName;
		 cout << "| " << setw(40) << left << clientData.AccountBalance;
	 }

	 void printTotalBalances(vector<stClientData> vClients)
	 {
		 cout << "\n\t\t\t\tBalances list(" << vClients.size() << ")client (s).\n";
		 cout << "___________________________________________________________________________________\n";
		 cout << "| " << left << setw(15) << "Account Number";
		 cout << "| " << left << setw(40) << "client Name";
		 cout << "| " << left << setw(12) << "Balance";
		 cout << "\n___________________________________________________________________________________\n";
		 
		 if (vClients.size() == 0)
		 {
			 cout << "\t\t\t\t no available balance in the system\n"; 
		 }

		 double totalBalance = 0;

		 for (stClientData client : vClients)
		 {
			 printClientBalance(client);
			 totalBalance += client.AccountBalance;
			 cout << endl;
		 }

		 cout << "\n_______________________________________________________";
		 cout << "_________________________________________\n" << endl;

		 cout << "\t\t\t\t Total Balance =  " << totalBalance << endl;
	 }

	 void showDeleteClientScreen()
	 {
		 cout << "\n-----------------------------------\n"; 
		 cout << "\tDelete Client Screen";
		 cout << "\n-----------------------------------\n";

		 vector<stClientData> vClient  =   loadDataFromFileToVector(clientFileName);
		 string accountNumber = readClientAccountNumber();
		 
		 deleteClientByAccountNumber(vClient, accountNumber);
	 }

	 void showUpdateClientScreen()
	 {
		 cout << "\n-----------------------------------\n";
		 cout << "\nupdate Client Screen";
		 cout << "\n-----------------------------------\n";

		 vector<stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 string accountNumber = readClientAccountNumber();

		 updateClientByAccountNumber(vClient, accountNumber);
	 }

	 void showAddClientScreen()
	 {
		 cout << "\n-----------------------------------\n";
		 cout << "\Add Client Screen";
		 cout << "\n-----------------------------------\n";

		 addClients();
	 }

	 void showFindClientScreen()
	 {
		 cout << "\n-----------------------------------\n";
		 cout << "\nfind Client Screen";
		 cout << "\n-----------------------------------\n";

		 vector<stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 string accountNumber = readClientAccountNumber();
		 stClientData client;

		 if (findClientByAccountNumber(client, accountNumber))
		 
			 printClientsData(client, accountNumber);
		 else   
			 cout << "\nClient with Account Number[" << accountNumber << "] is not found!"; 
	 }

	 void showAllClientsScreen()
	 {
		 vector <stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 printClientsData(vClient);
	 }

	 void ShowEndScreen()
	 { 
		 cout << "\n-----------------------------------\n"; 
		 cout << "\tProgram Ends :-)";   
		 cout << "\n-----------------------------------\n";
	 }

	 bool depositAmount(vector<stClientData> vClient, string accountNumber, double amount)
	 {
		 string answer = "no";

		 cout << "are you sure you want to perform this transaction? (yes or no)";
		 cin >> answer;

		 if (convertAllStringToLowerCase(answer) == "yes")
		 {
			 for (stClientData& c : vClient)
			 {
				 if (c.AccountNumber == accountNumber)
				 {
					 c.AccountBalance += amount;
					 
					 saveClientDataToFile(clientFileName, vClient);

					 cout << "\nTransaction has successfully done, New balance is : "<< c.AccountBalance;
					 return  true;
				 }
			 }
			
		 }
		 else
		 {
			 cout << "\nTransaction canceled by the user.\n\n";
			 return false;
		 }
	 }

	 void depositByAccountNumber(vector<stClientData> vClient, string accountNumber)
	 {
		 stClientData client;
		 double amount = 0;
		 short repeat = 0;
		 while ( !findClientByAccountNumber(client, accountNumber)) {
			 cout << "\nError: Invalid account number or client not found.\n";
			 cout << "Enter a valid account number: ";
			 cin >> accountNumber;
			 repeat++;
			 if (repeat > 4)
			 {
				 goBackToTransactionMenu();
			 }
		 }

	     cout << "please enter deposit amount?";
		 cin >> amount;

		printClientsData(client, accountNumber);

		depositAmount(vClient, accountNumber, amount);
		
	 }
	 
	 double getValidationWithdrawalAmount(stClientData client,double amount)
	 {
	
		 do
		 {
			 cout << "please enter withdraw amount?";
			 cin >> amount;

			 if (amount <= 0)
				 cout << "\nError: Withdrawal amount must be greater than 0.\n";
			 else if (amount > client.AccountBalance)
				 cout << "amount exceeds the balance, you can withdraw up to : " << client.AccountBalance << endl;


		 } while (amount <= 0 || amount > client.AccountBalance);

		 return amount;
	 }

	 void withdrawByAccountNumber(vector<stClientData> vClient, string accountNumber)
	 {
		 stClientData client;
		 double amount = 0;
		 short repeat = 0;

		 while (!findClientByAccountNumber(client, accountNumber)) {
			 cout << "\nError: Invalid account number or client not found.\n";
			 cout << "Enter a valid account number: ";
			 cin >> accountNumber;
			 
			 repeat++;
			 if (repeat > 4)
			 {
				 goBackToTransactionMenu();
			 }
		 }

		 printClientsData(client, accountNumber);

		 getValidationWithdrawalAmount(client, amount);

		 depositAmount(vClient, accountNumber, (amount * -1));
	 }

	 void showDepositScreen()
	 {
		 cout << "\n-----------------------------------\n";
		 cout << "\Deposit Screen";
		 cout << "\n-----------------------------------\n";

		 vector<stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 string accountNumber = readClientAccountNumber();

		 depositByAccountNumber(vClient, accountNumber);
	 }

	 void showWithDrawScreen()
	 {
		 cout << "\n-----------------------------------\n";
		 cout << "\Withdraw Screen";
		 cout << "\n-----------------------------------\n";

		 vector<stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 string accountNumber = readClientAccountNumber();

		 withdrawByAccountNumber(vClient, accountNumber);
	 }

	 void showTotalBalanceScreen()
	 {
		 vector<stClientData> vClient = loadDataFromFileToVector(clientFileName);
		 printTotalBalances(vClient);
	 }

	 short readUserChoice()
	 {
		 short answer;
		 cout << "choose what do you want to do? [1-7]";
		 cin >> answer;

		 return  answer;
	 }

	 short readTransactionChoice()
	 {
		 short answer;
		 cout << "choose what do you want to do? [1-4]";
		 cin >> answer;

		 return  answer;
	 }

	 void goBackToMainMenu()
	 {
		 cout << "press any key to  go back to  main menu......\n";
		 system("pause>0");
		 mainMenu();
	 }

	 void goBackToTransactionMenu()
	 {
		 cout << "press any key to  go back to  main menu......\n";
		 system("pause>0");
		 transactionMenu();
	 }

	 void setTransaction(enTransaction transactinChoice)
	 {
		 switch (transactinChoice)
		 {
		 case enTransaction::deposit:
			 system("cls");
			 showDepositScreen();
			 goBackToTransactionMenu();
			 break;

		 case enTransaction::withdraw:
			 system("cls");
			 showWithDrawScreen();
			 goBackToTransactionMenu();
			 break;

		 case  enTransaction::totalBalance:
			 system("cls");
			 showTotalBalanceScreen();
			 goBackToTransactionMenu();
			 break;

		 case enTransaction::mainMenue:
			 system("cls");
			 mainMenu();
			 break;
		 }
	 }

	 void transactionMenu()
	 {
		 system("cls");
		 cout << "======================================\n";
		 cout << tab(3) << "Transaction Main Screen" << tab(3) << endl;
		 cout << "======================================\n";
		 cout << "[1] Deposit\n";
		 cout << "[2] Withdraw\n";
		 cout << "[3] Totalbalance\n";
		 cout << "[4] Main Menu\n";
		 cout << "======================================\n";
		 setTransaction((enTransaction)readTransactionChoice());
	 }

	 void setOpertaion(enOption userChoice)
	 {
		 switch (userChoice)
		 {
		 case enOption::show:
			 system("cls");
			 showAllClientsScreen();
			 goBackToMainMenu();
			 break;

		 case enOption::add:
			 system("cls");
			 showAddClientScreen();
			 goBackToMainMenu();		
			 break;

		 case  enOption::deleted:
			 system("cls");
			 showDeleteClientScreen();
			 goBackToMainMenu();			
			 break;

		 case enOption::update:
			 system("cls");
			 showUpdateClientScreen();
			 goBackToMainMenu(); 
			 break;

		 case enOption::find:
			 system("cls");
			 showFindClientScreen();
			 goBackToMainMenu(); 
			 break;

		 case enOption::transaction:
			 system("cls");
			 transactionMenu();
			 break;
				
		 case enOption::exit:
			 system("cls");
			 ShowEndScreen();
			 break;
		 }
	
	 }
	
	 void mainMenu()
	 {
		 system("cls");
		 cout << "======================================\n";
		 cout << tab(3) << " Main Menu Screen" << tab(3) << endl;
		 cout << "======================================\n";
		 cout << "[1] Show client list\n";
		 cout << "[2] Add new client\n";
		 cout << "[3] Delete client\n";
		 cout << "[4] Update client info \n";
		 cout << "[5] Find client\n";
		 cout << "[6] Transactios\n";
		 cout << "[7] Exit\n";
		 cout << "======================================\n";
		 setOpertaion((enOption)readUserChoice());
	 }

}

