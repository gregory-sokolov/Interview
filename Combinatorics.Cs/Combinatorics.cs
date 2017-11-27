using System;
using System.Collections.Generic;

namespace Combinatorics.Cs
{
	/// <summary>
	/// EPI. Combinatorial Problems
	/// </summary>
	public class Combinatorics
	{
		/// <summary>
		/// EPI 15.5.1. Max sum subarray (MSSA).
		/// Returns subarray with maximum sum using Kadane's algorithm (Dynamic Programming (DP)).
		/// Kadane's algorithm is based on the fact: max_sum(i + 1) = max(max_sum(i), a[i]).
		/// We can start from trivial case with max_sum=a[0](0,0) and infer further sums using memoization in DP.
		/// Variables: tracking max sum (ts), overall max sum (ms) and related subarray indexes (mi, mj).
		/// Time: O(n), space: O(1)
		/// </summary>
		public KeyValuePair<int, KeyValuePair<int, int>> MaxSumSubarray(IList<int> a)
		{
			if (a == null || a.Count == 0)
			{
				return new KeyValuePair<int, KeyValuePair<int, int>>(-1, new KeyValuePair<int, int>(-1, -1));
			}

			int ts = a[0], ms = a[0];
			int ti = 0, mi = 0, mj = 0;
			for (var i = 1; i < a.Count; ++i)
			{
				var sum = ts + a[i];
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

			return new KeyValuePair<int, KeyValuePair<int, int>>(ms, new KeyValuePair<int, int>(mi, mj));
		}

		/// <summary>
		/// EPI 15.5.2. Max product subarray (MPSA).
		/// Finds the subarray with maximum product in an array of positive, negative and zero values.
		/// The main idea is similar to MSSA: track and store maximums in DP style when interating.
		/// Both maximum and minimum products are tracked to handle transitions between positive and negative numbers.
		/// Swap them on negative number, since after the multiplication to a negative the extremums will change their places.
		/// Given in 2 versions: original one for a better understanding and a full one with subarray index range.
		/// Range search is based on rolling back each maximum candidate by dividing it consequently by previous array items.
		/// Time: O(n), space: O(1)
		/// </summary>
		public int MaxProductSubarrayOriginal(IList<int> a)
		{
			int pmax = a[0], pmin = a[0], result = a[0];
			for (var i = 1; i < a.Count; ++i)
			{
				if (a[i] < 0)
				{
					var tmp = pmax;
					pmax = pmin;
					pmin = tmp;
				}

				pmax = Math.Max(a[i], pmax * a[i]);
				pmin = Math.Min(a[i], pmin * a[i]);

				result = Math.Max(result, pmax);
			}

			return result;
		}
		/// Version with subarray range
		public KeyValuePair<int, KeyValuePair<int, int>> MaxProductSubarray(IList<int> a)
		{
			if (a == null || a.Count == 0)
			{
				return new KeyValuePair<int, KeyValuePair<int, int>>(-1, new KeyValuePair<int, int>(-1, -1));
			}

			int pmax = a[0], pmin = a[0], result = a[0];
			int left = 0, right = 0;
			for (var i = 1; i < a.Count; ++i)
			{
				if (a[i] < 0)
				{
					var tmp = pmax;
					pmax = pmin;
					pmin = tmp;
				}

				pmax = Math.Max(a[i], pmax * a[i]);
				pmin = Math.Min(a[i], pmin * a[i]);

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

			return new KeyValuePair<int, KeyValuePair<int, int>>(result, new KeyValuePair<int, int>(left, right));
		}

		/// <summary>
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
		/// </summary>
		public IList<int> Lnds(IList<int> a)
		{
			if (a == null || a.Count == 0)
			{
				return new List<int>();
			}

			var endings = new List<int> { a[0] };
			var lists = new List<IList<int>> { new List<int> { a[0] } };
			LogLists(0, a[0], lists);
			
			for (var i = 1; i < a.Count; ++i)
			{
				IList<int> first = lists[0], last = lists[lists.Count - 1];
				if (a[i] < first[first.Count - 1])
				{
					endings.Insert(0, a[i]);
					lists.Insert(0, new List<int> { a[i] });
				}
				else if (a[i] >= last[last.Count - 1])
				{
					endings.Add(a[i]);
					lists.Add(new List<int>(last) { a[i] });
				}
				else
				{
					var index = endings.BinarySearch(a[i]);
					index = index < 0 ? ~index : index + 1;
					endings[index] = a[i];

					var previous = new List<int>(lists[index - 1]) { a[i] };
					lists.RemoveAt(index);
					lists.Insert(index, previous);
				}

				LogLists(i, a[i], lists);
			}

			return lists[lists.Count - 1];
		}

		/// LNDSS log helper
		void LogLists(int i, int ai, IList<IList<int>> lists)
		{
			Console.WriteLine("{0}: {1}", i.ToString().PadLeft(2, '0'), ai);
			foreach (var list in lists)
			{
				Console.WriteLine("  " + string.Join("-", list));
			}
		}
	}
}
