// 
// C++: Exercises
//
#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <bitset>
#include <limits>
#include <cmath>
#include <ctime>

#include "Cpp.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Program has started" << endl;

    cout << "== C++ ==" << endl << endl;
	{
		cout << "-- Types started --" << endl;
		{
			//for (unsigned int i = 100; i >= 0; i--)
			//{	
			//	  printf("%d", i); 
			//}
			// Infinite loop because of unsigned never becomes negative

			cout << endl;
		}
		cout << endl;

		cout << "-- References started --" << endl;
		{
			int i1 = 1;
			int& r1 = i1;
			// int& r2; // error: not initialized
			cout << "r1 = i1; i1 = " << i1 << ", r1 = " << r1 << endl;

			int i2 = r1;
			cout << "i2 = r1: i2 = " << i2 << endl;

			r1 = 2;
			cout << "r1 = 2: r1 = " << r1 << ", i1 = " << i1 << ", i2 = " << i2 << endl;

			r1++;
			cout << "r1++: r1 = " << r1 << ", i1 = " << i1 << ", i2 = " << i2 << endl;

			int* pp = &r1;
			cout << "pp = &r1: r1 = " << r1 << ", *pp = " << *pp << " (pp = 0x" << pp << ")" << endl;

			int i3 = 49;
			float f2 = 3.14F;
			//double& dr1 = 18; // const int -> double&
			//double& dr1 = i3; // int -> double&
			//double& dr2 = f2;  // float -> double&
			const double& cdr = 1;

			string str1 = "AAA";
			string& rstr1 = str1;
			{
				string str2 = "BBB";
				rstr1 = str2;
			}
			cout << "Refs and scope: " << rstr1 << endl;

			class ArrayByValue
			{
			public:
				int f(int arr[], int size) { arr[0] = 1000; arr[1] = 1001; return size; }
			};

			ArrayByValue abv;

			int array[] = { 100, 101, 102, 103, 104 };
			abv.f(array, sizeof(array));
			for (auto&& ai : array)
			{
				cout << ai << " ";
			}
			cout << endl;
		}
		cout << endl;

		cout << "-- Inheritance started --" << endl;
		{
			AAA* a1 = new AAA(10);
			AAA* b1 = new BBB(20);
			BBB* b2 = new BBB(20);
			AAA* a2 = a1;
			AAA* a3 = b1;
			//BBB* b3 = a1; // Cast base to derived
			//BBB* b4 = b1; // Type of b1 is still AAA
			BBB* b5 = b2;

			AAA* aa2 = new AAA(10);
			AAA* bb2 = new BBB(20);
			*aa2 = *bb2;
			delete aa2;
			//delete bb2; // Double delete because of slice-effect

			auto pva = new vector<AAA*>(2);
			auto pvb = new vector<BBB*>(5);
			//pva = pvb; // Template covariance error

			Converter cv;
			auto ci = (int)cv;
			cout << "Class to int: " << ci << endl;
			//Derived d; // Pure virtual call

			vector<AAA*> va = { new AAA(12), new BBB(24), new BBB(32) };
			for (AAA* pa : va)
			{
				cout << pa << " ";
			}
			cout << endl;
		}
		cout << endl;

		cout << "-- Containers started --" << endl;
		{
			// Iterating through a vector
			vector<int> vi = { 2, 5, 99, 0, -3, 999, -365, 1, 0, 5, 75 };
			cout << "Vector, vi[i]: ";
			for (unsigned i = 0; i < vi.size(); ++i)
			{
				cout << vi[i] << " ";
			}
			cout << endl;

			cout << "Vector, *(pvi+i): ";
			auto pvi = vi.data();
			for (unsigned i = 0; i < vi.size(); ++i)
			{
				cout << *(pvi + i) << " ";
			}
			cout << endl;

			cout << "Vector, *it: ";
			for (auto it = vi.cbegin(); it != vi.cend(); ++it)
			{
				cout << *it << " ";
			}
			cout << endl;

			cout << "Vector, for: : ";
			for (const auto& it : vi)
			{
				cout << it << " ";
			}
			cout << endl << endl;
		
			// STL: working with matrixes
			int mxm = 4, mxn = 3;
			vector<vector<unsigned>> mx01(mxm, vector<unsigned>(mxn));
			cout << "Matrix (" << mxm << "*" << mxn << "):" << endl;
			for (const auto & row : mx01)
			{
				for (auto it = row.cbegin(); it != row.cend(); ++it)
				{
					//cout << setiosflags(ios::right) << setw(2) << setfill('0');
					cout << *it << (it != row.cend() - 1 ? " " : "");
				}
				cout << endl;
			}
			cout << endl;

			map<unsigned, string> stats = { make_pair(53, "cd"), make_pair(26, "cp"), 
				                       make_pair(12, "mv"), make_pair(49, "dir")};
			cout << "Command usage statistics:" << endl;
			for (auto it = stats.crbegin(); it != stats.crend(); ++it)
			{
				cout << it->second << ": " << it->first << (std::next(it) != stats.crend() ? ", " : "");
			}
			cout << endl;
		}
		cout << endl;

		cout << "-- Algorithms started --" << endl;
		{
			vector<int> vi = { 2, 5, 99, 0, -3, 999, 99, -365, 1, 0, 5, 75 };
			for_each(vi.cbegin(), vi.cend(), [&](const auto& it) { cout << it << " "; });
			cout << endl;

			const int limit = 52;
			auto found = find_if(vi.cbegin(), vi.cend(), [&](auto it) { return it > limit; });
			cout << "First value > " << limit << ": " << (found != vi.cend() ? to_string(*found) : "-");
			cout << endl;

			multiset<int> fssi;
			copy_if(vi.cbegin(), vi.cend(), inserter(fssi, fssi.begin()), [&](const auto& it) { return it > limit; });
			cout << "Values > " << limit << ": ";
			for_each(fssi.cbegin(), fssi.cend(), [&](const auto& it) { cout << it << " "; });
			cout << (fssi.empty() ? "-" : "");
			cout << endl << endl;

			// STL: std::transform one vector to another
			vector<pair<int, int>> vpii = { make_pair(1, 2), make_pair(3, 1), make_pair(5, 4), make_pair(7, 8) };
			vector<int> vt;
			transform(vpii.cbegin(), vpii.cend(), back_inserter(vt), [](const pair<int, int>& p) { return p.first; });
			cout << "Source: ";
			for (auto it = vpii.cbegin(); it != vpii.cend(); ++it)
			{
				cout << "(" + to_string(it->first) + "," + to_string(it->second) + ")" << (it != vpii.cend() - 1 ? ", " : "");
			}
			cout << endl;
			cout << "Result: ";
			for (auto it = vt.cbegin(); it != vt.cend(); ++it)
			{
				cout << *it << (it != vt.cend() - 1 ? ", " : "");
			}
			cout << endl << endl;

			// Fibonacci with recursive lambda
			const int fib_max = 12;
			std::cout << "Fibonacci, recursive lambda #1 (n = " << fib_max << "): ";
			auto nth_fib1 = [](int n)
			{
				std::function<int(int, int, int)> fib = [&](int n, int a, int b)
				{
					return n ? fib(n - 1, a + b, a) : b;
				};
				return fib(n, 0, 1);
			};
			for (int i = 1; i <= fib_max; ++i)
			{
				std::cout << nth_fib1(i) << (i < fib_max ? ", " : "");
			}
			cout << endl;

			// Fibonacci with recursive lambda, alternative approach
			std::cout << "Fibonacci, recursive lambda #2 (n = " << fib_max << "): ";
			auto nth_fib2 = [](auto self, int n, int a = 0, int b = 1) -> int
			{
				return n ? self(self, n - 1, a + b, a) : b;
			};
			for (int i = 1; i <= fib_max; ++i)
			{
				std::cout << nth_fib2(nth_fib2, i) << (i < fib_max ? ", " : "");
			}
			cout << endl;
		}
		cout << endl;

		cout << "-- Upper-lower bound started --" << endl;
		{
			vector<int> vi01 = { 1, 1, 2, 3, 5, 7, 7, 9, 10, 12, 15, 17 };
			auto bs1 = lower_bound(vi01.cbegin(), vi01.cend(), 7);
			auto bs2 = lower_bound(vi01.cbegin(), vi01.cend(), 12);
			auto bs3 = upper_bound(vi01.cbegin(), vi01.cend(), 7);
			auto bs4 = upper_bound(vi01.cbegin(), vi01.cend(), 12);
			auto bs5 = lower_bound(vi01.cbegin(), vi01.cend(), 4);
			auto bs6 = upper_bound(vi01.cbegin(), vi01.cend(), 4);
			auto bs7 = lower_bound(vi01.cbegin(), vi01.cend(), 21);
			auto bs8 = upper_bound(vi01.cbegin(), vi01.cend(), 21);
			cout << "Source (" + to_string(vi01.size()) + "): ";
			for (auto it = vi01.cbegin(); it != vi01.cend(); ++it)
			{
				cout << *it << (it != vi01.cend() - 1 ? ", " : "");
			}
			cout << endl;
			cout << "Value: 7, lower_bound: [" << bs1 - vi01.cbegin() << "]" << endl;
			cout << "Value: 12, lower_bound: [" << bs2 - vi01.cbegin() << "]" << endl;
			cout << "Value: 7, upper_bound: [" << bs3 - vi01.cbegin() << "]" << endl;
			cout << "Value: 12, upper_bound: [" << bs4 - vi01.cbegin() << "]" << endl;
			cout << "Value: 4, lower_bound: [" << bs5 - vi01.cbegin() << "]" << endl;
			cout << "Value: 4, upper_bound: [" << bs6 - vi01.cbegin() << "]" << endl;
			cout << "Value: 21, lower_bound: [" << bs7 - vi01.cbegin() << "]" << endl;
			cout << "Value: 21, upper_bound: [" << bs8 - vi01.cbegin() << "]" << endl;
		}
		cout << endl;

		cout << "-- Move-ctor started --" << endl;
		{
			ItemEx item("123", "456");
			cout << item.GetContent() << endl;
			ItemEx newItem = std::move(item);
			cout << "After move, new item: " << newItem.GetContent() << endl;
			auto itemContent = item.GetContent();
			cout << "After move, old item: " << (itemContent != "" ? itemContent : "-") << endl;
		}
		cout << endl;

		cout << "-- Template type inference started --" << endl;
		{
			const string s = "1234";
			auto v32 = BuildFromString<vector<uint32_t>>(s)[0];
			auto v16 = BuildFromString<vector<uint16_t>>(s)[1];
			// auto vbb = BuildFromString<vector<bool>>(s)[2]; // program crash here, casting char to bit in vector<bool>
			auto vbb = BuildFromString<vector<char>>(s)[2];
			cout << "Auto-type: " << v32 << " " << v16 << " " << vbb << endl;

			TInt<int, 200> v200;
			cout << "Template default args: array size = " << sizeof(v200._arr)/sizeof(int) << endl;
			TDef<> td(-1, 2.7);
			cout << "Template merge args: [" << td.x << ", " << td.y << "]" << endl;

			int x = 27;
			const int cx = x;
			const int& rx = x;
			typeInferer(x);
			typeInferer(cx);
			typeInferer(rx);
			typeInferer(27);
			auto ax = rx;
			auto& arx = x;
			const auto& arcx = x;
			cout << "Type inference: " << x << ", " << cx << ", " << rx << ", " << ax << ", " << arx << ", " << arcx;
			cout << endl;
		}
		cout << endl;
    }

    cout << "Program has completed" << endl;
    system("PAUSE");
    return 0;
}
