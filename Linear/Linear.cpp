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

	cout << "- Max difference -" << endl;
	{
		vector<vector<unsigned>> testMaxDiff =
		{
			{},
			{ 0 },
			{ 9 },
			{ 0, 0 },
			{ 0, 9 },
			{ 9, 0 },
			{ 9, 9 },
			{ 2, 1, 0, 5, 6, 4, 9, 3, 1, 4, 1, 0 }
		};
		for (unsigned i = 0; i < testMaxDiff.size(); ++i)
		{
			auto test = testMaxDiff[i];
			unsigned result = Linear::MaxDiff(test);
			cout << "Test " << i + 1 << ": " << result << ", input: ";
			for (auto it = test.cbegin(); it != test.cend(); ++it)
			{
				cout << *it << (it != test.cend() - 1 ? ", " : "");
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "- Sudoku Checker -" << endl;
	{
		vector<vector<vector<unsigned>>> testSudoku =
		{
			{ {} },
			{ { 9 } },
			{
				{ 5, 3, 0, 0 },
				{ 6, 0, 0, 1 },
				{ 0, 9, 8, 0 },
				{ 8, 0, 0, 0 }
			},
			{
				{ 5, 3, 0, 0, 7 },
				{ 6, 0, 0, 1, 9 },
				{ 0, 9, 8, 0, 0 },
				{ 8, 0, 0, 0, 6 },
				{ 4, 0, 0, 8, 0 }
			},
			{
				{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
				{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
				{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
				{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
				{ 4, 0, 0, 8, 0, 3, 0, 0, 1 }
			},
			{
				{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
				{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
				{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
				{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
				{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
				{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
				{ 0, 6, 0, 0, 1, 0, 2, 8, 0 },
				{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
				{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
			},
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
			auto result1 = Linear::SudokuChecker1(test);
			auto result2 = Linear::SudokuChecker2(test);
			if (result1.first == result2.first && result1.second == result2.second)
			{
				auto result = result2;
				auto verdict = result.first == 0 && result.second == 0 ? " - valid" :
					(result.first < 0 && result.second < 0 ? " - input error" : " - invalid");
				cout << "Result: (" << result.first << ", " << result.second << ")" << verdict << endl;
			}
			else
			{
				cout << "Mismatching results: (" << result1.first << ", " << result1.second <<
					"), (" << result2.first << ", " << result2.second << ")" << endl;
			}
		}
	}
	cout << endl;

	cout << "- Spiral Order -" << endl;
	{
		vector<vector<vector<unsigned>>> testSpiral =
		{
			{ {} },
			{ { 9 } },
			{ { 9, 1 } },
			{ 
				{ 9, 1 },
				{ 2, 7 }
			},
			{
				{ 9, 1, 5 },
				{ 2, 7, 3 },
				{ 4, 8, 0 }
			},
			{
				{ 5, 3, 0, 9 },
				{ 6, 7, 0, 1 },
				{ 0, 9, 8, 0 },
				{ 8, 0, 1, 4 }
			},
			{
				{ 5, 3, 0, 0, 7 },
				{ 6, 0, 0, 1, 9 },
				{ 0, 9, 8, 0, 0 },
				{ 8, 0, 0, 0, 6 },
				{ 4, 0, 0, 8, 0 }
			},
			{
				{ 5, 3, 0, 0, 7, 0, 0, 0, 9 },
				{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
				{ 0, 9, 8, 0, 1, 2, 4, 6, 0 },
				{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
				{ 4, 0, 0, 8, 0, 3, 0, 0, 1 }
			},
			{
				{ 5, 3, 0, 0, 7 },
				{ 6, 0, 0, 1, 9 },
				{ 0, 9, 8, 0, 0 },
				{ 8, 0, 0, 0, 6 },
				{ 4, 0, 0, 8, 0 },
				{ 5, 0, 2, 9, 1 },
				{ 6, 1, 4, 1, 0 },
				{ 7, 3, 6, 2, 5 },
				{ 8, 5, 8, 3, 9 }
			},
			{
				{ 5, 3, 0, 0, 7, 0, 0, 0, 0 },
				{ 6, 0, 0, 1, 9, 5, 0, 0, 0 },
				{ 0, 9, 8, 0, 0, 0, 0, 6, 0 },
				{ 8, 0, 0, 0, 6, 0, 0, 0, 3 },
				{ 4, 0, 0, 8, 0, 3, 0, 0, 1 },
				{ 7, 0, 0, 0, 2, 0, 0, 0, 6 },
				{ 0, 6, 0, 0, 1, 0, 2, 8, 0 },
				{ 0, 0, 0, 4, 1, 9, 0, 0, 5 },
				{ 0, 0, 0, 0, 8, 0, 0, 7, 9 }
			}
		};
		for (auto&& test : testSpiral)
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
			auto result = Linear::SpiralizeMatrix(test);
			cout << "Result (" + to_string(result.size()) + "): ";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << *it << (it != result.cend() - 1 ? " " : "");
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}
