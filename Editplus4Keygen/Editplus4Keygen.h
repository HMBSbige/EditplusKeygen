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
	wstring getKey(wstring usr);
	bool CheckKey(wstring, wstring);
};