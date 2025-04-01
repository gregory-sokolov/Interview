#pragma once

#include <utility>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
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
	/// Method 1: use a hash table to store and check duplicates. Requires O(n) extra space.
	/// Time: O(n), space: O(n)
	static int UniqueNumberHT(std::vector<int>& a) {
		std::unordered_set<int> ht;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			if (ht.find(a[i]) == ht.cend())
			{
				ht.insert(a[i]);
			}
			else
			{
				ht.erase(a[i]);
			}
		}

		return !ht.empty() ? *(ht.cbegin()) : 0;
	}

	/// Method 2: XOR all elements. Based on fact, that x ^ 0 = x, x ^ x = 0, hence a1 ^ a2 ^ ... ^ an ^ x ^ an ^ ... ^ a1 = x.
	/// Time: O(n), space: O(1)
	static int UniqueNumberXOR(std::vector<int>& a) {
		int x = 0;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			x ^= a[i];
		}

		return x;
	}

	/// EPI 11.3/Pramp. Array element equal to its index
	/// Returns the lowest index of an element which is equal to its index in an array: a[i] == i.
	/// Based on the property: all items before a[i] == i are less than their indices, and the ones after a[i], are greater.
	/// We use partitioning approach (similar to quick sort): select a pivot index = n/2, then
	/// if a[pivot] @lt pivot - cut off the left part, a[pivot] @gt pivot - cut off the right part, otherwise - item found.
	/// Cutting off array parts is done with adjusting start and end indices respectively, until they meet each other.
	/// Time: O(log(n)), space: O(1)
	static int EqualToIndex(const std::vector<int>& a)
	{
		int result = -1;
		if (a.empty()) { return result; }

		int start = 0, end = a.size() - 1;
		while (start <= end)
		{
			int pivot = start + (end - start) / 2;
			if (a[pivot] < pivot)
			{
				start = pivot + 1;
			}
			else if (a[pivot] > pivot)
			{
				end = pivot - 1;
			}
			else
			{
				result = pivot;
				break;
			}
		}

		return result;
	}

	/// EPI 13.5/Pramp. Intersection of two sorted arrays
	/// Finds common items in 2 sorted arrays of size n and m.
	/// Intuitive solution is the "loop join" algorithm, but its time complexity is O(n*m).
	/// Method 1: use binary search (BS), applying it to the longer array (n << m, O(n*log m)).
	/// To handle duplicates in the first array, when found, we simply advance the pointer one position up.
	/// Time: O(n*log m), space: O(1)
	static std::vector<int> ArrayIntersectionBS(const std::vector<int>& a1, const std::vector<int>& a2)
	{
		std::vector<int> results;
		if (a1.empty() || a2.empty()) { return results; };
		if (a1.back() < a2[0] || a1[0] > a2.back()) { return results; };

		const std::vector<int>& a_small = a1.size() <= a2.size() ? a1 : a2;
		const std::vector<int>& a_big = a1.size() > a2.size() ? a1 : a2;
		for (unsigned i = 0; i < a_small.size(); ++i)
		{
			if ((i == 0 || a_small[i] != a_small[i - 1]) &&
				std::binary_search(a_big.cbegin(), a_big.cend(), a_small[i]))
			{
				results.push_back(a_small[i]);
			}
		}

		return results;
	}

	/// Method 2: use two pointers (TP), iterating through both of them in tandem in increasing order (n ~ m, O(n + m)).
	/// To handle duplicates in the first array, when found, we simply advance the pointer one position up.
	/// Time: O(n + m), space: O(1)
	static std::vector<int> ArrayIntersectionTP(const std::vector<int>& a1, const std::vector<int>& a2)
	{
		std::vector<int> results;
		if (a1.empty() || a2.empty()) { return results; };
		if (a1.back() < a2[0] || a1[0] > a2.back()) { return results; };

		for (unsigned i = 0, j = 0; i < a1.size() && j < a2.size();)
		{
			if ((i == 0 || a1[i] != a1[i - 1]) &&
				a1[i] == a2[j])
			{
				results.push_back(a1[i]);
				++i, ++j;
			}
			else if (a1[i] > a2[j])
			{
				++j;
			}
			else
			{
				++i;
			}
		}

		return results;
	}

	/// Leetcode 347. Most frequent elements
	/// Given a non-empty array of integers, return the k most frequent elements.
	/// Populates hash table with the occurence statistics, then uses map instead of heap as the insertion complexitity is the same - O(log n).
	/// Time: O(n), space: O(n)
	static std::vector<std::pair<int, unsigned>> MostFrequent(const std::vector<int>& a, unsigned k)
	{
		if (a.size() == 0) { return std::vector< std::pair<int, unsigned>>(); }
		if (a.size() == 1) { return std::vector<std::pair<int, unsigned>>({ std::make_pair(a[0], 1) }); }

		std::unordered_map<int, unsigned> stats;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			if (stats.find(a[i]) != stats.cend())
			{
				++stats[a[i]];
			}
			else
			{
				stats[a[i]] = 1;
			}
		}

		std::multimap<unsigned, int, std::greater<unsigned>> hist;
		for (const auto& entry : stats)
		{
			hist.insert(std::make_pair(entry.second, entry.first));
		}

		std::vector<std::pair<int, unsigned>> values;
		std::transform(hist.cbegin(), hist.cend(), std::back_inserter(values),
			[](const std::pair<unsigned, int>& p) { return std::make_pair(p.second, p.first); });
		std::vector< std::pair<int, unsigned>> results(values.cbegin(), k < values.size() ? values.cbegin() + k : values.cend());

		return results;
	}

	/// EPI 11.10. Find a number in an ascendingly sorted matrix m*n
	/// Method 1: Binary Search. Scans all sorted rows with standard binary search.
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

	/// Method 2: Diagonal Search. Compares x with the row ending element a[r][c - 1]:
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

	/// EPI 11.4.2. 2-sum problem
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

	/// Leetcode 543, Pramp. Unique 2-difference pairs
	/// Returns all unique pairs from an array whose difference is equal to the specified number diff.
	/// The same approach as for 2-sum problem: place the vector to the hash for fast O(1) search of xi = yi + diff.
	/// Time: O(n), space: O(n)
	private: struct PairHash
	{
		inline unsigned operator()(const std::pair<int, int> p) const
		{
			std::hash<int> int_hasher;
			return int_hasher(p.first) ^ int_hasher(p.second);
		}
	};
	public: static std::vector<std::pair<int, int>> UniqueTwoDiff(const std::vector<int>& a, const int diff)
	{
		std::unordered_set<std::pair<int, int>, PairHash> results;
		std::unordered_map<int, unsigned> ht;
		for (const auto& ai : a)
		{
			auto found = ht.find(ai);
			if (found != ht.cend())
			{
				++found->second;
			}
			else
			{
				ht[ai] = 1;
			}
		}

		for (unsigned i = 0; i < a.size(); ++i)
		{
			int sum = a[i] + diff;
			auto found = ht.find(sum);
			if (found != ht.end() && (diff != 0 || (found->first == a[i] && found->second > 1)))
			{
				results.insert(std::make_pair(std::max<int>(found->first, a[i]), std::min<int>(found->first, a[i])));
			}
		}

		return std::vector<std::pair<int, int>>(results.cbegin(), results.cend());
	}

	/// EPI 13.14. 3-sum problem
	/// Returns true if an input vector contains any 3 elements that sum up to the given value.
	/// Firstly, sort the array.
	/// Then iterate through the array, fixing a[i] element and searching 2-sum in the rest of the array a[i+1..n-1].
	/// 2-sum could be used either with min-max elimination (MME), or with hash table algorithm.
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
