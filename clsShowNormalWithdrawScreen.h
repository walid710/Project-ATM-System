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

#include "clsBankClient.h"
#include "GlobalClient.h"
using namespace std;



class clsShowNormalWithdrawScreen : protected clsScreen
{


private:
    static void _PrintBalanceOfClient(short NumberOfTabs = 0)
    {
        cout << "\n";
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
        cout << clsUtil::Tabs(NumberOfTabs) << " Your Balance Is : " << CurrentClient.AccountBalance << endl;
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
    }

	static int _ReadWithDrawAmount()
	{
		int Amount;
		cout << "\nEnter an amount multiple of 5's ? => ";
		Amount = clsInputValidate::ReadIntNumber();
		while (Amount % 5 != 0)
		{
			cout << "\nEnter an amount multiple of 5's ? => ";
			Amount = clsInputValidate::ReadIntNumber();
		}
		return Amount;
	}
    static void _GoBackToShowNormalWithdrawScreen()
    {
        //cout << "\nPress any key to Continue..";
        //system("pause>0");
        system("cls");
        ShowNormalWithdrawScreen();
    }
public:
	static void ShowNormalWithdrawScreen()
	{
		_DrawScreenHeader("\t   Normal Withdraw Screen");
        int WithDrawAmount = _ReadWithDrawAmount();
        char Answer = 'n';
        cout << "\nAre you sure you want to perform this transaction? [Y/N] => ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (CurrentClient.Withdraw(WithDrawAmount))
            {
                cout << "\nDone Successfully :-)\n";
                cout << "\nNew Balance : ";
                _PrintBalanceOfClient();
            }
            else
            {
                cout << "\nCan not withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to Withdraw is : [" << WithDrawAmount << "].";
                cout << "\nYour Balance is       : [" << CurrentClient.AccountBalance << "].\n";
                if (CurrentClient.AccountBalance < 5)
                {
                    cout << "\nSorry Your Balance is Not Enough to Withdraw Please try when your balane is enough !! \n";
                    return;
                }
                cout << "\nThe Amount exceeds your balance, make another choice.\n";
                cout << "\nDo you want to Withdraw Again ? [Y/N] => ";
                cin >> Answer;
                if (Answer == 'y' || Answer == 'Y')
                {
                    _GoBackToShowNormalWithdrawScreen();
                }
                else
                    return;
            }
        }
        else
        {
            cout << "\nOperation was cancelled\n";
        }
    }
};

