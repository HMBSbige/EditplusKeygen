#include "CRC16.h"
CRC16::CRC16() {
	memset(table, 0, sizeof(table));
	BuildCRCTable();
}
void CRC16::BuildCRCTable()
{
	int i, j, ax;
	for (i = 0; i < 0x100; ++i)
	{
		ax = 0xc0c1;
		for (j = 1; j < 0x100; j <<= 1)
		{
			if (i & j)
				table[i] ^= ax;
			ax <<= 1;
			ax ^= 0x4003;
		}
	}
}
uint16_t CRC16::GetCRC16(string ascii)
{
	uint16_t res = 0;
	uint8_t tmp;
	for (size_t i = 0; i < ascii.size(); ++i)
	{
		tmp = res & 0xFF;
		res >>= 8;
		tmp ^= ascii[i];
		res ^= table[tmp];
	}
	return res;
}