using System;
using System.Collections.Generic;

namespace Combinatorics.Cs
{
	/// <summary>
	/// Combinatorics testing program
	/// </summary>
	public class CombinatoricsMain
	{
		/// <summary>
		/// Application entry point
		/// </summary>
		public static void Main(string[] args)
		{
			var solutions = new Combinatorics();

			Console.WriteLine("== Max Sum Subarray (MSSA) ==");
			var testMss = new List<IList<int>>
			{
				new List<int>(),
				new List<int> { 2 },
				new List<int> { -1, -5, -2 },
				new List<int> { 0, 0, 0 },
				new List<int> { 5, 1, 2 },
				new List<int> { 2, 5, -1, -7, 0, 9, -3, -4 },
				new List<int> { 2, 5, -1, -7, 0, 2, 4, 3, -3, -4 },
				new List<int> { 2, 5, -3, -2, 2, 3, 0, -2, 2, 4, 3, -1, -2 }
			};
			var count = 1;
			foreach (var test in testMss)
			{
				Console.WriteLine((count++).ToString().PadLeft(2, '0') + ": [" + string.Join(", ", test) + "]");
				var result = solutions.MaxSumSubarray(test);
				Console.WriteLine("    {0} [{1}, {2}]", result.Key, result.Value.Key, result.Value.Value);
			}
			Console.WriteLine();

			Console.WriteLine("== Max Product Subarray (MPSA) ==");
			var testMps = new List<IList<int>>
			{
				new List<int>(),
				new List<int> { 2 },
				new List<int> { 2, -2 },
				new List<int> { 2, 3, 5, 4, 3, 1 },
				new List<int> { -2, -3, -5, -4, -3, -1 },
				new List<int> { 2, 3, 5, 0, 7, 5, 1 },
				new List<int> { -1, -2, -3, 4, 0, -5, 2 },
				new List<int> { -10, 0, -20, 0, -30, 0, 0, -40 }
			};
			count = 1;
			foreach (var test in testMps)
			{
				Console.WriteLine((count++).ToString().PadLeft(2, '0') + ": [" + string.Join(", ", test) + "]");
				var result = solutions.MaxProductSubarray(test);
				Console.WriteLine("    {0} [{1}, {2}]", result.Key, result.Value.Key, result.Value.Value);
			}
			Console.WriteLine();

			Console.WriteLine("== Longest Nondecreasing Subsequence (LNDSS) ==");
			var testLnds = new List<IList<int>>
			{
				new List<int>(),
				new List<int> { 0 },
				new List<int> { 0, 2 },
				new List<int> { 2, 0 },
				new List<int> { 2, 0, 5 },
				new List<int> { 0, 2, 5 },
				new List<int> { 5, 2, 0 },
				new List<int> { 2, 0, 9, 3, 9, 1, 9, 5, 7, 7, 8 },
				new List<int> { 0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15 }
			};
			count = 1;
			foreach (var test in testLnds)
			{
				Console.WriteLine("Test " + (count++).ToString().PadLeft(2, '0') + ": [" + string.Join(", ", test) + "]");
				var result = solutions.Lnds(test);
				Console.WriteLine("Result: {0}", result.Count > 0 ? "[" + string.Join(", ", result) + "]": "-");
				Console.WriteLine();
			}
			Console.WriteLine();

			Console.WriteLine();
			Console.WriteLine("Press any key to exit...");
			Console.ReadKey();
		}
	}
}
