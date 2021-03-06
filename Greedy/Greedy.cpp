/// 
/// Greedy Method Problems
///

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <numeric>

using namespace std;

#include "Greedy.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Greedy Method ==" << endl << endl;

	cout << "- Scheduling Tutors (GISMP) -" << endl;
	{
		vector<pair<double, double>> schedule =
		{
			{ 9, 9.5 },{ 9.3, 9.8 },{ 9.5, 10.0 },{ 9.8, 10.3 },{ 9.9, 10.4 },{ 10.0, 10.5 },{ 10.2, 10.7 },{ 10.5, 11.0 },
			{ 10.5, 11.0 },{ 10.8, 11.3 },{ 11.5, 12.0 }
		};
		auto tutors = Greedy::ScheduleTutors(schedule, 2.0);
		cout << "Max tutors: " << tutors.size() << endl;
	}
	cout << endl;

	cout << "- Greedy Method. Coin Change -" << endl;
	{
		vector<unsigned> coinage = { 1, 2, 5, 10, 25, 50 };
		vector<unsigned> sums = { 0, 1, 2, 3, 5, 79, 100, 122, 243, 1399 };
		for (const auto& sum : sums)
		{
			auto results = Greedy::CoinChangeGreedy(coinage, sum);
			auto coins = accumulate(results.cbegin(), results.cend(), (unsigned)0,
				[](const unsigned& s, const pair<unsigned, unsigned>& ci) { return s + ci.second; });
			cout << "Sum: " << sum << ", coins (" << coins << "): { ";
			for (auto it = results.cbegin(); it != results.cend(); ++it)
			{
				cout << it->first << ":" << it->second << (it != results.cend() - 1 ? ", " : "");
			}
			cout << " }" << endl;
		}
	}
	cout << endl;

	cout << "- Greedy Method. Huffman Coding -" << endl;
	{
		vector<vector<pair<char, double>>> freqs =
		{
			{ {} },
			{ { 'e', 12.98 } },
			{ { 'e', 12.98 },{ 'h', 5.79 } },
			{ { 'e', 12.98 },{ 't', 8.49 },{ 'i', 6.51 },{ 'h', 5.79 } },
			{
				{ 'a', 8.17 },{ 'b', 1.49 },{ 'c', 2.78 },{ 'd', 4.25 },{ 'e', 12.7 },{ 'f', 2.23 },{ 'g', 2.02 },{ 'h', 6.09 },
				{ 'i', 6.97 },{ 'j', 0.15 },{ 'k', 0.77 },{ 'l', 4.03 },{ 'm', 2.41 },{ 'n', 6.75 },{ 'o', 7.51 },{ 'p', 1.93 },
				{ 'q', 0.1 },{ 'r', 5.99 },{ 's', 6.33 },{ 't', 9.06 },{ 'u', 2.76 },{ 'v', 0.98 },{ 'w', 2.36 },{ 'x', 0.15 },
				{ 'y', 1.97 },{ 'z', 0.07 }
			}
		};
		for (const auto& freq : freqs)
		{
			auto results = Greedy::HuffmanCoding(freq);
			for (auto it = freq.cbegin(); it != freq.cend(); ++it)
			{
				cout << it->first << ":" << it->second << ":" << results[it->first] << (it != freq.cend() - 1 ? ", " : "") << endl;
			}
			cout << "--" << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

