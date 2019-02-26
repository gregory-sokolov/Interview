/// 
/// Combinatorial Problems
///

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

#include "Combinatorics.h"

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Combinatorics ==" << endl << endl;

	cout << "- Permutations -" << endl;
	{
		vector<vector<unsigned>> results1;
		unsigned* pmt0 = NULL;
		cout << "Permutation input: (empty)" << endl;
		Combinatorics::PermutationsR(pmt0, 0, 0, results1);
		cout << "Permutation count: " << results1.size() << endl;
		cout << "Permutations: ";
		for (auto it = results1.begin(); it < results1.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}

		unsigned pmti[] = { 1, 2, 3, 4 };
		cout << "Permutation input: ";
		copy(pmti, pmti + sizeof(pmti) / sizeof(int), ostream_iterator<unsigned>(cout));
		cout << endl;
		Combinatorics::PermutationsR(pmti, sizeof(pmti) / sizeof(unsigned), sizeof(pmti) / sizeof(unsigned), results1);
		cout << "Permutation count: " << results1.size() << endl;
		cout << "Permutations: ";
		for (auto it = results1.begin(); it < results1.end(); ++it)
		{
			copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

