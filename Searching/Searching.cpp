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

	cout << "- Unique number -" << endl;
	{
		vector<int> vi01 = { 1, 7, -2, 6, 12, 12, 7, 3, -2, 1, 6 };
		auto result1 = Searching::UniqueNumberHT(vi01);
		auto result2 = Searching::UniqueNumberXOR(vi01);
		cout << "Source (" + to_string(vi01.size()) + "): ";
		for (auto it = vi01.cbegin(); it != vi01.cend(); ++it)
		{
			cout << *it << (it != vi01.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Result: " << to_string(result1) << "/" << result2 << endl;
	}
	cout << endl;

	cout << "- Equal to index -" << endl;
	{
		vector<vector<int>> tests =
		{
		  {},
		  { 0 },
		  { 1 },
		  { 0, 1 },
		  { 1, 2 },
		  { -3, 0, 2, 3 },
		  { -3, -1, 1, 2, 4 },
		  { -6, -5, -4, -1, 1, 3, 5, 7 },
		  { -8, -5, 0, 3, 4, 5, 9, 11, 15, 19, 23, 27, 29, 31, 33, 37, 43 }
		};

		for (auto vi = tests.cbegin(); vi != tests.cend(); ++vi)
		{
			if (!vi->empty())
			{
				for (auto it = vi->cbegin(); it != vi->cend(); ++it)
				{
					cout << *it << (it != vi->cend() - 1 ? ", " : "");
				}
			}
			else
			{
				cout << "[]";
			}
			cout << ": ";

			auto result = Searching::EqualToIndex(*vi);
			cout << result << endl;
		}
	}
	cout << endl;

	cout << "- Most Frequent Items -" << endl;
	{
		unsigned top = 3;
		vector<vector<int>> tests =
		{
			{ },
			{ 0 },
			{ 0, 0 },
			{ 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 1, 2, 4, 4, 4, 4, 4 },
			{ 0, 1, 1, 2, 2, 2, 3, 4, 4, 4, 5 },
			{ 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 7 }
		};
		for (auto vi = tests.begin(); vi != tests.end(); ++vi)
		{
			if (!vi->empty())
			{
				string input;
				for (auto it = vi->cbegin(); it != vi->cend(); ++it)
				{
					input += to_string(*it) + (it != vi->cend() - 1 ? ", " : "");
				}
				cout << input;
			}
			else
			{
				cout << "[]";
			}
			cout << ": ";

			cout << "[";
			auto results = Searching::MostFrequent(*vi, top);
			for (auto it = results.cbegin(); it != results.cend(); ++it)
			{
				cout << it->first << ":" << it->second << (it != results.end() - 1 ? ", " : "");
			}
			cout << "]" << endl;
		}
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

	cout << "- Two/three-sum and diff -" << endl;
	{
		vector<int> vi = { 1, 2, 2, 5, -5, 8, 8, 1, 7, -3 };
		cout << "Input array: ";
		copy(vi.begin(), vi.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;

		for (auto&& sum : { 10, 23 })
		{
			cout << "Sum to match: " << sum << endl;
			vector<int> vi1(vi);
			auto found2 = Searching::HasTwoSum(vi1, sum);
			cout << "  Any 2-combination found: " << (found2 ? "true" : "false") << endl;
			vector<int> vi2(vi);
			auto found3 = Searching::HasThreeSum(vi2, sum);
			cout << "  Any 3-combination found: " << (found3 ? "true" : "false") << endl;

			vector<int> vi3(vi);
			auto allThree3 = Searching::AllThreeSum(vi3, sum);
			cout << "  All triplets (" << allThree3.size() << "): ";
			for (auto mi = allThree3.begin(); mi != allThree3.end(); ++mi)
			{
				cout << mi->at(0) << " " << mi->at(1) << " " << mi->at(2) << (mi != allThree3.end() - 1 ? ", " : "");
			}
			cout << endl;

			vector<int> vi4(vi);
			auto combins = Searching::AllThreeSumCombinations(vi4, sum);
			cout << "  All combinations (" << combins.size() << "): ";
			for (auto mi = combins.begin(); mi != combins.end(); ++mi)
			{
				cout << "[" << mi->at(0) << "," << mi->at(2) << "," << mi->at(4) << "]: " <<
					mi->at(1) << " " << mi->at(3) << " " << mi->at(5) << (mi != combins.end() - 1 ? ", " : "");
			}
			cout << endl;
		}

		int low = 0, high = 20;
		vector<int> vi5(vi);
		cout << "No 3-sum match in range [" << low << "; " << high << "]: ";
		for (int sum = low; sum < high; ++sum)
		{
			auto found = Searching::HasThreeSum(vi5, sum);
			if (!found)
			{
				cout << sum << (sum < high - 1 ? ", " : "");
			}
		}
		cout << endl << endl;

		vector<int> vi6 = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
		cout << "Input array: a[3000] = { 0 }" << endl;
		auto allThree6 = Searching::AllThreeSum(vi6, 0);
		cout << "  All triplets (" << allThree6.size() << "): ";
		for (auto mi = allThree6.begin(); mi != allThree6.end(); ++mi)
		{
			cout << mi->at(0) << " " << mi->at(1) << " " << mi->at(2) << (mi != allThree6.end() - 1 ? ", " : "");
		}
		cout << endl << endl;

		cout << "All unique 2-diff pairs:" << endl;
		for (const auto& diff : { 0, 3, 7, 20 })
		{
			auto uniqueDiffs1 = Searching::UniqueTwoDiff(vi, diff);
			cout << "Diff: " << diff << ", (" << uniqueDiffs1.size() << "): ";
			for (auto mi = uniqueDiffs1.begin(); mi != uniqueDiffs1.end(); ++mi)
			{
				cout << mi->first << ";" << mi->second << (mi != uniqueDiffs1.end() - 1 ? ", " : "");
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

