/// 
/// EPI. Chapter 5. Bit Manipulation Problems
///
#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>

#include "Bitwise.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Bitwise ==" << endl << endl;

	cout << "- Bit Count -" << endl;
	{
		vector<long long> numbers =
		{
			0, 1, 2, 3, 5, 9, 0x7F, 0xFF, 0x7FFFFFFF, 0x0001000100010001, LLONG_MAX - 1, LLONG_MAX,
			-1, -2, -3, -8, -9, -0x0001000100010001, LLONG_MIN + 1, LLONG_MIN
		};
		cout << "-- Simple method --" << endl;
		for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
		{
			cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountSmp(*it) << (it != numbers.cend() - 1 ? ", " : "") << endl;
		}
		cout << "-- 'The lowest bit' method --" << endl;
		for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
		{
			cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountOpt(*it) << (it != numbers.cend() - 1 ? ", " : "") << endl;
		}
		cout << "-- Lookup table method --" << endl;
		vector<unsigned short> table;
		Bitwise::GenerateWordTable(table);
		for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
		{
			cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountTbl(*it, table) << (it != numbers.cend() - 1 ? ", " : "") << endl;
		}
	}
	cout << endl;

	cout << "- Bit Swap -" << endl;
	{
		bitset<16> number(string("1000000010010110"));
		vector<pair<unsigned short, unsigned short>> indices = { { 0, 0 }, { 0, 1 }, { 1, 2 }, { 2, 6 }, { 0, 7 }, { 7, 8 }, { 0, 15 }, { 14, 15 } };
		for (auto it = indices.cbegin(); it != indices.cend(); ++it)
		{
			bitset<16> result = Bitwise::SwapBits(number.to_ullong(), it->first, it->second);
			cout << number << ":(" << it->first << "," << it->second << ") -> " << result << (it != indices.cend() - 1 ? ", " : "") << endl;
		}
	}
	cout << endl;

	cout << "- Bit Reverse -" << endl;
	{
		vector<bitset<16>> numbers2 = { bitset<16>(string("1110000000011111")), bitset<16>(string("0000111111110000")),
			bitset<16>(string("1111111100000000")), bitset<16>(string("1000000101111110")) };
		for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
		{
			bitset<16> result = Bitwise::ReverseBits((unsigned short)it->to_ulong());
			cout << *it << " -> " << result << (it != numbers2.cend() - 1 ? ", " : "") << endl;
		}
	}
	cout << endl;

	cout << "- Power Set -" << endl;
	{
		vector<string> inputSet = { "A", "B", "C", "D" };
		auto powerSet = Bitwise::GenereatePowerSet(inputSet);
		cout << "Initial set: { ";
		for (auto item = inputSet.cbegin(); item != inputSet.cend(); ++item)
		{
			cout << *item << (item != inputSet.cend() - 1 ? ", " : "");
		}
		cout << " }" << endl;
		cout << "Power set (" << powerSet.size() << "): ";
		for (auto subset = powerSet.cbegin(); subset != powerSet.cend(); ++subset)
		{
			cout << "{ ";
			for (auto it = subset->cbegin(); it != subset->cend(); ++it)
			{
				cout << *it << (it != subset->cend() - 1 ? "," : "");
			}
			cout << (subset != powerSet.cend() - 1 ? " }, " : " }");
		}
	}
	cout << endl;

	cout << endl << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

