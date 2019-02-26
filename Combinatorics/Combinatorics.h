#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

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
};

