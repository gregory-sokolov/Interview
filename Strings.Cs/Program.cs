using System;
using System.Collections.Generic;

namespace Strings.Cs
{
	/// <summary>
	/// EPI. Strings
	/// </summary>
    public class Program
    {
		/// <summary>
		/// Testing program
		/// </summary>
        public static void Main(string[] args)
        {
			var solutions = new Strings();
			var dict = new SortedSet<string>
			{
				"bed", "bat", "bath", "bet", "and", "at", "hand", "beyond", "bey",
				"be", "beside", "besides", "edit", "it", "its", "id", "ion", "limit", "limited", "limitation", "imitation",
				"sit", "side", "slim", "sun"
			};
			var srcs = new List<string> { "", "bedbathandbeyond", "besideslimitation", "besidesunlimiteditqqq", "itsitsitsits" };

			foreach (var src in srcs)
			{
				Console.WriteLine("Source: " + src);
				var res = solutions.SplitByWords(src, dict);
				Console.WriteLine(res.Count > 0 ? "Results: " + string.Join(", ", res) : "No solutions");
				Console.WriteLine();
			}

			Console.WriteLine();
			Console.WriteLine("Press any key to exit...");
			Console.ReadKey();
        }
    }
}
