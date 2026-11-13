#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>
#include "clsUtil.h"
#include "clsPerson.h"
#include "clsString.h"
using namespace std;



class clsBankClient : public clsPerson
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	double _AccountBalance;
	bool _MarkForDelete = false;
	bool _IsLogin = false;

	static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
	{
		vector<string>vClientData;
		vClientData = clsString::Split(Line, Seperator);
		return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2],
			vClientData[3], vClientData[4], clsUtil::DecryptText(vClientData[5],2), stod(vClientData[6]));
	}
	static string _ConvertClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
	{
		string stClientRecord = "";
		stClientRecord += Client.FirstName + Seperator;
		stClientRecord += Client.LastName + Seperator;
		stClientRecord += Client.Email + Seperator;
		stClientRecord += Client.Phone + Seperator;
		stClientRecord += Client.AccountNumber() + Seperator;
		stClientRecord += clsUtil::EncryptText(Client.PinCode,2) + Seperator;
		stClientRecord += to_string(Client.AccountBalance);
		return stClientRecord;
	}

	static vector<clsBankClient>_LoadClientsDataFromFile(string FileName)
	{
		vector<clsBankClient>vClients;
		fstream MyFile;
		MyFile.open(FileName, ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return vClients;
	}
	static void _SaveClientsDataToFile(vector<clsBankClient>&vClients, string FileName)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out);//read Mode and over write All data.
		string DataLine = "";
		if (MyFile.is_open())
		{
			for (clsBankClient& C : vClients)
			{
				if (C._MarkForDelete == false)
				{
					//we only write record that are not marked for delete .
					DataLine = _ConvertClientObjectToLine(C);
					MyFile << DataLine << endl;
				}
			}
			MyFile.close();
		}
	}

	
	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	void _Update()
	{
		vector<clsBankClient>_vClients = _LoadClientsDataFromFile("Clients.txt");
		for (clsBankClient &C: _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients, "Clients.txt");
	}

	static void _AddDataLineToFile(string FileName, string stDataLine)
	{
		fstream MyFile;
		MyFile.open(FileName, ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << stDataLine << endl;
			MyFile.close();
		}
	}
	void _AddNew()
	{
		_AddDataLineToFile("Clients.txt", _ConvertClientObjectToLine(*this));
	}

	string _PrepareTransferLogInRecord(float Amount, clsBankClient DestinationClient,string UserName, string Seperator = "#//#")
	{
		string TransferLogRecord = "";
		TransferLogRecord += clsDate::GetSystemDateTimeString() + Seperator;
		TransferLogRecord += AccountNumber() + Seperator;
		TransferLogRecord += DestinationClient.AccountNumber() + Seperator;
		TransferLogRecord += to_string(Amount) + Seperator;
		TransferLogRecord += to_string(AccountBalance) + Seperator;
		TransferLogRecord += to_string(DestinationClient.AccountBalance) + Seperator;
		TransferLogRecord += UserName;
		return TransferLogRecord;
	}
	void _RegisterTransferLog(float Amount, clsBankClient DestinationClient,string UserName)
	{
		_AddDataLineToFile("TransferLog.text", _PrepareTransferLogInRecord(Amount, DestinationClient, UserName));
	}

	struct stTransferLogRecord;
	static stTransferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
	{
		stTransferLogRecord TransferLogRecord;
		vector<string>vTransferLogDataLine = clsString::Split(Line, Seperator);;
		TransferLogRecord.DateTime = vTransferLogDataLine[0];
		TransferLogRecord.SourceAccountNumber = vTransferLogDataLine[1];
		TransferLogRecord.DestinationAccountNumber = vTransferLogDataLine[2];
		TransferLogRecord.Amount = stoi(vTransferLogDataLine[3]);
		TransferLogRecord.srcBalanceAfter = stoi(vTransferLogDataLine[4]);
		TransferLogRecord.destBalanceAfter = stoi(vTransferLogDataLine[5]);
		TransferLogRecord.UserName = vTransferLogDataLine[6];
		return 	TransferLogRecord;
	}



public :
	struct stTransferLogRecord
	{
		string DateTime;
		string SourceAccountNumber;
		string DestinationAccountNumber;
		float  Amount;
		double srcBalanceAfter;
		double destBalanceAfter;
		string UserName;
	};
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone
		, string AccountNumber, string PinCode, float AccountBalance):
		clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode= PinCode;
		_AccountBalance= AccountBalance;
	}
	//---------------------------------------------------------------------------------------------------

	//Property (Read Only Property) Get
	string AccountNumber()
	{
		return _AccountNumber;
	}
	//Property Set And Get
	void SetPinCode(string PinCode)
	{
		_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return _PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode))string PinCode;
	//Property Set And Get
	void SetAccountBalance(float AccountBalance)
	{
		_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return _AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance))float AccountBalance;
	//Property Set And Get
	void SetIsLogin(bool IsLogin)
	{
		_IsLogin = IsLogin;
	}
	bool GetIsLogin()
	{
		return _IsLogin;
	}
	__declspec(property(get = GetIsLogin, put = SetIsLogin))bool IsLogin;
	//---------------------------------------------------------------------------------------------------
	bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}
	string FullName()
	{
		return FirstName + " " + LastName;
	}
	/*
	* No UI Related code inside object.
	void Print()
	{
		cout << "\nClient Card :";
		cout << "\n---------------------------------------\n";
		cout << "FirstName   :" << FirstName << endl;
		cout << "LastName    :" << LastName << endl;
		cout << "Full Name   :" << FullName() << endl;
		cout << "Email       :" << Email << endl;
		cout << "Phone       :" << Phone << endl;
		cout << "Acc. Number :" << _AccountNumber << endl;
		cout << "Password    :" << _PinCode << endl;
		cout << "Balance     :" << _AccountBalance << endl;
		cout << "---------------------------------------\n";
	}*/

	static clsBankClient Find(string AccountNumber)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return  _GetEmptyClientObject();
	}
	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line = "";
			while (getline(MyFile, Line))
			{
				clsBankClient Client = _ConvertLineToClientObject(Line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
			}
			MyFile.close();
		}

		return  _GetEmptyClientObject();
	}
	enum enSaveResult 
	{
		svFaildEmptyObject = 0,
		svSucceede = 1, 
		svFaildAccountNumberExists = 2
	};
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case enMode::EmptyMode:
			return enSaveResult::svFaildEmptyObject;
		case enMode::UpdateMode:
			_Update();
			return enSaveResult::svSucceede;
		case enMode::AddNewMode:
			//This will add new record to file or database
			if (IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFaildAccountNumberExists;
			}
			else
			{
				_AddNew();
				//we need to set the mode to update after add new
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceede;
			}
			break;
	    }
	}
	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}
	bool Delete()
	{
		vector<clsBankClient>_vClients = _LoadClientsDataFromFile("Clients.txt");
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkForDelete = true;
				break;
			}
		}
		_SaveClientsDataToFile(_vClients, "Clients.txt");
		*this = _GetEmptyClientObject();
		return true;
	}
	static vector<clsBankClient>GetClientsList()
	{
		return  _LoadClientsDataFromFile("Clients.txt");
	}
	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (!(Client1.IsEmpty()));
	}

	static double GetTotalBalances()
	{
		vector<clsBankClient>vClients = clsBankClient::GetClientsList();
		double TotalBalances = 0;
		for (clsBankClient& Client : vClients)
		{
			TotalBalances += Client.AccountBalance;
		}
		return TotalBalances;
	}
	void Deposit(double Amount)
	{
		_AccountBalance += Amount;
		Save();
	}
	bool Withdraw(double Amount)
	{
		if (Amount > _AccountBalance)
		{
			return false;
		}
		else
		{
			_AccountBalance -= Amount;
			Save();
			return true;
		}	
	}
	bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
	{
		if (Amount > AccountBalance)
		{
			return false;
		}
		Withdraw(Amount);
		DestinationClient.Deposit(Amount);
		_RegisterTransferLog(Amount,DestinationClient,UserName);
		return true;
	}

	static vector<stTransferLogRecord>GetTransferLogList()
	{
		vector<stTransferLogRecord>vstTransferLogRecord;
		fstream MyFile;
		MyFile.open("TransferLog.text", ios::in);//read Mode
		if (MyFile.is_open())
		{
			string Line = "";
			stTransferLogRecord TransferLogRecord;
			while (getline(MyFile, Line))
			{
				TransferLogRecord = _ConvertTransferLogLineToRecord(Line);
				vstTransferLogRecord.push_back(TransferLogRecord);
			}
			MyFile.close();
		}
		return vstTransferLogRecord;
	}
	
};


