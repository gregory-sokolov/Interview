using System;
using System.Collections.Generic;
using System.Linq;

namespace Strings.Cs
{
	/// <summary>
	/// EPI. Strings
	/// </summary>
	public class Strings
	{
		/// <summary>
		/// EPI 15.12. Word breaking (bedbathandbeyond problem).
		/// Checks if the text is a consequent concatenation of words and returns that sequence.
		/// Time: O(n^2), space: O(n)
		/// </summary>
		public IList<string> SplitByWords(string source, ISet<string> dictionary)
		{
			var results = new Stack<KeyValuePair<string, int>>();
			var word = string.Empty;
			for (var i = 0; i < source.Length; ++i)
			{
				word += source[i];
				if (dictionary.Contains(word))
				{
					results.Push(new KeyValuePair<string, int>(word, i));
					word = string.Empty;

					LogResults(results);
				}

				if (i == source.Length - 1 &&
					word != string.Empty &&
					results.Count > 0)
				{
					var last = results.Pop();
					word = last.Key;
					i = last.Value;

					LogResults(results);
				}
			}

			return results.Select(x => x.Key).Reverse().ToList();
		}

		/// <summary>
		/// Log helper
		/// </summary>
		static void LogResults(Stack<KeyValuePair<string, int>> results)
		{
			var words = results.Select(x => x.Key + ":" + x.Value).Reverse();
			Console.WriteLine("[ " + string.Join(", ", words) + " ]");
		}

	}
}
