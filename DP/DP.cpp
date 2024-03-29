/// 
/// Dynamic Programming Problems
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

#include "DP.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Dynamic Programming ==" << endl << endl;

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
			auto result = DP::Mssa(testMssa[i]);
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
			auto result = DP::Mpsa(testMpsa[i]);
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
			auto lcss = DP::Lcss(test.first, test.second);
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << ++i << ":" << endl;
			cout << "  (" << test.first.size() << "): " << test.first << endl;
			cout << "  (" << test.second.size() << "): " << test.second << endl;
			cout << "  LCSS  (" << lcss.size() << "): " << (lcss.size() > 0 ? lcss : "-") << endl;
		}
	}
	cout << endl;

	cout << "- Levenshtein distance (LD) -" << endl;
	{
		vector<pair<string, string>> testLD =
		{
			{ "", "" },
			{ "", "a" },
			{ "a", "" },
			{ "aaa", "aaa" },
			{ "aabaa", "aacaa" },
			{ "abc", "defgh" },
			{ "intention", "execution" },
			{ "democrat", "republican" },
			{ "exponential", "polynomial" },
			{ "subexponential", "subpolynomial" }
		};
		for (unsigned i = 0; i < testLD.size(); ++i)
		{
			auto input = testLD[i];
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i + 1 << ": " << setfill('\0') <<
				input.first << " -> " << input.second << ": ";
			auto result = DP::LevenshteinDistance(input.first, input.second);
			cout << "ld = " << result.first << endl;
			if (result.second.size() > 0)
			{
				string src, dst, edit;
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(src),
					[](const std::pair<char, char> x) { return !x.first && x.second ? ' ' : x.first; });
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(dst),
					[](const std::pair<char, char> x) { return x.first && !x.second ? ' ' : x.second; });
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(edit),
					[](const std::pair<char, char> x)
				{
					return x.first && !x.second ? 'D' : (!x.first && x.second ? 'I' : (x.first != x.second ? 'R' : 'M'));
				});
				if (!edit.empty())
				{
					edit.erase(edit.cend() - 1);
				} 

				cout << src << endl;
				cout << dst << endl;
				cout << edit << endl;
			}
			cout << "--" << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Word breaking -" << endl;
	{
		unordered_set<string> dictionary =
		{
			"no", "in", "is", "it", "ack", "now", "led", "eve", "owl", "win",
			"know", "even", "lack", "edge", "here", "tick",
			"event", "noise", "ledge", "seven", "turel", "where",
			"venture", "heretic", "acknowledge"
		};
		vector<string> testWB =
		{
			"noiseventurelacknowledge", "nowhereticknowin",
			"abcdefghijk", ""
		};
		for (auto si = testWB.begin(); si != testWB.end(); ++si)
		{
			cout << "Input: " << si->c_str() << endl;
			auto result1 = DP::BreakIntoWordsRB(si->c_str(), dictionary);
			cout << "Result 1: [";
			for (auto it = result1.cbegin(); it != result1.cend(); ++it)
			{
				cout << *it << (it != result1.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;

			auto result2 = DP::BreakIntoWordsDP(si->c_str(), dictionary);
			cout << "Result 2: [";
			for (auto it = result2.cbegin(); it != result2.cend(); ++it)
			{
				cout << *it << (it != result2.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
		}
		cout << endl;
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
			auto result = DP::Lndss(testLndss[i]);
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
				auto found = DP::HasSsa(test, sum);
				cout << "  Any subarray: [" << found.first << ", " << found.second << "]" << endl;
				auto matches = DP::Ssa(test, sum);
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
				auto found = DP::HasSubsetSumR(test, test.size(), sum);
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
				auto found = DP::HasSubsetSum(test, sum);
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
				auto sss = DP::Sss(test, sum);
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
			{ "-- Knapsack 0-1 (KS01) --", DP::Knapsack01 },
			{ "-- Knapsack Unbounded (KSU) --", DP::KnapsackU }
		});
		for (const auto& alg : algKs)
		{
			cout << endl << alg.first << endl;
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

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

