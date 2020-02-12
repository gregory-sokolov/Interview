#pragma once

#include <utility>
#include <vector>

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>

///
/// EPI. Chapter 13. Sorting Problems
///
class Sorting
{
public:
	/// EPI 6.1. Dutch national flag
	/// Rearranges the array in such way that all elements less that a[i] appear first, followed by elements equal to a[i],
	/// followed by elements greater than a[i].
	/// The idea is to maintain 3 'virtual' groups: smaller, equals and larger.
	/// Move along the array, analyse each element and place it to the necessary group by swapping.
	/// Time: O(n), memory: O(1)
	static void DnfPartition(std::vector<int>& a, const int index)
	{
		int pivot = a[index];
		int smaller = 0, equal = 0, larger = a.size() - 1;
		while (equal <= larger)
		{
			if (a[equal] < pivot)
			{
				std::swap(a[smaller++], a[equal++]);
			}
			else if (a[equal] == pivot)
			{
				++equal;
			}
			else
			{
				std::swap(a[equal], a[larger--]);
			}
		}
	}
	/// Alternative implementation using QuickSort partitions.
	/// The first pass makes standard partition, splitting the array into 2 groups with guaranteed less and greater elements, than the pivot.
	/// The other 2 passes pulls the pivot elements to the end and to the start of partitioned subarrays respectively.
	/// The implementation is not that short but complies to the time and memory constraints.
	/// Time: O(n), memory: O(1)
	static void DnfPartition(int* a, int n, int index)
	{
		int pivot = a[index];
		int i = 0, j = n - 1;
		while (i <= j)
		{
			while (a[i] < pivot) ++i;
			while (a[j] > pivot) --j;
			if (i <= j)
			{
				std::swap(a[i], a[j]);
				++i, --j;
			}
		}

		int n1 = j, n2 = i;
		i = 0, j = n1;
		while (i <= j)
		{
			while (a[i] < pivot) ++i;
			while (a[j] == pivot) --j;
			if (i <= j)
			{
				std::swap(a[i], a[j]);
				++i, --j;
			}
		}
		i = n2, j = n - 1;
		while (i <= j)
		{
			while (a[i] == pivot) ++i;
			while (a[j] > pivot) --j;
			if (i <= j)
			{
				std::swap(a[i], a[j]);
				++i, --j;
			}
		}
	}

	/// Quick Sort canonical implementation in C (based on array size)
	static void QuickSortNR(int* a, int n)
	{
		if (n < 3)
		{
			if (a[0] > a[1])
			{
				std::swap(a[0], a[1]);
			}
			return;
		}

		int i = 0, j = n - 1;
		int p = a[n/2];
		while (i <= j)
		{
			while (a[i] < p) ++i;
			while (a[j] > p) --j;
			if (i <= j)
			{
				if (i < j)
				{
					std::swap(a[i], a[j]);
				}
				++i, --j;
			}
		}

		if (j > 1) QuickSortNR(a, j + 1);
		if (n > i && n - i > 1) QuickSortNR(a + i, n - i);
	}
	/// [Debug] Quick Sort canonical implementation in C (based on array size)
	static void QuickSortDebugNR(int* a, int n, int tc)
	{
		tc += 2;
		std::string tab(tc, ' ');
		std::string swapped;

		if (n < 3)
		{
			std::cout << tab.c_str();
			std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
			std::cout << ", n=" << n << ", simple case" << std::endl;

			if (a[0] > a[1])
			{
				std::swap(a[0], a[1]);
			}

			std::cout << tab.c_str();
			std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
			std::cout << ", n=" << n << std::endl;

			return;
		}
		
		std::cout << tab.c_str();
		std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
		std::cout << ", n=" << n << std::endl;
		
		int i = 0, j = n - 1;
		int p = a[n / 2];
		while (i <= j)
		{
			while (a[i] < p) ++i;
			while (a[j] > p) --j;
			if (i <= j)
			{
				if (i < j) 
				{ 
					std::swap(a[i], a[j]);
					swapped = ", " + std::to_string(i) + "<->" + std::to_string(j);
				}
				++i, --j;
			}

			std::cout << tab.c_str();
			std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
			std::cout << swapped << ", p=" << p << ", i=" << i << ", j=" << j << std::endl;
			swapped = "";
		}

		if (j > 1) QuickSortDebugNR(a, j + 1, tc);
		else std::cout << tab.c_str() << "Skip Rec-L, n=" << j + 1 << std::endl;

		std::cout << tab.c_str();
		std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
		std::cout << ", after Rec-L" << std::endl;

		if (n > i && n - i > 1) QuickSortDebugNR(a + i, n - i, tc);
		else std::cout << tab.c_str() << "Skip Rec-R, n = " << n - i << std::endl;

		std::cout << tab.c_str();
		std::copy(&a[0], &a[n], std::ostream_iterator<int>(std::cout));
		std::cout << ", after Rec-R" << std::endl;
	}

	/// Quick Sort canonical implementation in C (based on indexes)
	static void QuickSortDebugIR(int* a, int l, int r)
	{
		if (r - l + 1 < 3)
		{
			if (a[0] > a[1])
			{
				std::swap(a[0], a[1]);
			}
			return;
		}

		int i = l, j = r;
		int p = a[(l + r) / 2];
		while (i <= j)
		{
			while (a[i] < p) ++i;
			while (a[j] > p) --j;
			if (i <= j)
			{
				if (i < j)
				{
					std::swap(a[i], a[j]);
				}
				++i, --j;
			}
		}

		if (j > l) QuickSortDebugIR(a, l, j);
		if (i < r) QuickSortDebugIR(a, i, r);
	}
	/// [Debug] Quick Sort canonical implementation in C (based on indexes)
	static void QuickSortDebugIR(int* a, int l, int r, int tc)
	{
		tc += 2;
		std::string tab(tc, ' ');
		std::string swapped;

		if (r - l + 1 < 3)
		{
			std::cout << tab.c_str();
			std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
			std::cout << ", l=" << l << ", r=" << r << ", simple case" << std::endl;

			if (a[0] > a[1])
			{
				std::swap(a[0], a[1]);
			}

			std::cout << tab.c_str();
			std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
			std::cout << ", l=" << l << ", r=" << r << std::endl;

			return;
		}

		std::cout << tab.c_str();
		std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
		std::cout << ", l=" << l << ", r=" << r << std::endl;

		int i = l, j = r;
		int p = a[(l + r) / 2];
		while (i <= j)
		{
			while (a[i] < p) ++i;
			while (a[j] > p) --j;
			if (i <= j)
			{
				if (i < j)
				{
					std::swap(a[i], a[j]);
					swapped = ", " + std::to_string(i) + "<->" + std::to_string(j);
				}
				++i, --j;
			}

			std::cout << tab.c_str();
			std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
			std::cout << swapped << ", p=" << p << ", i=" << i << ", j=" << j << std::endl;
			swapped = "";
		}

		if (j > l) QuickSortDebugIR(a, l, j, tc);
		else std::cout << tab.c_str() << "Skip Rec-L, l=" << l << ", r=" << j << std::endl;

		std::cout << tab.c_str();
		std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
		std::cout << ", after Rec-L" << std::endl;

		if (i < r) QuickSortDebugIR(a, i, r, tc);
		else std::cout << tab.c_str() << "Skip Rec-R, l=" << i << ", r=" << r << std::endl;

		std::cout << tab.c_str();
		std::copy(&a[l], &a[r + 1], std::ostream_iterator<int>(std::cout));
		std::cout << ", after Rec-R" << std::endl;
	}


	/// Merge two sorted vectors (Yandex Question).
	/// Merges two sorted vectors of sizes m and n into the third destination vector.
	/// Implements std::merge algorithm.
	/// Time: O(max(m, n)), space: O(m) + O(n)
	static std::vector<int> MergeSorted(const std::vector<int>& v1, const std::vector<int>& v2)
	{
		std::vector<int> dest;
		if (v1.empty())
		{
			std::copy(v2.cbegin(), v2.cend(), std::back_inserter(dest));
			return dest;
		}
		if (v2.empty())
		{
			std::copy(v1.cbegin(), v1.cend(), std::back_inserter(dest));
			return dest;
		}

		for (auto it1 = v1.cbegin(), it2 = v2.cbegin(); it1 != v1.cend() || it2 != v2.cend();)
		{
			if (it1 == v1.cend())
			{
				std::copy(it2, v2.cend(), std::back_inserter(dest));
				break;
			}
			if (it2 == v2.cend())
			{
				std::copy(it1, v1.cend(), std::back_inserter(dest));
				break;
			}

			if (*it2 <= *it1)
			{
				dest.push_back(*it2);
				++it2;
			}
			if (*it1 <= *it2)
			{
				dest.push_back(*it1);
				++it1;
			}
		}

		return dest;
	}

	/// EPI 13.8/Leetcode 26. Removing duplicates in a sorted array
	/// Similar to std::unique.
	/// Moves all unique values to the beginning of the vector in-place and returns the size of deduplicated subsequence (past-the-last iterator).
	/// The inital vector is already sorted ascendingly. It doesn't matter what values and in what order are set beyond the returned size.
	/// We iterate through the vector. In normal case, we search for start and end index of a subarray with duplicates.
	/// When found, swap the first subarray element with the one of duplicates in the beginning (or with itself if it's single item in its place).
	/// Handle the special case of last unique element, simply moving it to the end of the resulting sequence. 
	/// Time: O(n), space: O(1)
	static unsigned DeduplicateSorted(std::vector<int>& a)
	{
		if (a.size() == 0) { return 0; }
		if (a.size() == 1) { return 1; }
		
		unsigned end = 0, j = 0;
		for (unsigned i = 0; i < a.size(); i = j)
		{
			for (j = i + 1; j < a.size(); ++j)
			{
				if (a[j] > a[i])
				{
					std::swap(a[i], a[end]);
					break;
				}
			}

			if (j == a.size() && end > 0 && a[j - 1] > a[end - 1])
			{
				std::swap(a[j - 1], a[end]);
			}

			++end;
		}

		return end;
	}

	/// EPI 13.5/Pramp. Intersection of two sorted arrays
	/// Finds common items in 2 sorted arrays of size n and m.
	/// Intuitive solution is the "loop join" algorithm, but its time complexity is O(n*m).
	/// A better method is to use binary search (BS), applying it to the longer array (n << m, O(n*log m)).
	/// For sorted arrays, we iterate through both of them with two pointers (TP) in tandem in increasing order (n ~ m, O(n + m)).
	/// To handle duplicates in the first array, we simply advance the pointer one position up.
	/// Time: O(n + m), space: O(1)
	static std::vector<int> ArrayIntersectionBS(std::vector<int>& a1, std::vector<int>& a2)
	{
		std::vector<int> results;
		if (a1.empty() || a2.empty()) { return results; };
		if (a1.back() < a2[0] || a1[0] > a2.back()) { return results; };

		std::vector<int>& a_small = a1.size() <= a2.size() ? a1 : a2;
		std::vector<int>& a_big = a1.size() > a2.size() ? a1 : a2;
		for (unsigned i = 0, j = 0; i < a_small.size(); ++i)
		{
			if ((i == 0 || a_small[i] != a_small[i - 1]) &&
				std::binary_search(a_big.cbegin(), a_big.cend(), a_small[i]))
			{
				results.push_back(a_small[i]);
			}
		}

		return results;
	}
	static std::vector<int> ArrayIntersectionTP(std::vector<int>& a1, std::vector<int>& a2)
	{
		std::vector<int> results;
		if (a1.empty() || a2.empty()) { return results; };
		if (a1.back() < a2[0] || a1[0] > a2.back()) { return results; };

		for (unsigned i = 0, j = 0; i < a1.size() && j < a2.size();)
		{
			if (a1[i] == a2[j] && (i == 0 || a1[i] != a1[i -1]))
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
};

