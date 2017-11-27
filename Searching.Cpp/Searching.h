#pragma once

#include <utility>
#include <vector>

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
};
