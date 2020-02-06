#pragma once

#include <utility>
#include <vector>
#include <queue>
#include <map>
#include <unordered_map>
#include <functional>

///
/// EPI. Chapter 10. Heaps
///
class Heaps
{
public:
	/// Leetcode 347. Most frequent elements
	/// Given a non-empty array of integers, return the k most frequent elements.
	/// Uses STL multimap (RB-tree) instead of heap as the insertion complexitity is the same - O(log n).
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
