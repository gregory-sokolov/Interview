#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

///
/// Dynamic Programming Problems
///
class DP
{
public:
	/// EPI 15.5.1. Max sum subarray (MSSA).
	/// Returns subarray with maximum sum using Kadane's algorithm (Dynamic Programming (DP)).
	/// Kadane's algorithm is based on the fact: max_sum(i + 1) = max(max_sum(i), a[i]).
	/// We can start from trivial case with max_sum=a[0](0,0) and infer further sums using memoization in DP.
	/// Variables: tracking max sum (ts), overall max sum (ms) and related subarray indexes (mi, mj).
	/// Time: O(n), space: O(1)
	static std::pair<int, std::pair<int, int>> Mssa(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::make_pair(-1, std::make_pair(-1, -1));
		}

		int ts = a[0], ms = a[0];
		int ti = 0, mi = 0, mj = 0;
		for (unsigned i = 1; i < a.size(); ++i)
		{
			int sum = ts + a[i];
			if (a[i] > sum)
			{
				ts = a[i];
				ti = i;
			}
			else
			{
				ts = sum;
			}

			if (ts > ms)
			{
				ms = ts;
				mi = ti;
				mj = i;
			}
		}

		return std::make_pair(ms, std::make_pair(mi, mj));
	}

	/// EPI 15.5.2. Max product subarray (MPSA).
	/// Finds the subarray with maximum product in an array of positive, negative and zero values.
	/// The main idea is similar to MSSA: track and store maximums in DP style when interating.
	/// Both maximum and minimum products are tracked to handle transitions between positive and negative numbers.
	/// Swap them on negative number, since after the multiplication to a negative the extremums will change their places.
	/// Given in 2 versions: the original one for a better understanding and the full one with subarray index range.
	/// Range searching is based on rolling back each maximum candidate by dividing it consequently by previous array items.
	/// Time: O(n), space: O(1)
	static int MpsaOriginal(const std::vector<int>& a)
	{
		int pmax = a[0], pmin = a[0], result = a[0];
		for (unsigned i = 1; i < a.size(); ++i)
		{
			if (a[i] < 0)
			{
				std::swap(pmax, pmin);
			}

			pmax = std::max(a[i], pmax * a[i]);
			pmin = std::min(a[i], pmin * a[i]);

			result = std::max(result, pmax);
		}

		return result;
	}
	/// Version with subarray range
	static std::pair<int, std::pair<int, int>> Mpsa(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::make_pair(-1, std::make_pair(-1, -1));
		}

		int pmax = a[0], pmin = a[0], result = a[0];
		int left = 0, right = 0;
		for (unsigned i = 1; i < a.size(); ++i)
		{
			if (a[i] < 0)
			{
				std::swap(pmax, pmin);
			}

			pmax = std::max(a[i], pmax * a[i]);
			pmin = std::min(a[i], pmin * a[i]);

			if (pmax >= result)
			{
				result = pmax;

				right = i;
				left = right;
				for (int div = pmax; div != 1 && left >= 0 && a[left] != 0; --left)
				{
					div /= a[left];
				}
				++left;
			}
		}

		return std::make_pair(result, std::make_pair(left, right));
	}

	/// EPI 15.5.3. Longest Common Subsequence (LCSS).
	/// Returns LCSS of two strings with lengths m and n.
	/// Classical DP algorithm based on tabular memoization, where we build the matrix of matches.
	/// If there is no match, the maximum of the previous-top and previous-left elements is used.
	/// The second loop builds the resulting string by traversing the matrix.
	/// Time: O(m*n), space: O(n) for matrix
	static std::string Lcss(std::string s1, std::string s2)
	{
		if (s1.size() == 0 || s2.size() == 0)
		{
			return std::string();
		}

		std::vector<std::vector<int>> mx(s1.size() + 1, std::vector<int>(s2.size() + 1));
		for (unsigned i = 1; i <= s1.size(); ++i)
		{
			for (unsigned j = 1; j <= s2.size(); ++j)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					mx[i][j] = 1 + mx[i - 1][j - 1];
				}
				else
				{
					mx[i][j] = std::max(mx[i - 1][j], mx[i][j - 1]);
				}
			}
		}

		std::string result;
		for (int i = s1.size(), j = s2.size(); i > 0 && j > 0;)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				result = s1[i - 1] + result;
				--i; --j;
			}
			else if (mx[i - 1][j] > mx[i][j - 1])
			{
				--i;
			}
			else
			{
				--j;
			}
		}

		return result;
	}

	/// EPI 15.6. Longest nondecreasing subsequence (LNDSS).
	/// Finds longest nondecreasing subsequence in an array of integers.
	/// The resulting sequence should not necessarily be a subarray.
	/// Builds active lists with possible sequences, using binary search to find the best ending candidate.
	/// Cases: 
	/// - [New] Smaller than all known endings. Start a new list with the single element a[i].
	/// - [Clone + Extend] Greater than all known endings. Clone the largest list and extend it by a[i].
	/// - [Find + Replace] In between of known endings.
	///   Find a larger list with the ending greater than a[i] using binary search. Locate the previous list, clone and extend it by a[i].
	///   Replace the larger list with the previous list. It discards all less perpective lists.
	/// To find the resulting sequence, O(n) space is required to store all intermediate sequences (mapped to endings).
	/// To find the length only, it's enough just to keep the array of endings.
	/// Time: O(n*log(n)), space: O(n)
	static const std::vector<int> Lndss(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::vector<int>();
		}

		std::deque<int> endings = { a[0] };
		std::deque<std::deque<int>> lists = { { a[0] } };
		//Combinatorics::LogLists(0, a[0], lists);

		for (unsigned i = 1; i < a.size(); ++i)
		{
			std::deque<int> first = lists[0], last = lists[lists.size() - 1];
			if (a[i] < first[first.size() - 1])
			{
				endings.push_front(a[i]);
				std::deque<int> next = { a[i] };
				lists.push_front(next);
			}
			else if (a[i] >= last[last.size() - 1])
			{
				endings.push_back(a[i]);
				std::deque<int> clone(last.cbegin(), last.cend());
				clone.push_back(a[i]);
				lists.push_back(clone);
			}
			else
			{
				auto found = std::upper_bound(endings.cbegin(), endings.cend(), a[i]);
				unsigned index = found - endings.cbegin();
				endings[index] = a[i];

				std::deque<int> previous(lists[index - 1].cbegin(), lists[index - 1].cend());
				previous.push_back(a[i]);
				lists[index] = previous;
			}

			//Combinatorics::LogLists(i, a[i], lists);
		}

		std::vector<int> result((lists.cend() - 1)->cbegin(), (lists.cend() - 1)->cend());
		return result;
	}

	/// LNDSS log helper
	static void LogLists(const int i, const int ai, const std::deque<std::deque<int>>& lists)
	{
		std::cout << std::setiosflags(std::ios::right) << std::setw(2) << std::setfill('0') << i << ": " << ai << std::endl;
		for (auto lit = lists.cbegin(); lit != lists.end(); ++lit)
		{
			std::cout << "  ";
			for (auto it = lit->cbegin(); it != lit->end(); ++it)
			{
				std::cout << *it << (it != lit->end() - 1 ? "-" : "");
			}
			std::cout << std::endl;
		}
	}

	/// EPI 15.11. Levenshtein distance (edit distance). 
	/// Returns the number of edit operations required to transform one string s1 to another s2.
	/// Types of standard operations: 
	/// I - insert, D - delete, R - replace, M - match
	/// Based on standard DP algorithm with tabular memoization (similar to EPI 15.5.3 LCSS).
	/// Edit prescription (IDRM transformation sequence) is inferred by traversing the matrix bottom up,
	/// for each cell we find the minimum from the diagonal/left/top elements,
	/// where diagonal - R or M, left - insert from s2, top - delete from s1 (Wagner-Fisher algorithm).
	/// Time: O(m*n), space: O(m*n)
	/// Returns: the distance and the edit prescription
	static std::pair<unsigned, std::vector<std::pair<char, char>>>
		LevenshteinDistance(const std::string& s1, const std::string& s2)
	{
		// Input checks
		if (s1.empty() && s2.empty() || s1 == s2)
		{
			return std::make_pair(0, std::vector<std::pair<char, char>>());
		}
		else if (s1.empty() && !s2.empty())
		{
			return std::make_pair(s2.size(), std::vector<std::pair<char, char>>());
		}
		else if (!s1.empty() && s2.empty())
		{
			return std::make_pair(s1.size(), std::vector<std::pair<char, char>>());
		}

		// Initialization
		unsigned m = s1.size(), n = s2.size();
		std::vector<std::vector<unsigned>> mx(m + 1, std::vector<unsigned>(n + 1));
		for (unsigned i = 0; i <= m; ++i)
		{
			mx[i][0] = i;
		}
		for (unsigned i = 0; i <= n; ++i)
		{
			mx[0][i] = i;
		}

		// The DP algorithm
		for (unsigned i = 1; i <= m; ++i)
		{
			for (unsigned j = 1; j <= n; ++j)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					mx[i][j] = mx[i - 1][j - 1];
				}
				else
				{
					mx[i][j] = 1 + std::min(std::min(mx[i][j - 1], mx[i - 1][j]), mx[i - 1][j - 1]);
				}
			}
		}

		// TODO: debug tracing
		LogResults(mx);

		// Edit prescription: Wagner-Fisher algorithm
		std::vector<std::pair<char, char>> result;
		for (int i = m, j = n; i >= 0 || j >= 0;)
		{
			unsigned current = mx[i][j],
				diag = i > 0 && j > 0 ? mx[i - 1][j - 1] : std::numeric_limits<unsigned>::max(),
				left = j > 0 ? mx[i][j - 1] : std::numeric_limits<unsigned>::max(),
				top = i > 0 ? mx[i - 1][j] : std::numeric_limits<unsigned>::max(),
				min = std::min(diag, std::min(left, top));
			if (min == diag)
			{
				result.push_back(std::make_pair(s1[i], s2[j]));
				--i; --j;
			}
			else if (min == left)
			{
				result.push_back(std::make_pair('\0', s2[j]));
				--j;
			}
			else //if (min == top)
			{
				result.push_back(std::make_pair(s1[i], '\0'));
				--i;
			}
		}
		std::reverse(result.begin(), result.end());

		return std::make_pair(mx[m][n], result);
	}

	/// Log helper
	static void LogResults(const std::vector<std::vector<unsigned>>& mx)
	{
		if (mx.size() > 0 && mx[0].size() > 0)
		{
			std::cout << std::endl;
			for (unsigned i = 0; i < mx.size(); ++i)
			{
				for (unsigned j = 0; j < mx[0].size(); ++j)
				{
					std::cout << std::setiosflags(std::ios::right) << std::setw(3) << mx[i][j];
				}
				std::cout << std::endl;
			}
		}
	}

	/// EPI 15.12. Word breaking (bedbathandbeyond problem).
	/// Checks if the text is a consequent concatenation of words and returns that sequence.
	/// Non-DP searching algorithm with rollbacks and without memoization.
	/// Time: O(n^2), space: O(n)
	static std::vector<std::string> SplitByWords(const std::string& s, const std::set<std::string>& d)
	{
		std::deque<std::pair<std::string, unsigned>> words;
		std::string token;
		for (unsigned i = 0; i < s.size(); ++i)
		{
			token += s[i];
			if (d.find(token) != d.cend())
			{
				words.push_back(std::make_pair(token, i));
				token.clear();
			}

			if (i == s.size() - 1 && !token.empty() && !words.empty())
			{
				token = words.back().first;
				i = words.back().second;
				words.pop_back();
			}

			// TODO: debug tracing
			if (token.empty())
			{
				LogResults(words, i + 1);
			}
		}

		std::vector<std::string> results;
		std::transform(words.cbegin(), words.cend(), back_inserter(results),
			[](const std::pair<std::string, unsigned>& x) { return x.first; });
		return results;
	}

	/// Log helper
	static void LogResults(std::deque<std::pair<std::string, unsigned>> words, unsigned i)
	{
		std::cout << std::setiosflags(std::ios::right) << std::setw(2) << std::setfill('0') << i << ": [ ";
		for (auto it = words.cbegin(); it != words.cend(); ++it)
		{
			std::cout << it->first << (it->first != words.crbegin()->first ? ", " : "");
		}
		std::cout << " ]" << std::endl;
	}

	/// EPI 15.7.1. Subarray sum (SSA)
	/// Finds any subarray whose sum equals to the target number.
	/// Time: O(n), space: O(n)
	static std::pair<int, int> HasSsa(const std::vector<int>& a, const long long sum)
	{
		std::pair<int, int> result = std::make_pair(-1, -1);

		long long ts = 0;
		std::unordered_map<long long, unsigned> ht;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			ts += a[i];
			if (ts == sum)
			{
				result = std::make_pair(0, i);
				break;
			}

			auto found = ht.find(ts - sum);
			if (found != ht.cend())
			{
				result = std::make_pair(found->second, i);
				break;
			}
			ht[ts] = i;
		}

		return result;
	}

	/// EPI 15.7.2. Subarray sum (SSA)
	/// Finds all subarrays whose sum equals or less than the target number.
	/// Handles both positive and negative numbers, array could be unsorted.
	/// Moves the "window" with the sum through the entire array, removing only leading items if sum exceeds target.
	/// When encounters zeroes, runs a sort of "greedy" search to generate all required subsequences.
	/// Time: O(n), space: O(n)
	static std::vector<std::deque<std::pair<unsigned, int>>> Ssa(const std::vector<int>& a, const long long target)
	{
		std::vector<std::deque<std::pair<unsigned, int>>> results;
		std::deque<std::pair<unsigned, int>> dq;
		long long sum = LLONG_MIN;
		for (unsigned i = 0; i < a.size() || sum >= target; )
		{
			if (sum < target)
			{
				sum = sum == LLONG_MIN ? a[i] : sum + a[i];
				dq.push_back(std::make_pair(i, a[i]));
				++i;
			}
			else
			{
				if (sum == target)
				{
					results.push_back(dq);
					for (unsigned j = i; j < a.size() && a[j] == 0; ++j)
					{
						auto dq0 = results.back();
						dq0.push_back(std::make_pair(j, a[j]));
						results.push_back(dq0);
					}
				}

				int front = dq.front().second;
				dq.pop_front();
				sum = !dq.empty() ? sum - front : LLONG_MIN;
			}
		}

		return results;
	}

	/// EPI 17.0.1. Subset Sum (SSS)
	/// This is well-known NP-problem, could be solved with brute-force recursive implementation.
	/// The solution handles only positive numbers in the array.
	/// Time: O(2^n), space: O(1)
	static bool HasSubsetSumR(std::vector<unsigned>& a, unsigned n, unsigned sum)
	{
		if (sum == 0)
		{
			return true;
		}
		else if (n == 0 && sum != 0)
		{
			return false;
		}

		if (a[n - 1] > sum)
		{
			return DP::HasSubsetSumR(a, n - 1, sum);
		}
		else
		{
			return DP::HasSubsetSumR(a, n - 1, sum) || DP::HasSubsetSumR(a, n - 1, sum - a[n - 1]);
		}
	}

	/// EPI 17.0.2. Subset Sum (SSS)
	/// Returns true if there is any subset of the given array with the sum equal to the given number.
	/// This is well-known NP-problem, could be solved with DP and tabular memoization.
	/// The solution handles only positive numbers in the array.
	/// We build the boolean matrix of sum matches with a[i] as lines and sum[j] as columns, where each mx[i][j]:
	/// - copied from the cell in the previous row if sum[j] < a[i],
	/// - taken from the cell a[i]-steps backward in the previous row if sum[j] >= a[i] and mx value from previous row is false.
	/// The result is in mx[n][sum].
	/// Time: O(n*sum), space: O(n*sum)
	static bool HasSubsetSum(const std::vector<unsigned>& a, const unsigned sum)
	{
		std::vector<std::vector<bool>> mx(a.size() + 1, std::vector<bool>(sum + 1));
		for (unsigned i = 0; i < mx.size(); ++i)
		{
			mx[i][0] = true;
		}

		for (unsigned i = 1; i < mx.size(); ++i)
		{
			for (unsigned j = 1; j < mx[0].size(); ++j)
			{
				if (j < a[i - 1])
				{
					mx[i][j] = mx[i - 1][j];
				}
				else
				{
					mx[i][j] = mx[i - 1][j] || mx[i - 1][j - a[i - 1]];
				}
			}
		}

		return mx[mx.size() - 1][mx[0].size() - 1];
	}

	/// EPI 17.0.3. Subset Sum (SSS)
	/// Returns one existing subset that are equal to the target number.
	/// Uses the same DP solution with building matrix of matches.
	/// Handles only positive numbers in the array.
	/// Backtracks the resulting subset by unwinding the matrix:
	/// - if upper element m[i - 1][j] is 1, moves one row up (array item not included),
	/// - if upper element m[i - 1][j] is 0, copies a[i - 1] to the result and rolls back a[i - 1]-steps.
	/// Time: O(n*sum), space: O(n*sum)
	static std::vector<unsigned> Sss(const std::vector<unsigned>& a, const unsigned sum)
	{
		std::vector<std::vector<bool>> mx(a.size() + 1, std::vector<bool>(sum + 1));
		for (unsigned i = 0; i < mx.size(); ++i)
		{
			mx[i][0] = true;
		}

		for (unsigned i = 1; i < mx.size(); ++i)
		{
			for (unsigned j = 1; j < mx[0].size(); ++j)
			{
				if (j < a[i - 1])
				{
					mx[i][j] = mx[i - 1][j];
				}
				else
				{
					mx[i][j] = mx[i - 1][j] || mx[i - 1][j - a[i - 1]];
				}
			}
		}

		std::vector<unsigned> result;
		if (mx[mx.size() - 1][mx[0].size() - 1])
		{
			for (unsigned j = mx[0].size() - 1; j > 0; )
			{
				for (unsigned i = mx.size() - 1; i > 0; --i)
				{
					if (mx[i - 1][j] == 0)
					{
						result.push_back(a[i - 1]);
						j -= a[i - 1];
					}
				}
			}
		}
		return result;
	}

	/// EPI 17.2.1. 0-1 knapsack problem (KS01)
	/// Returns the maximum value of items that is possible to put into the knapsack.
	/// Classical DP problem, it is solved by tabular memoization.
	/// We build the matrix of values, where lines are asc-sorted item weights w[i]
	/// and columns are the discretized knapsack weigth w[j].
	/// On each step we make the decision of either to take the item or not, and select the one with the max value:
	/// - if no, then we inherit the value from the previous line, mx[i - 1][j]
	/// - if yes, then we take the current value v[i] plus the value of the knapsack with 'not-selected' item, mx[i - 1][j - w[j]]
	/// This 'not-selected' value has been previously calculated and is now reused, that is the essence of the DP memoization.
	/// The formula for each cell: 
	/// - i == j == 0: mx[i][j] = 0 (zero line/column)
	/// - i < w[j]: mx[i][j] = mx[i - 1][j] (if less, then previous),
	/// - i >= w[j]: mx[i][j] = max(mx[i - 1][j], mx[i - 1][j - w[j]] + v[i]) (if greater, then max(previous, not-selected+current))
	/// Backtracks the resulting items by unwinding the matrix from the end.
	/// If the value comes from the upper line, the current item is skipped and we move one line up.
	/// Otherwise, it is taken, we move one line up and backtrace back the line by the item weight.
	/// Time: O(n*weight), space: O(n*weight)
	static std::vector<std::pair<unsigned, unsigned>> Knapsack01(std::vector<std::pair<unsigned, unsigned>>& items, unsigned weight)
	{
		if (items.size() == 0 || weight == 0)
		{
			return std::vector<std::pair<unsigned, unsigned>>();
		}

		std::sort(items.begin(), items.end(),
			[](std::pair<unsigned, unsigned>& p1, std::pair<unsigned, unsigned>& p2) { return p1.first < p2.first; });
		std::vector<std::vector<unsigned>> mx(items.size() + 1, std::vector<unsigned>(weight + 1, 0));
		for (unsigned i = 1; i < mx.size(); ++i)
		{
			for (unsigned j = 1; j < mx[0].size(); ++j)
			{
				if (j < items[i - 1].first)
				{
					mx[i][j] = mx[i - 1][j];
				}
				else
				{
					mx[i][j] = std::max(mx[i - 1][j], mx[i - 1][j - items[i - 1].first] + items[i - 1].second);
				}
			}
		}

		std::vector<std::pair<unsigned, unsigned>> results;
		unsigned w = mx[0].size() - 1;
		for (unsigned i = mx.size() - 1; i > 0; --i)
		{
			if (mx[i][w] > 0 && mx[i][w] != mx[i - 1][w])
			{
				results.push_back(items[i - 1]);
				w -= items[i - 1].first;
			}
		}
		std::reverse(results.begin(), results.end());

		return results;
	}

	/// EPI 17.2.2. Unbounded knapsack problem (KSU)
	/// Returns the maximum value of items that is possible to put into the knapsack, item repetitions are allowed.
	/// The difference between KS01 is that for each discretized value w[i] we evaluate all available item weights/values,
	/// so the maximum i-th value ends up in the last matrix line. Thus we handle repetitions.
	/// In KS01, we iterated line by line; here, we iterate column by column, so the matrix indexation in loops is the opposite.
	/// The formula for each cell:
	/// - i == j == 0, mx[i][j] = 0
	/// - i < w[j]: mx[j][i] = mx[j - 1][i] (if less, then previous)
	/// - i >= w[j]: mx[j][i] = max(mx[j][i], mx[n - 1][i - w[j]] + v[j]) (if greater, then max(previous, not-selected+current))
	/// Result backtracking is similar to KS01, but after each selection we reset the search back to the last line and move up from the bottom.
	/// Time: O(n*weight), space: O(n*weight)
	static std::vector<std::pair<unsigned, unsigned>> KnapsackU(std::vector<std::pair<unsigned, unsigned>>& items, unsigned weight)
	{
		if (items.size() == 0 || weight == 0)
		{
			return std::vector<std::pair<unsigned, unsigned>>();
		}

		std::sort(items.begin(), items.end(),
			[](std::pair<unsigned, unsigned>& p1, std::pair<unsigned, unsigned>& p2) { return p1.first < p2.first; });
		std::vector<std::vector<unsigned>> mx(items.size() + 1, std::vector<unsigned>(weight + 1, 0));
		for (unsigned i = 1; i < mx[0].size(); ++i)
		{
			for (unsigned j = 1; j < mx.size(); ++j)
			{
				if (i >= items[j - 1].first)
				{
					mx[j][i] = std::max(mx[j - 1][i], mx[mx.size() - 1][i - items[j - 1].first] + items[j - 1].second);
				}
				else
				{
					mx[j][i] = mx[j - 1][i];
				}
			}
		}

		std::vector<std::pair<unsigned, unsigned>> results;
		for (unsigned i = mx[0].size() - 1; i > 0; --i)
		{
			for (unsigned j = mx.size() - 1; j > 0; --j)
			{
				if (mx[j][i] > 0 && mx[j][i] != mx[j - 1][i])
				{
					results.push_back(items[j - 1]);
					i -= items[j - 1].first - 1;
					break;
				}
			}
		}

		return results;
	}
};
