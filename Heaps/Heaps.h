#pragma once

#include <utility>
#include <vector>
#include <queue>
#include <functional>

///
/// EPI. Chapter 10. Heaps
///
class Heaps
{
public:
	/// EPI 10.8/Leetcode 295. Online median of a stream
	/// Computes running median of a sequence.
	/// We use two heaps, heap_left (max) and heap_right (min), to make a partition of the stream items around the 'virtual' median value. 
	/// When we encounter a value less than median, we place it to the left heap, otherwise to the right one. We keep both heaps 'balanced', 
	/// that is, we move the top items from one heap to another when the heap sizes differ for more than one. Such balancing allows to preserve
	/// the median calculation context. 
	/// The resulting median is either on the top of a larger heap (odd count of input), or is the average of both heap tops (even count).
	/// Time: O(n*log(n)) - O(1)/O(log(n)) for heap operations, space: O(n) - heap allocation
	static std::vector<double> OnlineMedian(const std::vector<int>& a)
	{
		if (a.empty()) { return std::vector<double>(); }
		if (a.size() == 1) { return std::vector<double>(1, a[0]); }

		std::vector<double> results;
		std::priority_queue<int> heap_left;
		std::priority_queue<int, std::vector<int>, std::greater<int>> heap_right;
		if (a[0] <= a[1])
		{
			heap_left.push(a[0]);
		}
		else
		{
			heap_right.push(a[0]);
		}
		results.push_back(a[0]);

		for (unsigned i = 1; i < a.size(); ++i)
		{
			double med = results.back();
			if (a[i] <= med)
			{
				if (heap_left.size() > heap_right.size())
				{
					heap_right.push(heap_left.top());
					heap_left.pop();
				}
				heap_left.push(a[i]);
			}
			else
			{
				if (heap_right.size() > heap_left.size())
				{
					heap_left.push(heap_right.top());
					heap_right.pop();
				}
				heap_right.push(a[i]);
			}
			
			if (heap_right.size() > heap_left.size())
			{
				med = heap_right.top();
			}
			else if (heap_right.size() < heap_left.size())
			{
				med = heap_left.top();
			}
			else
			{
				med = ((double)heap_right.top() + (double)heap_left.top()) / 2;
			}
			results.push_back(med);
		}

		return results;
	}

	/// EPI 10.4, Leetcode 347. Returns k-closest point to the given point.
	/// Uses max-heap algorithm with STL priority_queue.
	/// Time: O(n*log(k)), space: O(k)
	static void GetClosestPoints(unsigned k, std::pair<double, double> origin, const std::vector<std::pair<double, double>>& points,
		std::vector<std::pair<double, double>>& results)
	{
		auto compare = [origin](std::pair<double, double> p1, std::pair<double, double> p2)
		{
			// No need to calculate full hypotenuse to economize on sqrt operation
			auto d1 = (p1.first - origin.first)*(p1.first - origin.first) +
				(p1.second - origin.second)*(p1.second - origin.second);
			auto d2 = (p2.first - origin.first)*(p2.first - origin.first) +
				(p2.second - origin.second)*(p2.second - origin.second);
			return d1 < d2;
		};
		std::priority_queue<std::pair<double, double>, std::vector<std::pair<double, double>>, decltype(compare)>
			pq(compare);

		for (auto&& pi : points)
		{
			if (pq.size() < k)
			{
				pq.push(pi);
			}
			else
			{
				if (compare(pi, pq.top()))
				{
					pq.push(pi);
					pq.pop();
				}
			}
		}

		while (!pq.empty())
		{
			results.push_back(pq.top());
			pq.pop();
		}
		std::reverse(results.begin(), results.end());
	}
};
