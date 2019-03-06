#pragma once
#include <string>
#include "Timer.h"

class Editplus4Keygen {
private:
	static string GetAsciiOfUnicode(wstring &words);
	static wstring INT2HexWString(int, int);
	static wstring reg_code_init();
	static char Encode5(char ch);
	static char Decode5(char ch);
public:
	Editplus4Keygen();
	static wstring get5Key(wstring usr);
	static wstring get4Key(wstring usr);
	static wstring get3Key(wstring usr);
	static int CheckKey(const wstring&, const wstring&);
	static bool Check5Key(wstring, wstring);
	static bool Check4Key(wstring, wstring);
	static bool Check3Key(wstring, wstring);
};