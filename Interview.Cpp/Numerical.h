#pragma once

#include <queue>
#include <cmath>
#include <algorithm>

// Numerical problems
class Numerical
{
public:
	// Calculates closest integer number to the actual square root (using binary search)
	static unsigned Sqrt(unsigned n)
	{
		unsigned min = n > 2 ? 2 : 0, max = n > 5 ? n/2 : n/2 + 1, med = (min + max)/2;
		while (med > min && med < max)
		{
			unsigned square = med*med;
			if (square > n)
			{
				max = med;
				med = (min + max)/2;
			}
			else if (square < n)
			{
				min = med;
				med = (min + max)/2;
			}
			else
			{
				return med;
			}
		}

		return max*max - n <= n - min*min ? max : min;
	}

	// Calculates square root of a number using simple binary search.
	// Time: logarithmic
	static double Sqrt(double n, double p)
	{
		if (n < 0) return NAN;
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return NAN;

		double low = n > 1 ? 1 : 0, high = n < 1 ? 1 : n;
		while (high - low > p)
		{
			double mid = (low + high)/2.0;
			double square = mid*mid;
			if (square > n)
			{
				high = mid;
			}
			else if (square < n)
			{
				low = mid;
			}
			else
			{
				return mid;
			}
		}

		return (high + low)/2.0;
	}

	// Calculates square root of a number using Newton-Raphson method derived from binary search.
	// Based on such optimizations as updating both bounds together (adding low = n/mid, high = n/mid),
	// and replacing low/high with mid/prev (since low/high will be the same). 
	// Time: O (log(p)*F(p)), where F(p) is cost of division with p-precision.
	// It takes 8-9 iterations for 15-digit precision (quadratical convergence of the N-R method).
	static double SqrtNewton(double n, double p)
	{
		if (n < 0) return NAN;
		if (n == 0.0 || n == 1.0) return n;
		if (n < p) return NAN;

		double prev = 0.0, mid = n;
		while (std::abs(mid - prev) > p)
		{
			prev = mid;
			mid = (mid + n/mid)/2.0;
		}

		return mid;
	}

	// Finds all continuous sequences whose sum equals to target number.
	// Moves the "window" with the sum through the entire, removing only leading items sum exceeds target.
	// When encountered zeroes, runs a sort of "greedy" search to generate all required subsequences.
	// Time: O(n)
	static void GetSumSequences(const std::vector<int>& input, long long target,
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

	// Finds max sum subarray using modified Kadane's algorithm.
	// Handles positive and negative numbers.
	static std::pair<long long, std::pair<unsigned, unsigned>> FindMaxSumSubarray(const std::vector<int>& input)
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


	// Returns true if an input vector contains any 3 elements that sums to given value.
	// Based on "greedy" algorithm from EPI, that uses solution of fast 2-sum search in O(n).
	// Time: O(n*log(n)) + O(n^2) = O(n^2), space: O(1)
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

	// Return all combinations of any 3 elements of an array that sum to given value.
	// Brute-force generation of all combinations (C(n/k), binomial coefficients).
	// Time: O(n^3), space: O(1)
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

	// Returns k-closest point to the given point.
	// Uses max-heap algorithm with STL priority queue.
	// Time: O(n*log(k)), space: O(k)
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

