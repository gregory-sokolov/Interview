#pragma once

#include <utility>
#include <vector>

#include <iostream>
#include <sstream>
#include <iterator>

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
};
