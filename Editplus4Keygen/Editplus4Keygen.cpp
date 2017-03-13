#include "Editplus4Keygen.h"
Editplus4Keygen::Editplus4Keygen() {}
string Editplus4Keygen::GetAsciiOfUnicode(wstring &words)
{
	stringstream ss;
	for (size_t i = 0; i < words.size(); ++i)
	{
		ss.fill('0');
		ss.width(4);
		ss << right << setiosflags(ios::uppercase) << hex << words[i];
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
wstring Editplus4Keygen::regcodeinit() {
	wstring key;
	RandomNum r;
	wstring a;
	a.resize(36);
	for (int i = 0; i < 10; ++i)
		a[i] = L'0' + i;
	for (int j = 10, i = 0; i < 26; ++i, ++j)
		a[j] = L'A' + i;
	for (int i = 0; i < 29; ++i) {
		if (i != 5 && i != 11 && i != 17 && i != 23)
			key.push_back(a[r.getNum(0, 35)]);
		else
			key.push_back(L'-');
	}
	return key;
}
wstring Editplus4Keygen::get4Key(wstring usr) {
	CRC16 c;
	wstring  unicode, regcode = regcodeinit();
	string ascii;
	RandomNum r;
	int wtf = r.getNum(0, 1);

	int sum = 1;
	for (size_t i = 0; i < usr.size(); ++i)
	{
		sum += usr[i];
	}
	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;

	unicode = INT2HexWString(res);
	regcode[4] = unicode[0];

	ascii = GetAsciiOfUnicode(usr);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	regcode[2] = unicode[0];
	regcode[3] = unicode[1];

	res = ((sum + 41) / 6 * 7) % 16;
	unicode = INT2HexWString(res);
	regcode[6] = unicode[0];

	res = ((3 * sum + 19) / 9) % 16;
	unicode = INT2HexWString(res);
	regcode[7] = unicode[0];

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	regcode[8] = unicode[0];

	if(wtf)
		res = ((3 * sum + 43) / 8) % 16;
	else
		res = ((3 * sum + 39) / 8) % 16;
	unicode = INT2HexWString(res);
	regcode[9] = unicode[0];

	res = ((sum + 10) / 3 * 8) % 16;
	unicode = INT2HexWString(res);
	regcode[10] = unicode[0];

	ascii = GetAsciiOfUnicode(regcode.substr(2));
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	regcode[0] = unicode[0];
	regcode[1] = unicode[1];
	//transform(regcode.begin(), regcode.end(), regcode.begin(), ::toupper);
	return regcode;
}

wstring Editplus4Keygen::get3Key(wstring usr)
{
	CRC16 c;
	wstring  unicode,regcode = regcodeinit();
	int temp;
	RandomNum r;
	int wtf = r.getNum(0, 1);

	int sum = 1;
	for (size_t i = 0; i < usr.size(); ++i)
	{
		sum += usr[i];
	}

	temp = (((sum + 23) / 6) + 3) * 7 % 16;
	unicode = INT2HexWString(temp);
	regcode[6] = unicode[0];

	if (wtf)
		temp = ((3 * sum + 43) / 8) % 16;
	else
		temp = ((3 * sum + 39) / 8) % 16;
	unicode = INT2HexWString(temp);
	regcode[9] = unicode[0];

	temp = ((3 * sum + 19) / 9) % 16;
	unicode = INT2HexWString(temp);
	regcode[7] = unicode[0];

	temp = ((sum + 10) / 3) * 8 % 16;
	unicode = INT2HexWString(temp);
	regcode[10] = unicode[0];

	temp = (((9 * sum + 10) / 3) + 36) % 16;
	unicode = INT2HexWString(temp);
	regcode[4] = unicode[0];

	temp = ((5 * sum + 11) / 5) % 16;
	unicode = INT2HexWString(temp);
	regcode[8] = unicode[0];

	unicode = INT2HexWString(c.GetCRC16(usr));
	regcode[2] = unicode[0];
	regcode[3] = unicode[1];

	unicode = INT2HexWString(c.GetCRC16(regcode.substr(2)));
	regcode[0] = unicode[0];
	regcode[1] = unicode[1];

	return regcode;
}
int Editplus4Keygen::CheckKey(wstring usr, wstring key)
{
	if (Check4Key(usr, key))
		return 4;
	if (Check3Key(usr, key))
		return 3;
	return 0;
}
bool Editplus4Keygen::Check4Key(wstring usr, wstring key)
{
	CRC16 c;
	wstring unicode;
	string ascii;

	int sum = 1;
	for (size_t i = 0; i < usr.size(); ++i)
	{
		sum += usr[i];
	}

	ascii = GetAsciiOfUnicode(key.substr(2));
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	if(key[0] != unicode[0] || key[1] != unicode[1])
		return false;

	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;
	unicode = INT2HexWString(res);
	if(key[4] != unicode[0])
		return false;

	ascii = GetAsciiOfUnicode(usr);
	unicode = INT2HexWString(c.GetCRC16(ascii), 4);
	if (key[2] != unicode[0] || key[3] != unicode[1])
		return false;

	res = ((sum + 41) / 6 * 7) % 16;
	unicode = INT2HexWString(res);
	if(key[6] != unicode[0])
		return false;

	res = ((3 * sum + 19) / 9) % 16;
	unicode = INT2HexWString(res);
	if (key[7] != unicode[0])
		return false;

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	if (key[8] != unicode[0])
		return false;

	res = ((3 * sum + 43) / 8) % 16;
	unicode = INT2HexWString(res);
	if (key[9] != unicode[0]) {
		res = ((3 * sum + 39) / 8) % 16;
		unicode = INT2HexWString(res);
		if (key[9] != unicode[0])
			return false;
	}

	res = ((sum + 10) / 3 * 8) % 16;
	unicode = INT2HexWString(res);
	if (key[10] != unicode[0])
		return false;

	return true;
}

bool Editplus4Keygen::Check3Key(wstring usr, wstring key)
{
	CRC16 c;
	wstring unicode;

	int sum = 1;
	for (size_t i = 0; i < usr.size(); ++i)
	{
		sum += usr[i];
	}

	unicode = INT2HexWString(c.GetCRC16(key.substr(2)));
	if (key[0] != unicode[0] || key[1] != unicode[1])
		return false;

	int res = ((sum * 9 + 10) / 3 + 0x24) % 16;
	unicode = INT2HexWString(res);
	if (key[4] != unicode[0])
		return false;

	unicode = INT2HexWString(c.GetCRC16(usr));
	if (key[2] != unicode[0] || key[3] != unicode[1])
		return false;

	res = ((sum + 41) / 6 * 7) % 16;
	unicode = INT2HexWString(res);
	if (key[6] != unicode[0])
		return false;

	res = ((3 * sum + 19) / 9) % 16;
	unicode = INT2HexWString(res);
	if (key[7] != unicode[0])
		return false;

	res = (sum + 2) % 16;
	unicode = INT2HexWString(res);
	if (key[8] != unicode[0])
		return false;

	res = ((3 * sum + 43) / 8) % 16;
	unicode = INT2HexWString(res);
	if (key[9] != unicode[0]) {
		res = ((3 * sum + 39) / 8) % 16;
		unicode = INT2HexWString(res);
		if (key[9] != unicode[0])
			return false;
	}

	res = ((sum + 10) / 3 * 8) % 16;
	unicode = INT2HexWString(res);
	if (key[10] != unicode[0])
		return false;

	return true;
}
