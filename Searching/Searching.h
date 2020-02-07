#pragma once

#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>

///
/// EPI. Chapter 11. Searching
///
class Searching
{
public:
	/// Find two maximums in an integer array (Yandex Question)
	/// Runs trivial linear search and returns two maximum values.
	/// Time: O(n), space: O(1)
	static std::pair<int, int> FindTwoMaximums(const std::vector<int>& source)
	{
		int max1 = INT_MIN, max2 = INT_MIN;
		for (auto&& vi : source)
		{
			if (vi > max2)
			{
				max1 = max2;
				max2 = vi;
			}
			else if (vi > max1)
			{
				max1 = vi;
			}
		}

		return std::make_pair(max1, max2);
	}

	/// EPI 11.17, Leetcode 136. Unique Number Among Duplicates
	/// Given a non-empty array of integers, every element appears twice except for one. Find that single one.
	/// Do it with linear runtime complexity. Try to implement it without using extra memory.
	/// Method 1: use hash table to store and check duplicates. Requires O(n) extra space.
	/// Method 2: XOR all elements. Based on fact, that x ^ 0 = x, x ^ x = 0, hence a1 ^ a2 ^ ... ^ an ^ x ^ an ^ ... ^ a1 = x.
	/// Time: O(n), space: O(1)
	static int UniqueNumber(std::vector<int>& a) {
		// Method 2: total XOR
		int x = 0;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			x ^= a[i];
		}

		return x;

		// Method 1: hash table
		/*
		unordered_set<int> ht;
		for (unsigned i = 0; i < nums.size(); ++i)
		{
			if (ht.find(nums[i]) == ht.cend())
			{
				ht.insert(nums[i]);
			}
			else
			{
				ht.erase(nums[i]);
			}
		}

		return !ht.empty() ? *(ht.cbegin()) : 0;
		*/
	}

	/// Find a number in an ascendingly sorted matrix m*n (Yandex Question)
	/// Binary Search. Scans all sorted rows with standard binary search.
	/// Time: O(m*log(n)), space: O(1)
	static std::pair<int, int> SearchSortedMatrixBs(const std::vector<std::vector<int>>& a, const int x)
	{
		auto result = std::make_pair(-1, -1);
		for (unsigned i = 0; i < a.size(); ++i)
		{
			auto rx = std::lower_bound(a[i].cbegin(), a[i].cend(), x);
			if (rx != a[i].cend() && *rx == x)
			{
				result = std::make_pair(i, rx - a[i].cbegin());
				break;
			}
		}

		return result;
	}

	/// EPI 11.10. Search in a sorted 2D-array m*n
	/// Diagonal Search. Compares x with the row ending element a[r][c - 1]:
	/// - a[r][c - 1] == x - result is found,
	/// - a[r][c - 1] < x - eliminate the column ñ - 1 by decrementing the column counter,
	/// - a[r][c - 1] > x - eliminate the row r by incrementing the row counter
	/// The resulting scan worst case: T(n) = 2d - 1, where d - diagonal of the matrix.
	/// Time: O(d), space: O(1)
	static std::pair<int, int> SearchSortedMatrixDs(const std::vector<std::vector<int>>& a, const int x)
	{
		auto result = std::make_pair(-1, -1);

		unsigned row = 0;
		int col = a[0].size() - 1;
		while (row < a.size() && col >= 0)
		{
			if (a[row][col] == x)
			{
				result = std::make_pair(row, col);
				break;
			}
			else if (a[row][col] > x)
			{
				--col;
			}
			else // a[row][col] < x
			{
				++row;
			}
		}

		return result;
	}

	/// EPI 11.4.2. 2-sum problem (Yandex Question)
	/// Returns true if an input vector contains any 2 elements that sum up to the given value.
	/// Places all the vector to the hash table for fast further searches.
	/// Iterates through the array, calculates the diff beetween sum and a[i] and finds it in the hash.
	/// If such diff exists, we have found the target pair of numbers.
	/// Time: O(n), space: O(n)
	static bool HasTwoSum(const std::vector<int>& a, const int sum)
	{
		bool result = false;
		std::unordered_set<int> ht(a.cbegin(), a.cend());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int diff = sum - a[i];
			auto found = ht.find(diff);
			if (found != ht.cend())
			{
				result = true;
				break;
			}
		}

		return result;
	}

	/// Pramp. 2-difference
	/// Returns all pairs from an array whose difference is equal to the specified number k.
	/// Time: O(n), space: O(n)
	static std::vector<std::pair<int, int>> AllTwoDiff(const std::vector<int>& a, const int k)
	{
		std::vector<std::pair<int, int>> results;
		std::unordered_set<int> ht(a.cbegin(), a.cend());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int sum = a[i] + k;
			auto found = ht.find(sum);
			if (found != ht.end())
			{
				results.push_back(std::make_pair(*found, a[i]));
			}
		}

		return results;
	}

	/// EPI 13.14. 3-sum problem
	/// Returns true if an input vector contains any 3 elements that sum up to the given value.
	/// Firstly, sort the array.
	/// Then iterate through the array, fixing a[i] element and searching 2-sum in the rest of the array a[i+1..n-1].
	/// 2-sum could be used either with min-max elimination, or with hash table algorithm.
	/// In MME, we move two indices i and j towards each other from start and end of the array.
	/// If the sum is quite big and even bigger than max, remove the min element by decrementing i,
	/// since all the pairs (min, a[i]) with that min will be anyway less than sum (too small).
	/// If the sum is quite small and smaller than min, remove the max element by incrementing j,
	/// since all the pairs (a[j], max) with that max will be anyway greater than sum (too big).
	/// Eventually, we either find the exact 2-sum, or it's not found when both indices meet.
	/// Time: O(n*log(n)) + O(n^2) = O(n^2), space: O(1)
	static bool HasThreeSum(std::vector<int>& a, const int sum)
	{
		std::sort(a.begin(), a.end());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int diff = sum - a[i];
			for (unsigned j = 0, k = a.size() - 1; j < k;)
			{
				if (j == i || a[j] + a[k] < diff)
				{
					++j;
				}
				else if (k == i || a[j] + a[k] > diff)
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

	/// EPI 13.14.1, Leetcode 15. 3-sum problem
	/// Returns all unique 3-sum combinations.
	static std::vector<std::vector<int>> AllThreeSum(std::vector<int>& a, const int sum)
	{
		std::vector<std::vector<int>> results;
		if (a.size() < 3)
		{
			return results;
		}
		if (a.size() == 3)
		{
			return a[0] + a[1] + a[2] == sum ? std::vector<std::vector<int>>(1, a) : results;
		}

		std::sort(a.begin(), a.end());
		for (unsigned i = 0; i < a.size() - 2; ++i)
		{
			if (i == 0 || a[i] != a[i - 1])
			{
				int diff = sum - a[i];
				for (unsigned j = i + 1, k = a.size() - 1; j < k;)
				{
					if (a[j] + a[k] < diff)
					{
						++j;
					}
					else if (a[j] + a[k] > diff)
					{
						--k;
					}
					else
					{
						if (j + 1 < k && a[j] == a[j + 1])
						{
							++j;
						}
						else if (k - 1 > j && a[k] == a[k - 1])
						{
							--k;
						}
						else
						{
							results.push_back(std::vector<int>({ a[i], a[j], a[k] }));
							++j; --k;
						}
					}
				}
			}
		}

		return results;
	}

	/// Returns all combinations of any 3 elements of an array that sum to given value.
	/// Brute-force generation of all combinations, C(n/k) - binomial coefficients.
	/// Time: O(n^3), space: O(1)
	static std::vector<std::vector<int>> AllThreeSumCombinations(const std::vector<int>& input, const int sum)
	{
		std::vector<std::vector<int>> results;

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

		return results;
	}
};
