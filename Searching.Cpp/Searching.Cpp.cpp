/// 
/// EPI. Chapter 11. Searching Problems
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "Searching.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	cout << "- Linear: Two Maximums -" << endl;
	{
		vector<int> vi01 = { 1, 7, -2, 6, 12, 7, 7, 3, 10, -8, 16, 0 };
		auto result = Searching::FindTwoMaximums(vi01);

		cout << "Source (" + to_string(vi01.size()) + "): ";
		for (auto it = vi01.cbegin(); it != vi01.cend(); ++it)
		{
			cout << *it << (it != vi01.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Result: (" << to_string(result.first) << ", " << to_string(result.second) << ")" << endl;
	}
	cout << endl;

	cout << "- Linear: Sorted Matrix -" << endl;
	{
		vector<vector<int>> mx01 = 
		{
			{ 2, 8, 12, 20 },
			{ 4, 14, 16, 25 },
			{ 8, 17, 21, 25 },
			{ 15, 19, 29, 32 }
		};
		vector<int> tests = { 0, 18, 25, 19, 32, 100 };
		vector<pair<int, int>> res01, res02;
		transform(tests.cbegin(), tests.cend(), back_inserter(res01),
			[&mx01](const int x) { return Searching::SearchSortedMatrixBs(mx01, x); });
		transform(tests.cbegin(), tests.cend(), back_inserter(res02),
			[&mx01](const int x) { return Searching::SearchSortedMatrixDs(mx01, x); });

		cout << "Source (" + to_string(mx01.size()) + "*" + to_string(mx01[0].size()) + "): " << endl;
		for (auto row = mx01.cbegin(); row != mx01.cend(); ++row)
		{
			for (auto it = row->cbegin(); it != row->cend(); ++it)
			{
				cout << setiosflags(ios::right) << setw(2) << *it << (it != row->cend() - 1 ? " " : "");
			}
			cout << endl;
		}
		for (unsigned i = 0; i < tests.size(); ++i)
		{
			cout << "Result: " << to_string(tests[i]) << 
				" -> BS: (" << to_string(res01[i].first) << "," << to_string(res01[i].second) << ")" << 
				", DS: (" << to_string(res02[i].first) << "," << to_string(res02[i].second) << ")" << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

