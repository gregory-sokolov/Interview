#pragma once

#include <utility>
#include <vector>
#include <algorithm>

///
/// EPI. Chapter 11. Searching
///
class Searching
{
public:
	/// Yandex. Find two maximums in an integer array.
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

	/// Yandex. Find number x in an ascendingly sorted matrix m*n.
	/// Scans all rows with binary search.
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

	/// EPI 11.10. Search in a sorted 2D-array m*n.
	/// Compares x with the row ending element a[r][c - 1]:
	/// - a[r][c - 1] == x - result is found,
	/// - a[r][c - 1] < x - eliminate the column ñ - 1 by decrementing the column counter,
	/// - a[r][c - 1] > x - eliminate the row r by incrementing the row counter
	/// The resulting scan worst case: T(n) = 2d - 1, where d - diagonal of the matrix (diagonal search).
	/// Time: O(d), space: O(1)
	static std::pair<int, int> SearchSortedMatrixDs(const std::vector<std::vector<int>>& a, const int x)
	{
		auto result = std::make_pair(-1, -1);

		unsigned row = 0, col = a[0].size() - 1;
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
};
