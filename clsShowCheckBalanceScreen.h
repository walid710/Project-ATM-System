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



class clsShowCheckBalanceScreen : protected clsScreen
{

private:

    static void _PrintBalanceOfClient(short NumberOfTabs=0)
    {
        cout << "\n\n\n";
        cout << clsUtil::Tabs(NumberOfTabs) << "Balance :\n";
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n";
        cout << clsUtil::Tabs(NumberOfTabs) << " Your Balance Is : " << CurrentClient.AccountBalance << endl;
        cout << clsUtil::Tabs(NumberOfTabs) << "---------------------------------------\n\n\n\n";
    }
public:

    static void ShowCheckBalanceScreen()
    {
        _DrawScreenHeader("\t    Check Balance Screen");
        _PrintBalanceOfClient(3);
    }
       

};

