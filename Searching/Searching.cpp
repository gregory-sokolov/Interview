/// 
/// EPI. Chapter 11. Searching Problems
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <map>

#include "Searching.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	cout << "- Two maximums -" << endl;
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

	cout << "- Search in sorted matrix -" << endl;
	{
		vector<vector<int>> mx01 = 
		{
			{ 2, 8, 12, 20 },
			{ 4, 14, 16, 25 },
			{ 8, 17, 21, 25 },
			{ 15, 19, 29, 32 }
		};
		vector<int> testSortedMx = { 0, 18, 25, 19, 32, 100 };
		vector<pair<int, int>> res01, res02;
		transform(testSortedMx.cbegin(), testSortedMx.cend(), back_inserter(res01),
			[&mx01](const int x) { return Searching::SearchSortedMatrixBs(mx01, x); });
		transform(testSortedMx.cbegin(), testSortedMx.cend(), back_inserter(res02),
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
		for (unsigned i = 0; i < testSortedMx.size(); ++i)
		{
			cout << "Result: " << to_string(testSortedMx[i]) <<
				" -> BS: (" << to_string(res01[i].first) << "," << to_string(res01[i].second) << ")" << 
				", DS: (" << to_string(res02[i].first) << "," << to_string(res02[i].second) << ")" << endl;
		}
	}
	cout << endl;

	cout << "- Two- and three-sum -" << endl;
	{
		vector<int> vi3 = { 1, 2, 2, 5, -5, 8, 8, 1, 7, -3 };
		vector<int> vi4(vi3);
		cout << "Input array: ";
		copy(vi3.begin(), vi3.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
		for (auto&& sum : { 10, 23 })
		{
			cout << "Sum to match: " << sum << endl;
			auto found2 = Searching::HasTwoSum(vi4, sum);
			auto found3 = Searching::HasThreeSum(vi4, sum);
			cout << "  Any 2-combination found: " << (found2 ? "true" : "false") << endl;
			cout << "  Any 3-combination found: " << (found3 ? "true" : "false") << endl;
			vector<vector<int>> matches;
			Searching::ThreeSumCombinations(vi3, sum, matches);
			cout << "  All combinations (" << matches.size() << "): ";
			for (auto mi = matches.begin(); mi != matches.end(); ++mi)
			{
				cout << "[" << mi->at(0) << "," << mi->at(2) << "," << mi->at(4) << "]: " <<
					mi->at(1) << " " << mi->at(3) << " " << mi->at(5) << (mi != matches.end() - 1 ? ", " : "");
			}
			cout << endl;
		}
		int low = 0, high = 20;
		cout << "No 3-match in range [" << low << "; " << high << "]: ";
		for (int sum = low; sum < high; ++sum)
		{
			auto found = Searching::HasThreeSum(vi4, sum);
			if (!found)
			{
				cout << sum << (sum < high - 1 ? ", " : "");
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

