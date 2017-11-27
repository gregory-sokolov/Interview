/// 
/// Combinatorial Problems
///

#include "stdafx.h"

#include <iostream>
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

	cout << "- Sequences to sum -" << endl;
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
		Combinatorics::LongestSumSubarray(vi1, sum, matches);
		cout << "Sequences: " << (matches.size() != 0 ? to_string(matches.size()) : "not found") << endl;
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
		}
		cout << endl << endl;

		vector<int> vi2 = { -2, 2, 0, 0, 5, -5, 0, 1, -4, -1, 0, -7 };
		cout << "Input array: ";
		for (auto it = vi2.cbegin(); it != vi2.cend(); ++it)
		{
			cout << *it << (it != vi2.end() - 1 ? ", " : "");
		}
		cout << endl;
		auto kadane = Combinatorics::MaxSumSubarray(vi2);
		cout << "Max sum subarray (Kadane's): " << kadane.first << ", [" <<
			kadane.second.first << ", " << kadane.second.second << "]";
		cout << endl;
	}
	cout << endl;

	cout << "- Combinations: three-sum -" << endl;
	{
		vector<int> vi3 = { 1, 2, 2, 5, -5, 8, 8, 1, 7, -3 };
		vector<int> vi4(vi3);
		cout << "Input array: ";
		copy(vi3.begin(), vi3.end(), ostream_iterator<int>(cout, ", "));
		cout << endl;
		for (auto&& sum : { 10, 23 })
		{
			cout << "Sum to match: " << sum << endl;
			auto found = Combinatorics::HasThreeSum(vi4, sum);
			cout << "Any combination found: " << (found ? "true" : "false") << endl;
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

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

