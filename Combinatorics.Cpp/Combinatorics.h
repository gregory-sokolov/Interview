#pragma once

#include <vector>
#include <deque>
#include <algorithm>

///
/// Combinatorial Problems
///
class Combinatorics
{
public:
	/// EPI 6.10. Permuting the elements of an array
	/// Generates all permutations P(n) recursively.
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

	/// EPI 15.5.1. Max sum subarray problem (MSS).
	/// Finds max sum subarray using modified Kadane's algorithm (dynamic programming).
	/// Handles positive and negative numbers.
	static std::pair<long long, std::pair<unsigned, unsigned>> MaxSumSubarray(const std::vector<int>& input)
	{
		long long max = input[0], current = input[0];
		unsigned start = 0, end = 0, max_start = 0, max_end = 0;
		for (unsigned i = 0; i < input.size(); ++i)
		{
			if (input[i] > current + input[i])
			{
				start = end = i;
				current = input[i];
			}
			else
			{
				end = i;
				current = current + input[i];
			}

			if (current > max)
			{
				max = current;
				max_start = start;
				max_end = end;
			}
		}

		return std::make_pair(max, std::make_pair(max_start, max_end));
	}

	/// EPI 15.7. Longest sum subarray problem (LSS)
	/// Finds all subarrays whose sum equals or less than the target number.
	/// Moves the "window" with the sum through the entire array, removing only leading items if sum exceeds target.
	/// When encountered zeroes, runs a sort of "greedy" search to generate all required subsequences.
	/// Time: O(n)
	static void LongestSumSubarray(const std::vector<int>& input, long long target,
		std::vector<std::deque<std::pair<unsigned, int>>>& results)
	{
		std::deque<std::pair<unsigned, int>> dq;
		long long sum = LLONG_MIN;
		for (unsigned i = 0; i < input.size() || sum >= target;)
		{
			if (sum < target)
			{
				sum = sum == LLONG_MIN ? input[i] : sum + input[i];
				dq.push_back(std::make_pair(i, input[i]));
				++i;
			}
			else
			{
				if (sum == target)
				{
					results.push_back(dq);
					for (unsigned j = i; j < input.size() && input[j] == 0; ++j)
					{
						auto dq0 = results.back();
						dq0.push_back(std::make_pair(j, input[j]));
						results.push_back(dq0);
					}
				}

				int front = dq.front().second;
				dq.pop_front();
				sum = !dq.empty() ? sum - front : LLONG_MIN;
			}
		}
	}

	/// Returns true if an input vector contains any 3 elements that sums to given value.
	/// Based on "greedy" algorithm from EPI, that uses solution of fast 2-sum search in O(n).
	/// Time: O(n*log(n)) + O(n^2) = O(n^2), space: O(1)
	static bool HasThreeSum(std::vector<int>& input, const int sum)
	{
		std::sort(input.begin(), input.end());
		for (unsigned i = 0; i < input.size(); ++i)
		{
			int sum2 = sum - input[i];
			for (unsigned j = 0, k = input.size() - 1; j < k;)
			{
				if (j == i || input[j] + input[k] < sum2)
				{
					++j;
				}
				else if (k == i || input[j] + input[k] > sum2)
				{
					--k;
				}
				else
				{
					return true;
				}
			}
		}

		return false;
	}

	/// Return all combinations of any 3 elements of an array that sum to given value.
	/// Brute-force generation of all combinations, C(n/k) - binomial coefficients.
	/// Time: O(n^3), space: O(1)
	static void ThreeSumCombinations(const std::vector<int>& input, const int sum,
		std::vector<std::vector<int>>& results)
	{
		std::vector<int> items(3);
		unsigned n = input.size();
		for (unsigned i = 0; i < n - 2; ++i)
		{
			items[0] = input[i];
			for (unsigned j = i + 1; j < n - 1; ++j)
			{
				items[1] = input[j];
				for (unsigned k = j + 1; k < n; ++k)
				{
					items[2] = input[k];
					if (items[0] + items[1] + items[2] == sum)
					{
						std::vector<int> triple = { (int)i, items[0], (int)j, items[1], (int)k, items[2] };
						results.push_back(triple);
					}
				}
			}
		}
	}
};

