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
#include <algorithm>
#include <functional>

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

	cout << "- Max Sum Subarray (MSSA) -" << endl;
	{
		vector<vector<int>> testMssa = 
		{
			{},
			{ 2 },
			{ -1, -5, -2 },
			{ 0, 0, 0 },
			{ 5, 1, 2 },
			{ 2, 5, -1, -7, 0, 9, -3, -4 },
			{ 2, 5, -1, -7, 0, 2, 4, 3, -3, -4 },
			{ 2, 5, -3, -2, 2, 3, 0, -2, 2, 4, 3, -1, -2 }
		};
		for (unsigned i = 0; i < testMssa.size(); ++i)
		{
			string input;
			for (auto it = testMssa[i].cbegin(); it != testMssa[i].cend(); ++it)
			{
				input += to_string(*it) + (it != testMssa[i].end() - 1 ? ", " : "");
			}
			cout << setiosflags(ios::right) << setw(2) << setfill('0') << i << ": [" << input << "]" << endl;
			auto result = Combinatorics::Mssa(testMssa[i]);
			cout << "    " << result.first << " [" << result.second.first << ", " << result.second.second << "]" << endl;
		}
	}
	cout << endl;

	/*Console.WriteLine("== Max Product Subarray (MPSA) ==");
	var testMps = new List<IList<int>>
	{
		new List<int>(),
		new List<int>{ 2 },
		new List<int>{ 2, -2 },
		new List<int>{ 2, 3, 5, 4, 3, 1 },
		new List<int>{ -2, -3, -5, -4, -3, -1 },
		new List<int>{ 2, 3, 5, 0, 7, 5, 1 },
		new List<int>{ -1, -2, -3, 4, 0, -5, 2 },
		new List<int>{ -10, 0, -20, 0, -30, 0, 0, -40 }
	};
	count = 1;
	foreach(var test in testMps)
	{
		Console.WriteLine((count++).ToString().PadLeft(2, '0') + ": [" + string.Join(", ", test) + "]");
		var result = solutions.Mpsa(test);
		Console.WriteLine("    {0} [{1}, {2}]", result.Key, result.Value.Key, result.Value.Value);
	}
	Console.WriteLine();

	Console.WriteLine("== Longest Nondecreasing Subsequence (LNDSS) ==");
	var testLnds = new List<IList<int>>
	{
		new List<int>(),
		new List<int>{ 0 },
		new List<int>{ 0, 2 },
		new List<int>{ 2, 0 },
		new List<int>{ 2, 0, 5 },
		new List<int>{ 0, 2, 5 },
		new List<int>{ 5, 2, 0 },
		new List<int>{ 2, 0, 9, 3, 9, 1, 9, 5, 7, 7, 8 },
		new List<int>{ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 }
	};
	count = 1;
	foreach(var test in testLnds)
	{
		Console.WriteLine("Test " + (count++).ToString().PadLeft(2, '0') + ": [" + string.Join(", ", test) + "]");
		var result = solutions.Lndss(test);
		Console.WriteLine("Result: {0}", result.Count > 0 ? "[" + string.Join(", ", result) + "]" : "-");
		Console.WriteLine();
	}
	Console.WriteLine();*/

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
			auto lcss = Combinatorics::Lcss(test.first, test.second);
			auto css = Combinatorics::Css(test.first, test.second);

			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << ++i << ":" << endl;
			cout << "  (" << test.first.size() << "): " << test.first << endl;
			cout << "  (" << test.second.size() << "): " << test.second << endl;
			cout << "  LCSS  (" << lcss.size() << "): " << (lcss.size() > 0 ? lcss : "-") << endl;
			cout << "  Set X (" << css.size() << "): " << (css.size() > 0 ? css : "-") << endl;
		}
	}
	cout << endl;

	cout << "- Subarray Sum (SSA) -" << endl;
	{
		vector<vector<int>> testSsa =
		{
			{ 7, 3, 5, 2, 10, 5, 0, 15, 0, 0, 12, 3 },
			{ 1, 2, 2, 0, 5, -5, 0, 8, -8, 1, 7, -3 }
		};
		for (auto&& test : testSsa)
		{
			cout << "Input: ";
			for (auto it = test.cbegin(); it != test.cend(); ++it)
			{
				cout << *it << (it != test.cend() - 1 ? ", " : "");
			}
			cout << endl << endl;

			vector<long long> sums = { 8, 15, 17, 25 };
			for (unsigned i = 0; i < sums.size(); ++i)
			{
				long long sum = sums[i];
				cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i + 1 << ": sum = " << sum << endl;
				auto found = Combinatorics::HasSsa(test, sum);
				cout << "  Any subarray: [" << found.first << ", " << found.second << "]" << endl;
				auto matches = Combinatorics::Ssa(test, sum);
				cout << "  All subarrays" << (!matches.empty() ? " (" + to_string(matches.size()) + "): " : ": not found");

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

					cout << "  Longest: [";
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
			cout << "--" << endl;
		}
		
	}
	cout << endl;

	cout << "- Custom SSS: two- and three-sum -" << endl;
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
			cout << "  Any 2-combination found: " << (found2 ? "true" : "false") << endl;
			cout << "  Any 3-combination found: " << (found3 ? "true" : "false") << endl;
			vector<vector<int>> matches;
			Combinatorics::ThreeSumCombinations(vi3, sum, matches);
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
			auto found = Combinatorics::HasThreeSum(vi4, sum);
			if (!found)
			{
				cout << sum << (sum < high - 1 ? ", " : "");
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Subset Sum (SSS) -" << endl;
	{
		vector<vector<unsigned>> testSss =
		{
			{ 1, 2, 5, 7, 13 },
			{ 13, 0, 2, 1, 0, 7, 5 },
			//{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 }
		};
		int count = 0, low = 0, high = 30;

		for (auto&& test : testSss)
		{
			cout << "Input: ";
			for (auto it = test.cbegin(); it != test.cend(); ++it)
			{
				cout << *it << (it != test.cend() - 1 ? ", " : "");
			}
			cout << endl;
			
			cout << "Non-matching SSS in range: [" << low << "; " << high << "]" << endl;
			count = 0;
			cout << "BF: ";
			for (int sum = low; sum < high; ++sum)
			{
				auto found = Combinatorics::HasSubsetSumR(test, test.size(), sum);
				if (!found)
				{
					cout << (count++ > 0 ? ", " : "") << sum;
				}
			}
			cout << endl;
			count = 0;
			cout << "DP: ";
			for (int sum = low; sum < high; ++sum)
			{
				auto found = Combinatorics::HasSubsetSum(test, sum);
				if (!found)
				{
					cout << (count++ > 0 ? ", " : "") << sum;
				}
			}
			cout << endl;

			cout << "All SSS in range: [" << low << "; " << high << "]" << endl;
			cout << "DP: ";
			for (int sum = low; sum < high; ++sum)
			{
				auto sss = Combinatorics::Sss(test, sum);
				cout << sum << ": ";
				if (!sss.empty())
				{
					cout << "[";
					for (auto it = sss.cbegin(); it != sss.cend(); ++it)
					{
						cout << *it << (it != sss.cend() - 1 ? ", " : "");
					}
					cout << "]";
				}
				else
				{
					cout << "-";
				}
				cout << (sum < high - 1 ? ", " : "");
				
			}
			cout << endl << "--" << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

