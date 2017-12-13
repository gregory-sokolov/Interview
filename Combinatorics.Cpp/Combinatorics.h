#pragma once

#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>

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

	/// EPI 15.5.1. Max sum subarray problem (MSSA).
	/// Finds max sum subarray using modified Kadane's algorithm (dynamic programming).
	/// Handles positive and negative numbers.
	static std::pair<long long, std::pair<unsigned, unsigned>> Mssa(const std::vector<int>& input)
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

	/// EPI 15.7. Longest sum subarray problem (LSSA)
	/// Finds all subarrays whose sum equals or less than the target number.
	/// Moves the "window" with the sum through the entire array, removing only leading items if sum exceeds target.
	/// When encountering zeroes, runs a sort of "greedy" search to generate all required subsequences.
	/// Time: O(n)
	static void Lssa(const std::vector<int>& input, long long target,
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

	/// Yandex. 2-sum problem
	/// Returns true if an input vector contains any 2 elements that sum up to the given value.
	/// Places all the vector to the hash table for fast further searches.
	/// Iterates through the array, calculates the diff beetween sum and a[i] and finds it in the hash.
	/// If such diff exists, we have found the target pair of numbers.
	/// Time: O(n), space: O(n)
	static bool HasTwoSum(const std::vector<int>& a, const int sum)
	{
		bool result = false;
		std::unordered_set<int> hash(a.cbegin(), a.cend());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int d = sum - a[i];
			auto found = hash.find(d);
			if (found != hash.cend())
			{
				result = true;
				break;
			}
		}

		return result;
	}

	/// Returns true if an input vector contains any 3 elements that sum up to the given value.
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

	/// EPI 15.5.3. Longest Common Subsequence (LCSS).
	/// Returns LCSS of two strings with lengths m and n.
	/// Classical DP algorithm based on tabular memoization, where we build the matrix of matches.
	/// If there is no match, the maximum of the previous-top and previous-left elements is used.
	/// Time: O(m*n), space: O(n) for matrix
	static std::string Lcss(std::string s1, std::string s2)
	{
		if (s1.size() == 0 || s2.size() == 0)
		{
			return "";
		}

		vector<vector<unsigned>> M(s1.size() + 1, vector<unsigned>(s2.size() + 1));
		for (unsigned i = 1; i <= s1.size(); ++i)
		{
			for (unsigned j = 1; j <= s2.size(); ++j)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					M[i][j] = 1 + M[i - 1][j - 1];
				}
				else
				{
					M[i][j] = std::max(M[i - 1][j], M[i][j - 1]);
				}
			}
		}

		std::string result;
		for (unsigned i = s1.size(), j = s2.size(); i > 0 && j > 0;)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				result = s1[i - 1] + result;
				--i; --j;
			}
			else if (M[i - 1][j] > M[i][j - 1])
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
};

