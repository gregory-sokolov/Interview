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

	/// 2-sum problem (Yandex Question)
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

	/// 3-sum problem.
	/// Returns true if an input vector contains any 3 elements that sum up to the given value.
	/// Based on "greedy" algorithm from EPI, that uses solution of fast 2-sum search in O(n).
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

	/// Returns all combinations of any 3 elements of an array that sum to given value.
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
