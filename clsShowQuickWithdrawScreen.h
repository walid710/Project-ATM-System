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
#include "clsUtil.h"

//#include "clsBankClient.h"
#include "GlobalClient.h"

class clsShowQuickWithdrawScreen : protected clsScreen
{

private:
    static void _GoBackToShowQuickWithdrawScreen()
    {
        cout << "\nPress any key to Continue..";
        system("pause>0");
        system("cls");
        ShowQuickWithdrawScreen();
    }
    static void _PrintBalanceOfClient(short NumberOfTabs=0)
    {
        cout << "\n";
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
        cout << clsUtil::Tabs(NumberOfTabs) << " Your Balance Is : " << CurrentClient.AccountBalance << endl;
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
    }
    
    static short _ReadQuichWithdrawOption()
    {
        short Choice;
        cout << "\n" << setw(38) << left << "" << "Choose What to do from [1] to [9] => ";
        Choice = clsInputValidate::ReadShortNumberBetween(1,9, "Enter Number between [1]to [9]? => ");
        return Choice;
    }
    static short _GetQuichWithdrawAmount(short QuichWithdrawOption)
    {
        switch (QuichWithdrawOption)
        {
        case 1:
            return 20;
        case 2:
            return 50;
        case 3:
            return 100;
        case 4:
            return 200;
        case 5:
            return 400;
        case 6:
            return 600;
        case 7:
            return 800;
        case 8:
            return 1000;
        default:
            return 0;
        }
    }
    static void _PerformQuichWithdrawOption(short QuichWithdrawOption)
    {
        if (QuichWithdrawOption == 9)//Exit
            return;
        short WithDrawBalance = _GetQuichWithdrawAmount(QuichWithdrawOption);
        char Answer = 'n';
        cout << "\nAre you sure you want to perform this transaction? [Y/N] => ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            if (CurrentClient.Withdraw(WithDrawBalance))
            {

                cout << "\nDone Successfully :-)\n";
                cout << "\nNew Balance : ";
                _PrintBalanceOfClient();
            }
            else
            {
                cout << "\nCan not withdraw, Insuffecient Balance!\n";
                cout << "\nAmount to Withdraw is : [" << WithDrawBalance << "].";
                cout << "\nYour Balance is       : [" << CurrentClient.AccountBalance << "].\n";
                if (CurrentClient.AccountBalance < 20)
                {
                    cout << "\nSorry Your Balance is Not Enough to Withdraw Please try when your balane is enough !! \n";
                    return;
                }
                cout << "\nThe Amount exceeds your balance, make another choice.\n";
                _GoBackToShowQuickWithdrawScreen();
            }
        }
        else
        {
            cout << "\nOperation was cancelled\n";
        }
    }
public:

    static void ShowQuickWithdrawScreen()
    {
        system("cls");
        _DrawScreenHeader("\t   Quich Withdraw Screen");
        cout << setw(38) << left  << ""<< "==================================================\n";
        cout << setw(38) << left  << ""<< "\t\t   Quick Withdraw Menue \n";
        cout << setw(38) << left  << ""<< "==================================================\n";
        cout << setw(38) << left  << ""<< "\t   [1] 20           [2] 50\n";
        cout << setw(38) << left  << ""<< "\t   [3] 100          [4] 200\n";
        cout << setw(38) << left  << ""<< "\t   [5] 400          [6] 600\n";
        cout << setw(38) << left  << ""<< "\t   [7] 800          [8] 1000\n";
        cout << setw(38) << left  << ""<< "\t   [9] Exit.\n";
        cout << setw(38) << left  << ""<< "==================================================\n";
        _PrintBalanceOfClient(3);
        _PerformQuichWithdrawOption(_ReadQuichWithdrawOption());
    }
};

