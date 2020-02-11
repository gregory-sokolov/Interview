/// 
/// EPI. Chapter 13. Sorting
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
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

	cout << "- Merge sort -" << endl;
	{
		vector<pair<vector<int>, vector<int>>> mergeTests =
		{
			make_pair(vector<int>({ 4, 7, 11, 13, 15 }), vector<int>()),
			make_pair(vector<int>(), vector<int>({ 2, 9, 17, 20 })),
			make_pair(vector<int>({ 4, 7, 11, 13, 15, 25 }), vector<int>({ 2, 9, 11, 17, 20, 25 }))
		};
		for (auto&& test : mergeTests)
		{
			cout << "Vector 1: [";
			for (auto it = test.first.cbegin(); it != test.first.cend(); ++it)
			{
				cout << *it << (it != test.first.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
			cout << "Vector 2: [";
			for (auto it = test.second.cbegin(); it != test.second.cend(); ++it)
			{
				cout << *it << (it != test.second.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;

			auto result = Sorting::MergeSorted(test.first, test.second);
			cout << "Result: [";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << *it << (it != result.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
			vector<int> check;
			merge(test.first.cbegin(), test.first.cend(), test.second.cbegin(), test.second.cend(), back_inserter(check));
			cout << "Merged: [";
			for (auto it = check.cbegin(); it != check.cend(); ++it)
			{
				cout << *it << (it != check.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
			vector<int> common;
			set_intersection(test.first.cbegin(), test.first.cend(), test.second.cbegin(), test.second.cend(), back_inserter(common));
			cout << "Common: [";
			for (auto it = common.cbegin(); it != common.cend(); ++it)
			{
				cout << *it << (it != common.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
			cout << "--" << endl;
		}
	}
	cout << endl;

	cout << "- Deduplicate sorted array -" << endl;
	{
		vector<vector<int>> tests =
		{
			{ },
			{ 0 },
			{ 0, 0 },
			{ 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 1, 2, 4, 4 },
			{ 0, 1, 1, 2, 2, 2, 3, 4, 4, 5 },
			{ 0, 0, 0, 1, 1, 2, 2, 2, 2, 3, 4, 4, 4, 5, 5, 7 }
		};
		for (auto vi = tests.begin(); vi != tests.end(); ++vi)
		{
			string input;
			for (auto it = vi->cbegin(); it != vi->cend(); ++it)
			{
				input += to_string(*it) + (it != vi->cend() - 1 ? ", " : "");
			}
			cout << input << ": ";

			string output;
			auto result = Sorting::DeduplicateSorted(*vi);
			for (auto it = vi->cbegin(); it != vi->cend(); ++it)
			{
				output += to_string(*it) + (it != vi->cend() - 1 ? ", " : "");
			}
			cout << "[" << result << "] " << output << endl;
			cout << "--" << endl;
		}
	}
	cout << endl;

	cout << "- Intersection of sorted arrays -" << endl;
	{
		vector<pair<vector<int>, vector<int>>> tests =
		{
			{ {}, {} },
			{ {}, { 0 } },
			{ { 0 }, {} },
			{ { 0 }, { 1 } },
			{ { 0 }, { 0 } },
			{ { 0 }, { 0, 1 } },
			{ { 0, 1 }, { 1 } },
			{ { 0, 1 }, { 0, 1 } },
			{ { 0, 1 }, { 1, 2 } },
			{ { 0, 1, 1, 1, 2 }, { 1, 2, 2, 2, 2, 3, 5 } },
			{ { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { -9, -8, -7, -6, -5, -4, -3, -2, -1, 0 } },
			{ { 1, 2, 3, 4, 5, 6, 7, 8, 9 }, { -9, -8, -7, -6, -5, -4, -3, -2, -1 } },
			{ { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21 }, { 0, 2, 4, 6, 8, 10, 12, 14, 16, 18 } }
		};
		for (auto test = tests.begin(); test != tests.end(); ++test)
		{
			string input1;
			for (auto it = test->first.cbegin(); it != test->first.cend(); ++it)
			{
				input1 += to_string(*it) + (it != test->first.cend() - 1 ? ", " : "");
			}
			string input2;
			for (auto it = test->second.cbegin(); it != test->second.cend(); ++it)
			{
				input2 += to_string(*it) + (it != test->second.cend() - 1 ? ", " : "");
			}
			cout << "[" << input1 << "], [" << input2 << "]: ";

			string output1, output2;
			auto result1 = Sorting::ArrayIntersectionBS(test->first, test->second);
			auto result2 = Sorting::ArrayIntersectionTP(test->first, test->second);
			for (auto it = result1.cbegin(); it != result1.cend(); ++it)
			{
				output1 += to_string(*it) + (it != result1.cend() - 1 ? ", " : "");
			}
			for (auto it = result2.cbegin(); it != result2.cend(); ++it)
			{
				output2 += to_string(*it) + (it != result2.cend() - 1 ? ", " : "");
			}
			cout << "(" << result1.size() << "/" << result2.size() << "), [" << output1 << "], [" << output2 << "]" << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

