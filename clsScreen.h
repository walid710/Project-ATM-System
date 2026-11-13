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
#include "clsDate.h"

#include "GlobalClient.h"

using namespace std;




class clsScreen
{

protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << clsUtil::Tabs(3) <<"_____________________________________________";
		cout << "\n\n" << clsUtil::Tabs(3) << Title;
		if (SubTitle != "")
		{
			cout << "\n" << clsUtil::Tabs(3) << SubTitle;
		}
		cout << "\n" << clsUtil::Tabs(3) <<"_____________________________________________\n\n";
		cout << clsUtil::Tabs(3) << "Date: " << clsDate::DateToString(clsDate());
		if (CurrentClient.IsLogin)
		{
			cout << "\n" << clsUtil::Tabs(3) << "User Name : " << CurrentClient.FullName();
		}
		cout <<"\n\n";
	}
	
public:

};

