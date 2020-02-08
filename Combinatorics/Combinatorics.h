#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <algorithm>

///
/// Combinatorial Problems
///
class Combinatorics
{
public:
	/// EPI 6.10, Leetcode 46. Generating all permutations of array's elements
	/// Generates all permutations P(n) recursively.
	/// Uses vector and start index in recursion instead of C-style array pointer.
	/// Time: O(n!), space: O(1) - in-place swap
	static std::vector<std::vector<int>> Permutations(std::vector<int>& numbers)
	{
		std::vector<std::vector<int>> results;
		if (numbers.size() == 1)
		{
			results.push_back(numbers);
		}
		else if (numbers.size() == 2)
		{
			results.push_back({ numbers[0], numbers[1] });
			results.push_back({ numbers[1], numbers[0] });
		}
		else if (numbers.size() > 2)
		{
			PermuteR(numbers, 0, results);
		}

		return results;
	}
	private: static void PermuteR(std::vector<int>& a, unsigned from, std::vector<std::vector<int>>& results)
	{
		if (from == a.size())
		{
			results.push_back(std::vector<int>(a));
		}
		else
		{
			for (unsigned i = from; i < a.size(); ++i)
			{
				std::swap(a[from], a[i]);
				PermuteR(a, from + 1, results);
				std::swap(a[i], a[from]);
			}
		}
	}

	/// EPI 6.22. Generating phone pad mnemonic combinations (Amazon Question)
	/// Generates all possible combinations out of standard phone keyboard layout numbers.
	/// Initializes the resulting output sequence with the letters from the first digit.
	/// Then reuses already generated sequence to append one more letter to each already existing combination,
	/// removing the head from the beginning and pushing new combinations to the end of the sequence.
	/// Finally, the sequence contains all required combinations.
	/// We use std::deque here as it is suitable for removing from the top and adding to the end of the collection. 
	/// Time: O(n), space: O(k*n)
	public: static std::deque<std::string> PhoneMnemonics(const std::vector<unsigned>& numbers, std::map<unsigned, std::string>& mapping)
	{
		if (numbers.empty() || mapping.empty())
		{
			return std::deque<std::string>();
		}

		std::deque<std::string> results;
		for (const auto& ci : mapping[numbers[0]])
		{
			results.push_back(std::string(1, ci));
		}
		for (unsigned i = 1; i < numbers.size(); ++i)
		{
			std::string lts = mapping[numbers[i]];
			unsigned size = results.size();
			for (unsigned j = 0; j < size; ++j)
			{
				std::string head = results.front();
				results.pop_front();
				for (unsigned k = 0; k < lts.size(); ++k)
				{
					results.push_back(head + std::string(1, lts[k]));
				}
			}
		}

		return results;
	}

	/// Leetcode 22. Generating all valid parenthesis combinations
	/// One of approaches is to use backtracking: add parenthesis '(' or ')' only when it remains a valid sequence.
	/// We can do this by keeping track of the number of opening and closing brackets we have placed so far.
	/// Each valid sequence has at most n steps during the backtracking procedure. 
	/// Complexity turns out to be the n-th Catalan number (1/(n + 1))|(2^n, n).
	/// Time: O(4^n/sqrt(n)), space: O(4^n/sqrt(n)) + O(n) (recursion + output)
	public:	static std::vector<std::string> ParenthesisCombinations(unsigned n)
	{
		std::vector<std::string> result;
		if (n > 0) 
		{
			std::string combin;
			ParenthesisR(n, n, combin, result);
		}

		return result;
	}
	private: static void ParenthesisR(unsigned open, unsigned closed, std::string combin, std::vector<std::string>& result)
	{
		if (open == 0 && closed == 0)
		{
			result.push_back(combin);
		}
		else
		{
			if (open > 0)
			{
				ParenthesisR(open - 1, closed, combin + "(", result);
			}
			if (closed > open)
			{
				ParenthesisR(open, closed - 1, combin + ")", result);
			}
		}
	}

	/// Leetcode 70. Ways of climbing a staircase
	/// Generates all possible distinct combinations of 1- and 2-stair steps to get to the top of an n-stair staircase.
	/// Uses recursive solution with trying as much as possible of 1-stair steps and only then adds 2-stair steps.
	/// Time: O(2^n), space: O(2^n)
	public:	static std::vector<std::deque<unsigned>> StairCombinations(unsigned n)
	{
		std::vector<std::deque<unsigned>> results;
		std::deque<unsigned> current;
		StairsR(0, n, current, results);

		return results;
	}
	private: static void StairsR(unsigned i, unsigned n, std::deque<unsigned>& current, std::vector<std::deque<unsigned>>& results)
	{
		if (i < n)
		{
			current.push_back(1);
			StairsR(i + 1, n, current, results);
			current.pop_back();

			current.push_back(2);
			StairsR(i + 2, n, current, results);
			current.pop_back();
		}
		else if (i == n)
		{
			results.push_back(current);
		}
	}

	/// Combination count only, recursive solution. 
	/// Time: O(2^n), space: O(2^n)
	public:	static int StairCombinationsR(unsigned n)
	{
		return n > 0 ? StairsR(0, n) : 0;
	}
	private: static unsigned StairsR(unsigned i, unsigned n)
	{
		unsigned result = 0;
		if (i < n)
		{
			result += StairsR(i + 1, n);
			result += StairsR(i + 2, n);
		}
		else if (i == n)
		{
			result = 1;
		}

		return result;
	}

	/// Combination count: DP solution 
	/// Time: O(n), space: O(n)
	public:	static unsigned StairCombinationsDP(unsigned n)
	{
		if (n == 0) return 0;
		if (n == 1) return 1;

		vector<unsigned> dp(n + 1, 0);
		dp[1] = 1;
		dp[2] = 2;

		for (unsigned i = 3; i <= n; ++i)
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		}

		return dp[n];
	}

	/// Combination count: Fibonacci solution
	/// It turns out that each step generates Fibonacci sequence.
	/// The problem transforms to the generation of N-th Fibonacci number.
	/// Time: O(n), space: O(1)
	static unsigned long long StairCombinationsFb(unsigned n)
	{
		if (n == 0) return 0;
		if (n == 1) return 1;

		unsigned long long fb1 = 1, fb2 = 2, tmp = fb2;
		for (unsigned i = 3; i <= n; ++i)
		{
			tmp = fb2;
			fb2 += fb1;
			fb1 = tmp;
		}

		return fb2;
	}

	/// Leetcode 746. Min cost stair combination
	/// The same 1-2-step staircase problem (#70), but now each step has its own cost.
	/// Similar DP-Fibonacci solution is used to find the minimal cost of reaching the top of the staircase.
	/// At the end we take minimum of last two values.
	/// Time: O(n), space: O(1)
	static unsigned MinCostStairCombination(const std::vector<unsigned>& cost)
	{
		if (cost.size() == 0) return 0;
		if (cost.size() == 1) return 1;

		unsigned fb1 = cost[0], fb2 = cost[1], current = 0;
		for (unsigned i = 2; i < cost.size(); ++i)
		{
			current = cost[i] + std::min(fb1, fb2);
			fb1 = fb2;
			fb2 = current;
		}

		return min(fb1, fb2);
	}
};

