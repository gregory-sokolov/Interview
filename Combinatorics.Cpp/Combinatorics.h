#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <unordered_set>
#include <algorithm>

///
/// Combinatorial Problems
///
class Combinatorics
{
public:
	/// EPI 6.10. Permuting the elements of an array
	/// Generates all permutations P(n) recursively.
	/// Time: O(n!), space: O(1) - in-place swap
	template<typename T>
	static void PermutationsR(T* input, unsigned size, unsigned length, std::vector<std::vector<T>>& results)
	{
		if (input != NULL && size != 0)
		{
			if (size == 1)
			{
				vector<T> perm;
				std::copy(input - length + 1, input + 1, std::back_inserter<vector<T>>(perm));
				results.push_back(perm);
			}
			else
			{
				for (unsigned i = 0; i < size; ++i)
				{
					std::swap(input[0], input[i]);
					PermutationsR(input + 1, size - 1, length, results);
					std::swap(input[i], input[0]);
				}
			}
		}
	}

	/// EPI 15.5.1. Max sum subarray (MSSA).
	/// Returns subarray with maximum sum using Kadane's algorithm (Dynamic Programming (DP)).
	/// Kadane's algorithm is based on the fact: max_sum(i + 1) = max(max_sum(i), a[i]).
	/// We can start from trivial case with max_sum=a[0](0,0) and infer further sums using memoization in DP.
	/// Variables: tracking max sum (ts), overall max sum (ms) and related subarray indexes (mi, mj).
	/// Time: O(n), space: O(1)
	static std::pair<int, std::pair<int, int>> Mssa(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::make_pair(-1, std::make_pair(-1, -1));
		}

		int ts = a[0], ms = a[0];
		int ti = 0, mi = 0, mj = 0;
		for (unsigned i = 1; i < a.size(); ++i)
		{
			int sum = ts + a[i];
			if (a[i] > sum)
			{
				ts = a[i];
				ti = i;
			}
			else
			{
				ts = sum;
			}

			if (ts > ms)
			{
				ms = ts;
				mi = ti;
				mj = i;
			}
		}

		return std::make_pair(ms, std::make_pair(mi, mj));
	}

	/// EPI 15.5.2. Max product subarray (MPSA).
	/// Finds the subarray with maximum product in an array of positive, negative and zero values.
	/// The main idea is similar to MSSA: track and store maximums in DP style when interating.
	/// Both maximum and minimum products are tracked to handle transitions between positive and negative numbers.
	/// Swap them on negative number, since after the multiplication to a negative the extremums will change their places.
	/// Given in 2 versions: the original one for a better understanding and the full one with subarray index range.
	/// Range searching is based on rolling back each maximum candidate by dividing it consequently by previous array items.
	/// Time: O(n), space: O(1)
	static int MpsaOriginal(const std::vector<int>& a)
	{
		int pmax = a[0], pmin = a[0], result = a[0];
		for (unsigned i = 1; i < a.size(); ++i)
		{
			if (a[i] < 0)
			{
				std::swap(pmax, pmin);
			}

			pmax = std::max(a[i], pmax * a[i]);
			pmin = std::min(a[i], pmin * a[i]);

			result = std::max(result, pmax);
		}

		return result;
	}
	/// Version with subarray range
	static std::pair<int, std::pair<int, int>> Mpsa(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::make_pair(-1, std::make_pair(-1, -1));
		}

		int pmax = a[0], pmin = a[0], result = a[0];
		int left = 0, right = 0;
		for (unsigned i = 1; i < a.size(); ++i)
		{
			if (a[i] < 0)
			{
				std::swap(pmax, pmin);
			}

			pmax = std::max(a[i], pmax * a[i]);
			pmin = std::min(a[i], pmin * a[i]);

			if (pmax >= result)
			{
				result = pmax;

				right = i;
				left = right;
				for (int div = pmax; div != 1 && left >= 0 && a[left] != 0; --left)
				{
					div /= a[left];
				}
				++left;
			}
		}

		return std::make_pair(result, std::make_pair(left, right));
	}

	/// EPI 15.5.3. Longest Common Subsequence (LCSS).
	/// Returns LCSS of two strings with lengths m and n.
	/// Classical DP algorithm based on tabular memoization, where we build the matrix of matches.
	/// If there is no match, the maximum of the previous-top and previous-left elements is used.
	/// The second loop build the resulting string by traversing the matrix.
	/// Time: O(m*n), space: O(n) for matrix
	static std::string Lcss(std::string s1, std::string s2)
	{
		if (s1.size() == 0 || s2.size() == 0)
		{
			return std::string();
		}

		std::vector<std::vector<int>> mx(s1.size() + 1, std::vector<int>(s2.size() + 1));
		for (unsigned i = 1; i <= s1.size(); ++i)
		{
			for (unsigned j = 1; j <= s2.size(); ++j)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					mx[i][j] = 1 + mx[i - 1][j - 1];
				}
				else
				{
					mx[i][j] = std::max(mx[i - 1][j], mx[i][j - 1]);
				}
			}
		}

		std::string result;
		for (int i = s1.size(), j = s2.size(); i > 0 && j > 0;)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				result = s1[i - 1] + result;
				--i; --j;
			}
			else if (mx[i - 1][j] > mx[i][j - 1])
			{
				--i;
			}
			else
			{
				--j;
			}
		}

		return result;
	}

	/// Yandex. Common Subset/Set Intersection (CSS).
	/// Similar to LCSS algorithm but with slightly different results.
	/// Actually, LCSS is very like to an intersection of two sets.
	/// To use STL set operations, both sequences must be initially sorted.
	/// Time: O(n*log(n)) + O(m*log(m)) + O(n + m) =  O(MN*log(MN)), where MN = max(m, n)
	/// Space: O(n) or O(m) for intersection
	static std::string LcssStl(std::string s1, std::string s2)
	{
		std::string check;
		std::sort(s1.begin(), s1.end());
		std::sort(s2.begin(), s2.end());
		std::set_intersection(s1.cbegin(), s1.cend(), s2.cbegin(), s2.cend(), std::back_inserter(check));

		return check;
	}

	/// EPI 15.6. Longest nondecreasing subsequence (LNDSS).
	/// Finds longest nondecreasing subsequence in an array of integers.
	/// The resulting sequence should not necessarily be a subarray.
	/// Builds active lists with possible sequences, using binary search to find the best ending candidate.
	/// Cases: 
	/// - [New] Smaller than all known endings. Start a new list with the single element a[i].
	/// - [Clone + Extend] Greater than all known endings. Clone the largest list and extend it by a[i].
	/// - [Find + Replace] In between of known endings.
	///   Find a larger list with the ending greater than a[i] using binary search. Locate the previous list, clone and extend it by a[i].
	///   Replace the larger list with the previous list. It discards all less perpective lists.
	/// To find the resulting sequence, O(n) space is required to store all intermediate sequences (mapped to endings).
	/// To find the length only, it's enough just to keep the array of endings.
	/// Time: O(n*log(n)), space: O(n)
	static const std::vector<int> Lndss(const std::vector<int>& a)
	{
		if (a.size() == 0)
		{
			return std::vector<int>();
		}

		std::deque<int> endings = { a[0] };
		std::deque<std::deque<int>> lists = { { a[0] } };
		Combinatorics::LogLists(0, a[0], lists);

		for (unsigned i = 1; i < a.size(); ++i)
		{
			std::deque<int> first = lists[0], last = lists[lists.size() - 1];
			if (a[i] < first[first.size() - 1])
			{
				endings.push_front(a[i]);
				std::deque<int> next = { a[i] };
				lists.push_front(next);
			}
			else if (a[i] >= last[last.size() - 1])
			{
				endings.push_back(a[i]);
				std::deque<int> clone(last.cbegin(), last.cend());
				clone.push_back(a[i]);
				lists.push_back(clone);
			}
			else
			{
				auto found = std::upper_bound(endings.cbegin(), endings.cend(), a[i]);
				unsigned index = found - endings.cbegin();
				endings[index] = a[i];

				std::deque<int> previous(lists[index - 1].cbegin(), lists[index - 1].cend());
				previous.push_back(a[i]);
				lists[index] = previous;
			}

			LogLists(i, a[i], lists);
		}

		std::vector<int> result((lists.cend() - 1)->cbegin(), (lists.cend() - 1)->cend());
		return result;
	}

	/// LNDSS log helper
	static void LogLists(const int i, const int ai, const std::deque<std::deque<int>>& lists)
	{
		cout << setiosflags(ios::right) << setw(2) << setfill('0') << i << ": " << ai << endl;
		for (auto lit = lists.cbegin(); lit != lists.end(); ++lit)
		{
			std::cout << "  ";
			for (auto it = lit->cbegin(); it != lit->end(); ++it)
			{
				std::cout << *it << (it != lit->end() - 1 ? "-" : "");
			}
			std::cout << endl;
		}
	}

	/// EPI 15.7. Longest sum subarray problem (LSSA)
	/// Finds all subarrays whose sum equals or less than the target number.
	/// Moves the "window" with the sum through the entire array, removing only leading items if sum exceeds target.
	/// When encounters zeroes, runs a sort of "greedy" search to generate all required subsequences.
	/// Time: O(n)
	static void Lssa(const std::vector<int>& input, long long target,
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

	/// Yandex. 2-sum problem
	/// Returns true if an input vector contains any 2 elements that sum up to the given value.
	/// Places all the vector to the hash table for fast further searches.
	/// Iterates through the array, calculates the diff beetween sum and a[i] and finds it in the hash.
	/// If such diff exists, we have found the target pair of numbers.
	/// Time: O(n), space: O(n)
	static bool HasTwoSum(const std::vector<int>& a, const int sum)
	{
		bool result = false;
		std::unordered_set<int> hash(a.cbegin(), a.cend());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int d = sum - a[i];
			auto found = hash.find(d);
			if (found != hash.cend())
			{
				result = true;
				break;
			}
		}

		return result;
	}

	/// Facebook. 3-sum problem
	/// Returns true if an input vector contains any 3 elements that sum up to the given value.
	/// Based on "greedy" algorithm from EPI, that uses solution of fast 2-sum search in O(n).
	/// Time: O(n*log(n)) + O(n^2) = O(n^2), space: O(1)
	static bool HasThreeSum(std::vector<int>& a, const int sum)
	{
		std::sort(a.begin(), a.end());
		for (unsigned i = 0; i < a.size(); ++i)
		{
			int d = sum - a[i];
			for (unsigned j = 0, k = a.size() - 1; j < k;)
			{
				if (j == i || a[j] + a[k] < d)
				{
					++j;
				}
				else if (k == i || a[j] + a[k] > d)
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

	/// Return all combinations of any 3 elements of an array that sum to given value.
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


	/// Yandex. Subset Sum (SSS)
	/// Brute-force recursive implementation.
	/// Time: O(2^n), space: O(1)
	static bool HasSubsetSumR(std::vector<int>& a, int n, int sum)
	{
		if (sum == 0)
		{
			return true;
		}
		else if (n == 0 && sum != 0)
		{
			return false;
		}

		if (a[n - 1] > sum)
		{
			return Combinatorics::HasSubsetSumR(a, n - 1, sum);
		}
		else
		{
			return Combinatorics::HasSubsetSumR(a, n - 1, sum) || Combinatorics::HasSubsetSumR(a, n - 1, sum - a[n - 1]);
		}
	}

};

