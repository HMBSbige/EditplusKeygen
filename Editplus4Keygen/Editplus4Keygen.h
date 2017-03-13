#pragma once
#include <algorithm>
#include <iomanip>
#include <string>
#include <sstream>
#include "Timer.h"
#include "CRC16.h"
class Editplus4Keygen {
private:
	string GetAsciiOfUnicode(wstring &words);
	wstring INT2HexWString(int, int);
	wstring regcodeinit();
public:
	Editplus4Keygen();
	wstring get4Key(wstring usr);
	wstring get3Key(wstring usr);
	int CheckKey(wstring, wstring);
	bool Check4Key(wstring, wstring);
	bool Check3Key(wstring, wstring);
};