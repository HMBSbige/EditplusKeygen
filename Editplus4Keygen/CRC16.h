#pragma once
#include <iostream>
#include <string>
using namespace std;
class CRC16 {
private:
	uint16_t table[256];
	void BuildCRCTable();
public:
	CRC16();
	uint16_t GetCRC16(string ascii);
};
