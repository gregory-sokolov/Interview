/// 
/// Combinatorial Problems
///

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

using namespace std;

#include "Combinatorics.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Combinatorics ==" << endl << endl;

	cout << "- Permutations -" << endl;
	{
		vector<vector<unsigned>> results;
		unsigned* pmt0 = NULL;
		
		cout << "Test 01: -" << endl;
		Combinatorics::PermutationsR(pmt0, 0, 0, results);
		cout << "Permutations (" << results.size() << "): ";
		for (auto it = results.begin(); it < results.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}
		cout << endl;

		unsigned pmti[] = { 1, 2, 3, 4 };
		cout << "Test 02: ";
		copy(pmti, pmti + sizeof(pmti) / sizeof(int), ostream_iterator<unsigned>(cout));
		cout << endl;
		Combinatorics::PermutationsR(pmti, sizeof(pmti) / sizeof(unsigned), sizeof(pmti) / sizeof(unsigned), results);
		cout << "Permutations (" << results.size() << "): ";
		for (auto it = results.begin(); it < results.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Phone Pad Mnemonic Combinations -" << endl;
	{
		map<unsigned, string> phonePad = 
		{ 
			{ 0, string() }, { 1, "*#" },
			{ 2, "ABC" }, { 3, "DEF" }, { 4, "GHI" }, { 5, "JKL" }, 
			{ 6, "MNO" }, { 7, "PQRS" }, { 8, "TUV" }, { 9, "WXYZ" }
		};
		vector<vector<unsigned>> testPpmc =
		{
			{},
			{ 1 },
			{ 2 },
			{ 2, 2 },
			{ 2, 3, 4 },
			{ 2, 7, 1 },
			{ 3, 7, 8, 9 },
			//{ 5, 5, 5, 7, 2, 9, 3 }
		};
		for (unsigned i = 0; i < testPpmc.size(); ++i)
		{
			string input;
			for (auto it = testPpmc[i].cbegin(); it != testPpmc[i].cend(); ++it)
			{
				input += to_string(*it) + (it != testPpmc[i].cend() - 1 ? ", " : "");
			}
			cout << "[" << input << "]: ";
			auto result = Combinatorics::PhoneMnemonics(testPpmc[i], phonePad);
			string output;
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				output += *it + (it != result.cend() - 1 ? ", " : "");
			}
			cout << output << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

