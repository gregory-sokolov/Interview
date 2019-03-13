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
	/// EPI 6.10. Permuting the elements of an array
	/// Generates all permutations P(n) recursively.
	/// Time: O(n!), space: O(1) - in-place swap
	template<typename T>
	static void PermutationsR(T* input, unsigned size, unsigned length, std::vector<std::vector<T>>& results)
	{
		if (input != NULL && size != 0)
		{
			if (size == 1)
			{
				vector<T> perm;
				std::copy(input - length + 1, input + 1, std::back_inserter<vector<T>>(perm));
				results.push_back(perm);
			}
			else
			{
				for (unsigned i = 0; i < size; ++i)
				{
					std::swap(input[0], input[i]);
					PermutationsR(input + 1, size - 1, length, results);
					std::swap(input[i], input[0]);
				}
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
	static std::deque<std::string> PhoneMnemonics(const std::vector<unsigned>& numbers, std::map<unsigned, std::string>& mapping)
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
};

