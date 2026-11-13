#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>

#include "clsInputValidate.h"
#include "clsUtil.h"
#include "clsScreen.h"

//#include "clsBankClient.h"
#include "GlobalClient.h"
using namespace std;




class clsShowDepositScreen : protected clsScreen
{


private:
	static double _ReadDepositAmount()
	{
		double Amount;
		cout << "\nEnter a positive Deposit Amount ? => ";
		Amount = clsInputValidate::ReadPositivedoubleNumber();		
		return Amount;
	}
	static void _PrintBalanceOfClient(short NumberOfTabs = 0)
	{
		cout << "\n";
		cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
		cout << clsUtil::Tabs(NumberOfTabs) << " Your Balance Is : " << CurrentClient.AccountBalance << endl;
		cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
	}
public:

	static void ShowDepositScreen()
	{
		_DrawScreenHeader("\t   Deposit Screen");
		double DepositAmount = _ReadDepositAmount();
		char Answer = 'n';
		cout << "\nAre you sure you want to perform this transaction? [Y/N] => ";
		cin >> Answer;
		if (Answer == 'y' || Answer == 'Y')
		{
			CurrentClient.Deposit(DepositAmount);
			cout << "\nDone Successfully :-)\n";
			cout << "\nNew Balance : ";
			_PrintBalanceOfClient();
		}
		else
		{
			cout << "\nOperation was cancelled\n";
		}
	}


};

