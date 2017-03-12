#include <iostream>
#include "Editplus4Keygen.h"
#include "W2CHAR.h"
using namespace std;

int main()
{
	Editplus4Keygen Key;
	setlocale(LC_ALL, "");
	wstring usr;
	W2CHAR c;
	cout << "Username:";
	while (getline(wcin, usr, L'\n')) { 
		wstring key = Key.getKey(usr);
		wcout <<"Regcode:"<<key<< endl;
		string s = c.WstringToString(usr);
		if (usr != c.StringToWstring(s))
			cout << "The Regcode may be wrong!" << endl;
		cout << endl<< "Username:";
	}
	return 0;
}