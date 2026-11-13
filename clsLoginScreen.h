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
#include "clsInputValidate.h"
#include "clsScreen.h"

#include "clsBankClient.h"
#include "clsShowATMMainMenueScreen.h"
#include "GlobalClient.h"
using namespace std;




class clsLoginScreen :protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFaild = false;
        string AccountNumber, PinCode;
        short FaildLoginCoun = 0;
        do
        {
            system("cls");
            _DrawScreenHeader("\t\tLogin Screen");
            if (LoginFaild)
            {
                FaildLoginCoun++;
                cout << "\nInvalid AccountNumber/PinCode!\n";
                cout << "You have [" + to_string(3 - FaildLoginCoun) + "] Trial(s) to login.\n";
            }
            if (FaildLoginCoun == 3)
            {
                cout << "\nYour are Locked after 3 faild trails.\n";
                return false;
            }
            cout << "\nEnter Account Number? => ";
            AccountNumber = clsInputValidate::ReadString();
            cout << "\nEnter PinCode? => ";
            PinCode = clsInputValidate::ReadString();
            CurrentClient = clsBankClient::Find(AccountNumber, PinCode);
            LoginFaild = CurrentClient.IsEmpty();
        } while (LoginFaild);  
        CurrentClient.IsLogin = true;
        clsShowATMMainMenueScreen::ShowATMMainMenueScreen();
        return true;
    }

public:

    static bool ShowLoginScreen()
    {
        //system("cls");
        //_DrawScreenHeader("\t\tLogin Screen"); 
       return  _Login();
    }
};

