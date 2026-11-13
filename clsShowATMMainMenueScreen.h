#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <vector>
#include <cctype>
#include <fstream>
#include <ctime>

#include "clsScreen.h"
#include "clsString.h"
#include "clsInputValidate.h"

#include "GlobalClient.h"
#include "clsBankClient.h"
#include "clsShowQuickWithdrawScreen.h"
#include "clsShowNormalWithdrawScreen.h"
#include "clsShowCheckBalanceScreen.h"
#include "clsShowDepositScreen.h"

using namespace std;

class clsShowATMMainMenueScreen : protected clsScreen
{
private:

	enum enATMMainMenueOption
	{
		eQuickWithdraw = 1,
		eNormalWithdraw = 2,
		eDeposit = 3,
		eCheckBalance =4,
		eExit =5,
	};
	static short _ReadATMMainMenueOption()
	{
		cout << setw(38) << left << "" << "Choose what do you want to do? [1:5] => ";
		short Choice = clsInputValidate::ReadIntNumberBetween(1, 5, "Enter Number between 1 to 5? ");
		return Choice;
	}
	static void _GoBackToATMMainMenueScreen()
	{
		cout << "\nPress any key to go back to ATM Main Menue Screen...";
		system("pause>0");
		ShowATMMainMenueScreen();
	}
	static void _ShowQuickWithdrawScreen()
	{
		//cout << "\nQuick Withdraw Screen Will be here...\n";
		clsShowQuickWithdrawScreen::ShowQuickWithdrawScreen();
	}
	static void _ShowNormalWithdrawScreen()
	{
		//cout << "\nNormal Withdraw  Screen Will be here...\n";
		clsShowNormalWithdrawScreen::ShowNormalWithdrawScreen();
	}
	static void _ShowDepositScreen()
	{
		//cout << "\nDeposit Screen Will be here...\n";
		clsShowDepositScreen::ShowDepositScreen();
	}
	static void _ShowCheckBalanceScreen()
	{
		//cout << "\nCheck Balance Screen Will be here...\n";
		clsShowCheckBalanceScreen::ShowCheckBalanceScreen();
	}
	
	static void _PerformATMMainMenueOption(enATMMainMenueOption ATMMainMenueOption)
	{
		switch (ATMMainMenueOption)
		{

		case enATMMainMenueOption::eQuickWithdraw:
			system("cls");
			_ShowQuickWithdrawScreen();
			_GoBackToATMMainMenueScreen();
			break;
		case enATMMainMenueOption::eNormalWithdraw:
			system("cls");
			_ShowNormalWithdrawScreen();
			_GoBackToATMMainMenueScreen();
			break;
		case enATMMainMenueOption::eDeposit:
			system("cls");
			_ShowDepositScreen();
			_GoBackToATMMainMenueScreen();
			break;
		case enATMMainMenueOption::eCheckBalance:
			system("cls");
			_ShowCheckBalanceScreen();
			_GoBackToATMMainMenueScreen();
			break;
		case enATMMainMenueOption::eExit:
			//Do nothing here the main screen will handle it :-);
			CurrentClient = clsBankClient::Find("", "");
			break;
		}
	}

public:

	static void ShowATMMainMenueScreen()
	{
		system("cls");
		_DrawScreenHeader("\t   ATM Main Menue Screen");
		cout << setw(38) << left << "" << "==================================================\n";
		cout << setw(38) << left << "" << "\t\t\tATM Main Menue \n";
		cout << setw(38) << left << "" << "==================================================\n";
		cout << setw(38) << left << "" << "\t[1] Quick Withdraw.\n";
		cout << setw(38) << left << "" << "\t[2] Normal Withdraw.\n";
		cout << setw(38) << left << "" << "\t[3] Deposit.\n";
		cout << setw(38) << left << "" << "\t[4] Check Balances.\n";
		cout << setw(38) << left << "" << "\t[5] Logout.\n";
		cout << setw(38) << left << "" << "==================================================\n";
		_PerformATMMainMenueOption((enATMMainMenueOption)_ReadATMMainMenueOption());
	}
};

