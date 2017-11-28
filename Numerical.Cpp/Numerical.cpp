/// 
/// EPI. Chapter 6. Numerical Problems
///
#include "stdafx.h"

#include <iostream>
#include <sstream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <tuple>

#include "Numerical.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Numerical ==" << endl << endl;

	cout << "- Conversions: int-string -" << endl;
	{
		vector<int> vs11 = { 0, 1, 12, 147, 65536, INT_MAX, -1, -16, -65536, INT_MIN };
		for (auto vi = vs11.cbegin(); vi != vs11.cend(); ++vi)
		{
			auto result = Numerical::IntToString(*vi);
			cout << *vi << ": " << result << (vi != vs11.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Conversions: string-int -" << endl;
	{
		vector<string> vs12 = { "0", "1", "12", "147", "65536", "2147483647", "-1", "-16", "-65536", "-2147483648" };
		for (auto si = vs12.cbegin(); si != vs12.cend(); ++si)
		{
			auto result = Numerical::StringToInt(*si);
			cout << *si << ": " << result << (si != vs12.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Conversions: numerical systems -" << endl;
	{
		vector<pair<vector<string>, vector<pair<int, int>>>> vbm21 = {
			{
				{ "0", "1", "2", "3", "4", "9", "35", "61", "234", "-1", "-5", "-128", "", "-0", "+0", "1A", "-1A", "1--1", "10M" },
				{ { 10, 2 }, { 10, 8 }, { 10, 12 }, { 10, 16 } }
			},
			{
				{ "0", "1", "10", "11", "100", "1001", "100111", "100001", "1111111", "-1", "-101", "-1000000", "", "-0", "+0", "9", "-1A", "1--1", "10M" },
				{ { 2, 10 }, { 2, 8 }, { 2, 12 }, { 2, 16 } }
			},
			{
				{ "0", "1", "2", "5", "10", "15", "55", "234", "554", "5000", "-1", "-2", "-5", "-225", "-555", "", "-0", "+0", "-1A", "1--1", "10M" },
				{ { 6, 10 }, { 6, 8 }, { 6, 12 }, { 6, 16 } }
			},
			{
				{ "0", "1", "2", "9", "A", "C", "F", "1D", "ACE", "FFFF", "-1", "-9", "-B", "-2C", "-FFFF", "", "-0", "+0", "-1A", "1--1", "10M" },
				{ { 16, 10 }, { 16, 8 }, { 16, 12 }, { 16, 15 } }
			}
		};
		for (auto entry : vbm21)
		{
			for (auto bi : entry.second)
			{
				cout << bi.first << "-" << bi.second << ": ";
				for (auto it = entry.first.cbegin(); it != entry.first.cend(); ++it)
				{
					auto result1 = Numerical::ConvertBase(*it, bi.first, bi.second);
					auto result2 = Numerical::ConvertBase(result1, bi.second, bi.first);
					cout << *it << ":" << result1 << "|" << result1 << ":" << result2 << (it != entry.first.cend() - 1 ? ", " : "");
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "- Excel columns -" << endl;
	{
		vector<string> ids = { "A", "B", "M", "Z", "AA", "AB", "AZ", "BA", "BB", "BZ", "MM", "ZZ", "AAA", "CXA", "ZZZZ", "", "-", "1A", "A-", "A@A", "#$%" };
		for (auto it = ids.cbegin(); it != ids.cend(); ++it)
		{
			cout << *it << ":" << Numerical::ExcelColumnId(*it) << (it != ids.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Elias Gamma Coding -" << endl;
	{
		auto delim = "";
		vector<unsigned> vu = { 1, 2, 9, 1, 32, 100, 128, 65536, INT_MAX };
		auto coded = Numerical::EliasEncode(vu);
		ostringstream text;
		copy(coded.cbegin(), coded.cend(), ostream_iterator<string>(text, delim));
		auto decoded = Numerical::EliasDecode(text.str());
		for (unsigned i = 0; i < vu.size(); ++i)
		{
			cout << vu[i] << ":" << coded[i] << ":" << decoded[i] << (i != vu.size() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Prime numbers -" << endl;
	{
		const unsigned limit = 1000;
		auto primes = Numerical::GeneratePrimes(limit);
		cout << "Limit: " << limit << ", results: " << primes.size() << endl;
		for (auto it = primes.cbegin(); it != primes.cend(); ++it)
		{
			cout << *it << (it != primes.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- GCD -" << endl;
	{
		vector<pair<int, int>> vn = { { 0, 0 }, { 1, 1 }, { 1, 2 }, { 2, 2 }, { 12, 15 }, { 48, 56 }, { 31, 17 }, { 1000, 1000000 },
			{ -12, 15 }, { 12, -15 }, { -12, -15 } };
		for (auto it = vn.cbegin(); it != vn.cend(); ++it)
		{
			auto gcd1 = Numerical::GcdR(it->first, it->second);
			auto gcd2 = Numerical::GcdRmd(it->first, it->second);
			auto gcd3 = Numerical::GcdSub(it->first, it->second);
			cout << it->first << "," << it->second << ":" << gcd1 << ":" << gcd2 << ":" << gcd3 << (it != vn.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Square roots -" << endl;
	{
		cout << "Integers: ";
		vector<unsigned> numbers1 =
		{
			0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
			49, 55, 81, 92, 100, 288, 289, 290, 10000, 99980001
		};
		for (auto it = numbers1.cbegin(); it != numbers1.cend(); ++it)
		{
			cout << *it << ":" << Numerical::Sqrt(*it) << (it != numbers1.cend() - 1 ? ", " : "");
		}
		cout << endl;
		const int digits = 5;
		double precision = 1 / pow(10, digits);
		cout << "Doubles BS (" << digits << "-digits)";
		vector<double> numbers2 =
		{
			0.0, 0.02, 0.04, 0.09, 1, 1.96, 2.0, 3.0, 4, 6.5536, 62.2521, 99999998.00000001
		};
		for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
		{
			cout << *it << ":" << Numerical::Sqrt(*it, precision) << (it != numbers2.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Doubles NR (" << digits << "-digits)";
		for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
		{
			cout << *it << ":" << Numerical::SqrtNewton(*it, precision) << (it != numbers2.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Closest Points -" << endl;
	{
		unsigned k = 4;
		pair<double, double> origin(0.0, 0.0);
		vector<pair<double, double>> vdpi =
		{
			make_pair(2.7, 1.8), make_pair(2.0, 5.9), make_pair(3.7, 3.4), make_pair(9.2, 0.4), make_pair(7.2, 7.5),
			make_pair(5.2, 2.6), make_pair(1.1, 1.3), make_pair(1.5, 2.7), make_pair(3.3, 8.1), make_pair(0.1, 9.9),
			make_pair(0.0, 0.0), make_pair(10.0, 10.0), make_pair(-4.56, 7.89), make_pair(0.3579, -0.2468), make_pair(-5.5, -7.7)
		};
		vector<pair<double, double>> vdpr;
		Numerical::GetClosestPoints(k, origin, vdpi, vdpr);
		cout << "Origin: " << "(" << origin.first << ";" << origin.second << ")" << ", count: " << k << endl;
		cout << "Points: ";
		for (auto pi = vdpi.begin(); pi != vdpi.end(); ++pi)
		{
			cout << "(" << pi->first << ";" << pi->second << ")" << (pi != vdpi.end() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Closest: ";
		for (auto pi = vdpr.begin(); pi != vdpr.end(); ++pi)
		{
			cout << "(" << pi->first << ";" << pi->second << ")" << (pi != vdpr.end() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

