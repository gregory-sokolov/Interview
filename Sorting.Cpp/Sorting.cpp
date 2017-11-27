/// 
/// EPI. Chapter 13. Sorting
///

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

#include "Sorting.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Sorting ==" << endl << endl;

	cout << "- Quick sort -" << endl;
	{
		unsigned cnt = 1;
		vector<vector<int>> vvi = 
		{ 
			{ 7, 5, 2, 8, 0, 2, 5 }, { 5, 7, 2, 0, 8, 2, 5 },
			{ 1, 2, 3, 4, 5, 6, 7 }, { 7, 6, 5, 4, 3, 2, 1 }, { 1, 1, 1, 1, 1, 1, 1 }
		};
		for (auto vi = vvi.begin(); vi != vvi.end(); ++vi)
		{
			cout << "Source-0" << cnt << ": ";
			for (auto it = vi->cbegin(); it != vi->cend(); ++it)
			{
				cout << *it << (it != vi->cend() - 1 ? ", " : "");
			}
			cout << endl;

			if (vi == vvi.begin())
			{
				Sorting::QuickSortDebugNR(&((*vi)[0]), vi->size(), -2);
			}
			else
			{
				Sorting::QuickSortNR(&((*vi)[0]), vi->size());
			}

			cout << "Result-0" << cnt++ << ": ";
			for (auto it = vi->cbegin(); it != vi->cend(); ++it)
			{
				cout << *it << (it != vi->cend() - 1 ? ", " : "");
			}
			cout << endl << endl;
		}
	}
	cout << endl;

	cout << "- Dutch national flag -" << endl;
	{
		vector<int> numbers = { 7, 5, 0, 6, 2, 2, 5, 8, 0, 2, 5, 8, 7, 1, 3 };
		vector<int> vi = { 1, 5, 7, 8 };
		cout << "Source" << ": ";
		for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
		{
			cout << *it << (it != numbers.cend() - 1 ? ", " : "");
		}
		cout << endl << "--" << endl;
		for (auto idx = vi.cbegin(); idx != vi.cend(); ++idx)
		{
			auto vn1 = numbers;
			Sorting::DnfPartition(vn1, *idx);
			cout << "V.1: [" << *idx << "]=" << numbers[*idx] << ": ";
			for (auto it = vn1.cbegin(); it != vn1.cend(); ++it)
			{
				cout << *it << (it != vn1.cend() - 1 ? ", " : "");
			}
			cout << endl;
			auto vn2 = numbers;
			Sorting::DnfPartition(&vn2[0], vn2.size(), *idx);
			cout << "V.2: [" << *idx << "]=" << numbers[*idx] << ": ";
			for (auto it = vn2.cbegin(); it != vn2.cend(); ++it)
			{
				cout << *it << (it != vn2.cend() - 1 ? ", " : "");
			}
			cout << endl << "--" << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

