#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <deque>
#include <map>

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
};

