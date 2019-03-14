//
// Linear operations: array and matrix problems
//

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Linear.h"

using namespace std;

int main()
{
	cout << "== Linear ==" << endl << endl;

	cout << "- Sudoku Checker -" << endl;
	{
		vector<vector<vector<unsigned>>> testSudoku =
		{ 
			{
				{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
				{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
				{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
				{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
				{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
				{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
				{ 0, 6, 0, 0, 0, 0, 2, 8, 0 },
				{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
				{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
			} 
		};
		for (auto&& test : testSudoku)
		{
			cout << "Source (" + to_string(test.size()) + "*" + to_string(test[0].size()) + "): " << endl;
			for (auto row = test.cbegin(); row != test.cend(); ++row)
			{
				for (auto it = row->cbegin(); it != row->cend(); ++it)
				{
					cout << setiosflags(ios::right) << setw(2) << *it << (it != row->cend() - 1 ? " " : "");
				}
				cout << endl;
			}
			auto result = Linear::SudokuChecker(test);
			auto verdict = result.first + result.second > 0 ? " - errors" : " - valid";
			cout << "Result: (" << result.first << ", " << result.second << ")" << verdict << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}
