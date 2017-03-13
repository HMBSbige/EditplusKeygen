#include <iostream>
#include "Editplus4Keygen.h"
#include "W2CHAR.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	ios::sync_with_stdio(false);
	Editplus4Keygen Key;
	wstring usr;
	W2CHAR c;
	cout << "Username:";
	while (getline(wcin, usr, L'\n')) { 

		wcout <<"Editplus 4.x Regcode: " << endl << Key.get4Key(usr) << endl << endl;
		wcout << "Editplus 3.x Regcode: " << endl << Key.get3Key(usr) << endl;
	
		string s = c.WstringToString(usr);
		if (usr != c.StringToWstring(s))
			cout << "The Regcode may be wrong!" << endl;
		cout << endl<< "Username:";
	}
	return 0;
}