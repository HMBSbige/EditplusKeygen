#include <iostream>
#include "Editplus4Keygen.h"
#include "W2CHAR.h"
using namespace std;

auto main() -> int
{
	setlocale(LC_ALL, "");
	ios::sync_with_stdio(false);
	wstring usr;
	W2CHAR c;
	try
	{
		cout << "Username:";
		while (getline(wcin, usr, L'\n'))
		{
			cout << endl;

			auto key5 = Editplus4Keygen::get5Key(usr);
			wcout << "Editplus 5.x Regcode: " << endl << key5 << endl;
			wcout << "Check Username:" << usr << endl;
			wcout << "Check Key:";
			cout << (Editplus4Keygen::Check5Key(usr, key5) ? "True" : "False") << endl << endl;

			auto key4 = Editplus4Keygen::get4Key(usr);
			wcout << "Editplus 4.x Regcode: " << endl << key4 << endl;
			wcout << "Check Username:" << usr << endl;
			wcout << "Check Key:";
			cout << (Editplus4Keygen::Check4Key(usr, key4) ? "True" : "False") << endl << endl;

			auto key3 = Editplus4Keygen::get3Key(usr);
			wcout << "Editplus 3.x Regcode: " << endl << key3 << endl;
			wcout << "Check Username:" << usr << endl;
			wcout << "Check Key:";
			cout << (Editplus4Keygen::Check3Key(usr, key3) ? "True" : "False") << endl << endl;

			auto s = c.WstringToString(usr);
			if (usr != c.StringToWstring(s))
			{
				cout << "The Regcode may be wrong!" << endl;
			}

			cout << endl << "Username:";
		}
	}
	catch (...)
	{

	}


	return 0;
}
