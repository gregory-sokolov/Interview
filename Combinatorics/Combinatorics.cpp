/// 
/// Combinatorial Problems
///

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>

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
				input += to_string(*it) + (it != testMssa[i].cend() - 1 ? ", " : "");
			}
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i << ": [" << input << "]" << endl;
			auto result = Combinatorics::Mssa(testMssa[i]);
			cout << "    " << result.first << " [" << result.second.first << ", " << result.second.second << "]" << endl;
		}
	}
	cout << endl;

	cout << "- Max Product Subarray (MPSA) -" << endl;
	{
		vector<vector<int>> testMpsa =
		{
			{},
			{ 2 },
			{ 2, -2 },
			{ 2, 3, 5, 4, 3, 1 },
			{ -2, -3, -5, -4, -3, -1 },
			{ 2, 3, 5, 0, 7, 5, 1 },
			{ -1, -2, -3, 4, 0, -5, 2 },
			{ -10, 0, -20, 0, -30, 0, 0, -40 }
		};
		for (unsigned i = 0; i < testMpsa.size(); ++i)
		{
			string input;
			for (auto it = testMpsa[i].cbegin(); it != testMpsa[i].cend(); ++it)
			{
				input += to_string(*it) + (it != testMpsa[i].cend() - 1 ? ", " : "");
			}
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i << ": [" << input << "]" << endl;
			auto result = Combinatorics::Mpsa(testMpsa[i]);
			cout << "    " << result.first << " [" << result.second.first << ", " << result.second.second << "]" << endl;
		}
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

	cout << "- Longest Nondecreasing Subsequence (LNDSS) -" << endl;
	{
		vector<vector<int>> testLndss =
		{
			{},
			{ 0 },
			{ 0, 2 },
			{ 2, 0 },
			{ 2, 0, 5 },
			{ 0, 2, 5 },
			{ 5, 2, 0 },
			{ 2, 0, 9, 3, 9, 1, 9, 5, 7, 7, 8 },
			{ 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 }
		};
		for (unsigned i = 0; i < testLndss.size(); ++i)
		{
			string input;
			for (auto it = testLndss[i].cbegin(); it != testLndss[i].cend(); ++it)
			{
				input += to_string(*it) + (it != testLndss[i].end() - 1 ? ", " : "");
			}
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i << ": [" << input << "]" << endl;
			auto result = Combinatorics::Lndss(testLndss[i]);
			string output;
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				output += to_string(*it) + (it != result.cend() - 1 ? ", " : "");
			}
			cout << "    " << (!output.empty() ? "(" + to_string(result.size()) + "): " + output : "-") << endl;
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
			{ 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 }
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

	cout << "- Knapsack Problem (KS) -" << endl;
	{
		vector<pair<vector<pair<unsigned, unsigned>>, unsigned>> testKs01 =
		{
			make_pair(vector<pair<unsigned, unsigned>>(), 0),
			make_pair(vector<pair<unsigned, unsigned>>(), 10),
			make_pair(vector<pair<unsigned, unsigned>>({ make_pair(4, 3) }), 0),
			make_pair(vector<pair<unsigned, unsigned>>({ make_pair(3, 4) }), 10),
			make_pair(vector<pair<unsigned, unsigned>>(
			{ 
				make_pair(4, 3), make_pair(2, 1), make_pair(5, 7), make_pair(3, 3), make_pair(7, 9), make_pair(10, 12), make_pair(6, 5)
			}), 16),
			make_pair(vector<pair<unsigned, unsigned>>(
			{
				make_pair(57, 83), make_pair(95, 84), make_pair(13, 85), make_pair(29, 76), make_pair(1, 13), make_pair(99, 87), make_pair(34, 2),
				make_pair(77, 23), make_pair(61, 33), make_pair(23, 82), make_pair(24, 79), make_pair(70, 100), make_pair(73, 88), make_pair(88, 85),
				make_pair(33, 91), make_pair(61, 78), make_pair(43, 83), make_pair(5, 44), make_pair(41, 4), make_pair(63, 50), make_pair(8, 11),
				make_pair(67, 68), make_pair(20, 90), make_pair(72, 88), make_pair(98, 73), make_pair(59, 59), make_pair(46, 46), make_pair(58, 16),
				make_pair(64, 7), make_pair(94, 35), make_pair(97, 76), make_pair(70, 31), make_pair(46, 40), make_pair(81, 49), make_pair(42, 65),
				make_pair(7, 2), make_pair(1, 18), make_pair(52, 47), make_pair(20, 55), make_pair(54, 38), make_pair(81, 81), make_pair(3, 58),
				make_pair(73, 86), make_pair(78, 77), make_pair(81, 96), make_pair(11, 94), make_pair(41, 82), make_pair(45, 92), make_pair(18, 10),
				make_pair(94, 86), make_pair(24, 54), make_pair(82, 49), make_pair(9, 65), make_pair(19, 44), make_pair(59, 77), make_pair(48, 22),
				make_pair(2, 81), make_pair(72, 52)
			}), 72)
		};

		vector<pair<string, function<std::vector<std::pair<unsigned, unsigned>>(std::vector<std::pair<unsigned, unsigned>>&, unsigned)>>> algKs(
		{ 
			{ "-- Knapsack 0-1 (KS01) --", Combinatorics::Knapsack01 },
			{ "-- Knapsack Unbounded (KSU) --", Combinatorics::KnapsackU } 
		});
		for (const auto& alg : algKs)
		{
			cout << alg.first << endl;
			for (unsigned i = 0; i < testKs01.size(); ++i)
			{
				auto test = testKs01[i];
				cout << "Input " << setiosflags(ios::right) << setw(2) << setfill('0') << i + 1 <<
					": w = " << test.second << ", [" << test.first.size() << "]: " << (test.first.size() > 0 ? "" : "{}");
				for (auto it = test.first.cbegin(); it != test.first.cend(); ++it)
				{
					cout << "{" << it->first << "," << it->second << "}" << (it != test.first.cend() - 1 ? ", " : "");
				}
				cout << endl;
				auto results = alg.second(test.first, test.second);
				unsigned weight = std::accumulate(results.cbegin(), results.cend(), 0,
					[](unsigned s, const pair<unsigned, unsigned> p) { return s + p.first; }),
					value = std::accumulate(results.cbegin(), results.cend(), 0,
						[](unsigned s, const pair<unsigned, unsigned> p) { return s + p.second; });
				cout << "Result: w = " << weight << ", v = " << value << (results.size() > 0 ? ", [" + to_string(results.size()) + "] : " : "");
				for (auto it = results.cbegin(); it != results.cend(); ++it)
				{
					cout << "{" << it->first << "," << it->second << "}" << (it != results.cend() - 1 ? ", " : "");
				}
				cout << endl;
			}
		}
		
	}
	cout << endl;

	cout << "- Scheduling Tutors (GISMP) -" << endl;
	{
		vector<pair<double, double>> schedule =
		{
			{ 9, 9.5 }, { 9.3, 9.8 }, { 9.5, 10.0 }, { 9.8, 10.3 }, { 9.9, 10.4 }, { 10.0, 10.5 }, { 10.2, 10.7 }, { 10.5, 11.0 },
			{ 10.5, 11.0 }, { 10.8, 11.3 },  { 11.5, 12.0 }
		};
		auto tutors = Combinatorics::ScheduleTutors(schedule, 2.0);
		cout << "Max tutors: " << tutors.size() << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

