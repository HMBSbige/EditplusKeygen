#include "Editplus4Keygen.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "CRC16.h"
#include <cctype>

Editplus4Keygen::Editplus4Keygen() = default;

const char arr[36] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
	0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A };

const char table5[26] =
{
	8, 9, 10, 11,		//	A,B,C,D,
	12, 13, 14, 15, 0,	//	E,F,G,H,I
	16, 17, 18, 19,		//	J,K,L,M,
	20, 0, 21, 22, 23,	//	N,O,P,Q,R,
	24, 25, 26, 27,		//	S,T,U,V,
	28, 29, 30, 31		//	W,X,Y,Z	
};

string Editplus4Keygen::GetAsciiOfUnicode(wstring &words)
{
	stringstream ss;
	for (auto word : words)
	{
		ss.fill('0');
		ss.width(4);
		ss << right << setiosflags(ios::uppercase) << hex << word;
	}
	return ss.str();
}

wstring Editplus4Keygen::INT2HexWString(int num, int n = 0) {
	wstringstream wss;
	wss.fill('0');
	wss.width(n);
	wss << right << setiosflags(ios::uppercase) << hex << num;
	return wss.str();
}

wstring Editplus4Keygen::reg_code_init() {
	wstring key;
	RandomNum r;
	for (auto i = 0; i < 29; ++i) {
		if (i != 5 && i != 11 && i != 17 && i != 23)
			key.push_back(arr[r.getNum(0, 35)]);
		else
			key.push_back(L'-');
	}
	return key;
}

char Editplus4Keygen::Decode5(char ch)
{
	for (auto i : arr)
	{
		char tmp;
		auto ret = Encode5(i);
		ret >>= 1;
		if (ret >= 10)
			tmp = ret + 55;
		else
			tmp = ret + 48;
		if (tmp == ch)
		{
			return i;
		}
	}
	return 0;
}

char Editplus4Keygen::Encode5(char ch)
{
	if (ch == '0' || ch == '1' || ch == 'I' || ch == 'O')
	{
		return 0;
	}

	if (isdigit(ch))
	{
		return ch - 50;
	}

	if (isupper(ch))
	{
		return table5[ch - 'A'];
	}

	return 0;
}

wstring Editplus4Keygen::get5Key(wstring usr)
{
	CRC16 c;
	wstring reg_code = reg_code_init();
	wstring dreg_code;
	dreg_code.resize(29);

	auto sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}
	const auto res = ((sum * 9 + 10) / 3 + 0x24) % 16;

	wstring unicode = INT2HexWString(res);
	reg_code[4] = Decode5(unicode[0]);

	string ascii = GetAsciiOfUnicode(usr);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	reg_code[2] = Decode5(unicode[0]);
	reg_code[3] = Decode5(unicode[1]);

	for (int i = 0; i < 29; ++i)
	{
		if ((i + 1) % 6 != 0)
		{
			char ret = Encode5(reg_code[i]);
			ret >>= 1;
			if (ret >= 10)
				dreg_code[i] = ret + 55;
			else
				dreg_code[i] = ret + 48;
		}
		else
			dreg_code[i] = '-';
	}
	auto t_str = dreg_code.substr(2);
	ascii = GetAsciiOfUnicode(t_str);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	reg_code[0] = Decode5(unicode[0]);
	reg_code[1] = Decode5(unicode[1]);
	return reg_code;
}

wstring Editplus4Keygen::get4Key(wstring usr)
{
	CRC16 c;
	wstring  unicode, reg_code = reg_code_init();
	string ascii;
	RandomNum r;
	int wtf = r.getNum(0, 1);

	int sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}
	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;

	unicode = INT2HexWString(res);
	reg_code[4] = unicode[0];

	ascii = GetAsciiOfUnicode(usr);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	reg_code[2] = unicode[0];
	reg_code[3] = unicode[1];

	res = (sum + 41) / 6 * 7 % 16;
	unicode = INT2HexWString(res);
	reg_code[6] = unicode[0];

	res = (3 * sum + 19) / 9 % 16;
	unicode = INT2HexWString(res);
	reg_code[7] = unicode[0];

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	reg_code[8] = unicode[0];

	res = (3 * sum + (wtf ? 43 : 39)) / 8 % 16;
	unicode = INT2HexWString(res);
	reg_code[9] = unicode[0];

	res = (sum + 10) / 3 * 8 % 16;
	unicode = INT2HexWString(res);
	reg_code[10] = unicode[0];

	auto t_str = reg_code.substr(2);
	ascii = GetAsciiOfUnicode(t_str);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	reg_code[0] = unicode[0];
	reg_code[1] = unicode[1];
	return reg_code;
}

wstring Editplus4Keygen::get3Key(wstring usr)
{
	CRC16 c;
	wstring reg_code = reg_code_init();
	RandomNum r;
	const auto wtf = r.getNum(0, 1);

	int sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}

	int temp = ((sum + 23) / 6 + 3) * 7 % 16;
	wstring unicode = INT2HexWString(temp);
	reg_code[6] = unicode[0];

	temp = (3 * sum + (wtf ? 43 : 39)) / 8 % 16;
	unicode = INT2HexWString(temp);
	reg_code[9] = unicode[0];

	temp = (3 * sum + 19) / 9 % 16;
	unicode = INT2HexWString(temp);
	reg_code[7] = unicode[0];

	temp = (sum + 10) / 3 * 8 % 16;
	unicode = INT2HexWString(temp);
	reg_code[10] = unicode[0];

	temp = ((9 * sum + 10) / 3 + 36) % 16;
	unicode = INT2HexWString(temp);
	reg_code[4] = unicode[0];

	temp = (5 * sum + 11) / 5 % 16;
	unicode = INT2HexWString(temp);
	reg_code[8] = unicode[0];

	unicode = INT2HexWString(c.GetCRC16(usr));
	reg_code[2] = unicode[0];
	reg_code[3] = unicode[1];

	unicode = INT2HexWString(c.GetCRC16(reg_code.substr(2)));
	reg_code[0] = unicode[0];
	reg_code[1] = unicode[1];

	return reg_code;
}

int Editplus4Keygen::CheckKey(const wstring& usr, const wstring& key)
{
	if (Check5Key(usr, key))
		return 5;
	if (Check4Key(usr, key))
		return 4;
	if (Check3Key(usr, key))
		return 3;
	return 0;
}

bool Editplus4Keygen::Check5Key(wstring usr, wstring key)
{
	CRC16 c;

	int sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}

	for (auto i = 0; i < 29; ++i)
	{
		if ((i + 1) % 6 != 0)//ignore '-'
		{
			auto ret = Encode5(key[i]);
			ret >>= 1;
			if (ret >= 10)
				key[i] = ret + 55;
			else
				key[i] = ret + 48;
		}
	}

	string ascii = GetAsciiOfUnicode(usr);
	wstring unicode = INT2HexWString(c.GetCRC16(ascii), 4);

	if (key[2] != unicode[0] || key[3] != unicode[1])
		return false;

	auto t_str = key.substr(2);
	ascii = GetAsciiOfUnicode(t_str);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	if (key[0] != unicode[0] || key[1] != unicode[1])
		return false;

	const auto res = ((sum * 9 + 10) / 3 + 0x24) % 16;
	unicode = INT2HexWString(res);
	return key[4] == unicode[0];
}

bool Editplus4Keygen::Check4Key(wstring usr, wstring key)
{
	CRC16 c;
	wstring unicode;
	string ascii;

	int sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}

	auto t_str = key.substr(2);
	ascii = GetAsciiOfUnicode(t_str);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	if (key[0] != unicode[0] || key[1] != unicode[1])
		return false;

	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;
	unicode = INT2HexWString(res);
	if (key[4] != unicode[0])
		return false;

	ascii = GetAsciiOfUnicode(usr);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	if (key[2] != unicode[0] || key[3] != unicode[1])
		return false;

	res = (sum + 41) / 6 * 7 % 16;
	unicode = INT2HexWString(res);
	if (key[6] != unicode[0])
		return false;

	res = (3 * sum + 19) / 9 % 16;
	unicode = INT2HexWString(res);
	if (key[7] != unicode[0])
		return false;

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	if (key[8] != unicode[0])
		return false;

	res = (3 * sum + 43) / 8 % 16;
	unicode = INT2HexWString(res);
	if (key[9] != unicode[0]) {
		res = (3 * sum + 39) / 8 % 16;
		unicode = INT2HexWString(res);
		if (key[9] != unicode[0])
			return false;
	}

	res = (sum + 10) / 3 * 8 % 16;
	unicode = INT2HexWString(res);
	return key[10] == unicode[0];
}

bool Editplus4Keygen::Check3Key(wstring usr, wstring key)
{
	CRC16 c;

	int sum = 1;
	for (auto i : usr)
	{
		sum += i;
	}

	wstring unicode = INT2HexWString(c.GetCRC16(key.substr(2)));
	if (key[0] != unicode[0] || key[1] != unicode[1])
		return false;

	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;
	unicode = INT2HexWString(res);
	if (key[4] != unicode[0])
		return false;

	unicode = INT2HexWString(c.GetCRC16(usr));
	if (key[2] != unicode[0] || key[3] != unicode[1])
		return false;

	res = (sum + 41) / 6 * 7 % 16;
	unicode = INT2HexWString(res);
	if (key[6] != unicode[0])
		return false;

	res = (3 * sum + 19) / 9 % 16;
	unicode = INT2HexWString(res);
	if (key[7] != unicode[0])
		return false;

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	if (key[8] != unicode[0])
		return false;

	res = (3 * sum + 43) / 8 % 16;
	unicode = INT2HexWString(res);
	if (key[9] != unicode[0]) {
		res = (3 * sum + 39) / 8 % 16;
		unicode = INT2HexWString(res);
		if (key[9] != unicode[0])
			return false;
	}

	res = (sum + 10) / 3 * 8 % 16;
	unicode = INT2HexWString(res);
	return key[10] == unicode[0];
}
