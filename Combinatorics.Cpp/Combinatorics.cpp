/// 
/// Combinatorial Problems
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <iterator>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Combinatorics.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Combinatorics ==" << endl << endl;

	cout << "- Permutations -" << endl;
	{
		vector<vector<unsigned>> results1;
		unsigned* pmt0 = NULL;
		cout << "Permutation input: (empty)" << endl;
		Combinatorics::PermutationsR(pmt0, 0, 0, results1);
		cout << "Permutation count: " << results1.size() << endl;
		cout << "Permutations: ";
		for (auto it = results1.begin(); it < results1.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}

		unsigned pmti[] = { 1, 2, 3, 4 };
		cout << "Permutation input: ";
		copy(pmti, pmti + sizeof(pmti) / sizeof(int), ostream_iterator<unsigned>(cout));
		cout << endl;
		Combinatorics::PermutationsR(pmti, sizeof(pmti) / sizeof(unsigned), sizeof(pmti) / sizeof(unsigned), results1);
		cout << "Permutation count: " << results1.size() << endl;
		cout << "Permutations: ";
		for (auto it = results1.begin(); it < results1.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Longest sum subarray (LSSA) -" << endl;
	{
		vector<int> vi1 = { 7, 3, 5, 2, 10, 5, 0, 15, 0, 0, 12, 3 };
		//vector<int> vi2 = { 1, 2, 2, 0, 5, -5, 0, 8, -8, 1, 7, -3 };
		cout << "Input array: ";
		for (auto it = vi1.cbegin(); it != vi1.cend(); ++it)
		{
			cout << *it << (it != vi1.end() - 1 ? ", " : "");
		}
		cout << endl;
		long long sum = 15;
		// long long sum = 0;
		cout << "Sum to match: " << sum << endl;
		vector<deque<pair<unsigned, int>>> matches;
		Combinatorics::Lssa(vi1, sum, matches);
		cout << "Sequences" << (matches.size() != 0 ? " ("+ to_string(matches.size()) + "): " : ": not found") << endl;
		deque<pair<unsigned, int>> result;
		if (!matches.empty())
		{
			for (auto mi = matches.begin(); mi != matches.end(); ++mi)
			{
				cout << "[";
				for (auto it = mi->cbegin(); it != mi->cend(); ++it)
				{
					cout << it->first << (it != mi->end() - 1 ? "," : "]: ");
				}
				for (auto it = mi->cbegin(); it != mi->cend(); ++it)
				{
					cout << it->second << (it != mi->end() - 1 ? " " : "");
				}
				cout << (mi != matches.end() - 1 ? ", " : "");

				if (mi->size() > result.size())
				{
					result = *mi;
				}
			}
			cout << endl;

			cout << "Result: [";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << it->first << (it != result.end() - 1 ? "," : "]: ");
			}
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << it->second << (it != result.end() - 1 ? " " : "");
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Custom LSSA: two- and three-sum -" << endl;
	{
		vector<int> vi3 = { 1, 2, 2, 5, -5, 8, 8, 1, 7, -3 };
		vector<int> vi4(vi3);
		cout << "Input array: ";
		copy(vi3.begin(), vi3.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
		for (auto&& sum : { 10, 23 })
		{
			cout << "Sum to match: " << sum << endl;
			auto found2 = Combinatorics::HasTwoSum(vi4, sum);
			auto found3 = Combinatorics::HasThreeSum(vi4, sum);
			cout << "Any 2-combination found: " << (found2 ? "true" : "false") << endl;
			cout << "Any 3-combination found: " << (found3 ? "true" : "false") << endl;
			vector<vector<int>> matches;
			Combinatorics::ThreeSumCombinations(vi3, sum, matches);
			cout << "All combinations: " << matches.size() << endl;
			for (auto mi = matches.begin(); mi != matches.end(); ++mi)
			{
				cout << "[" << mi->at(0) << "," << mi->at(2) << "," << mi->at(4) << "]: " <<
					mi->at(1) << " " << mi->at(3) << " " << mi->at(5) << (mi != matches.end() - 1 ? ", " : "");
			}
			cout << endl;
		}
		int low = 0, high = 20;
		cout << "Non-matching sums in range [" << low << "; " << high << "]: ";
		for (int sum = low; sum < high; ++sum)
		{
			auto found = Combinatorics::HasThreeSum(vi4, sum);
			if (!found)
			{
				cout << sum << (sum < high - 1 ? ", " : "");
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Longest common subsequence (LCSS) -" << endl;
	{
		vector<pair<string, string>> testLcss = 
		{ 
			{ "", "" },
			{ "ABC", "" },
			{ "", "abc" },
			{ "AGGTAB", "GXTXAYB" },
			{ "hello world", "hlwrld" },
			{ "abcdefghijklmn", "oprstuvwxyz" },
			{ "JATAXGPDMYLDXUKDNFTPRRUMBMEMLROWRHWOQNTCLGHLCRORZHGSBAECPLPCCDYVNXMDMFHAOPLQ", "IZKHIQBJTIMITDKXIKSXJECWMKWABHSL" }

		};
		unsigned i = 0;
		for (auto&& test : testLcss)
		{
			auto result = Combinatorics::Lcss(test.first, test.second);

			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << ++i << ":" << endl;
			cout << "(" << test.first.size() << "): " << test.first << endl;
			cout << "(" << test.second.size() << "): " << test.second << endl;
			cout << "Result (" << result.size() << "): " << (result.size() > 0 ? result : "-") << endl;
			cout << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

