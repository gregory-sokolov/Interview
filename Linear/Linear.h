#pragma once

#include <utility>
#include <vector>
#include <algorithm>

///
/// Linear operations: array and matrix problems
///
class Linear
{
public:
	/// EPI 6.14. Sudoku checker
	/// Checks that input board matrix is a valid Sudoku assignment.
	/// Tedious duplicate checking problem in a matrix line by line.
	/// Firstly, check duplicates in all rows, then in all columns, and finally in all 3x3 sections.
	/// To generalize checking procedure, for column check the matrix is transposed, 
	/// for section check all sections are unfolded into lines with tricky index formula.
	/// Time: O(n), space: O(n)
	static std::pair<unsigned, unsigned> SudokuChecker(const std::vector<std::vector<unsigned>>& board)
	{
		auto result = CheckSudokuLines(board);
		if (result.first == 0 && result.second == 0)
		{
			std::vector<std::vector<unsigned>> modified(board.size(), std::vector<unsigned>(board[0].size()));
			for (unsigned i = 0; i < board.size(); ++i)
			{
				for (unsigned j = 0; j < board[0].size(); ++j)
				{
					modified[i][j] = board[j][i];
				}
			}
			result = CheckSudokuLines(modified);

			if (result.first == 0 && result.second == 0)
			{
				for (unsigned i = 0; i < board.size(); ++i)
				{
					for (unsigned j = 0; j < board[0].size(); ++j)
					{
						modified[3*(i/3) + j/3][3*(i%3) + j%3] = board[i][j];
						
					}
				}
				result = CheckSudokuLines(modified);
			}
		}

		return result;
	}
	/// Helper method to check Sudoku validity by lines
	static std::pair<int, int> CheckSudokuLines(const std::vector<std::vector<unsigned>>& mx)
	{
		std::pair<int, int> result(0, 0);

		std::vector<unsigned> check(10, 0);
		bool found = false;
		for (unsigned i = 0; i < mx.size(); ++i)
		{
			std::fill(check.begin(), check.end(), 0);
			for (unsigned j = 0; j < mx[0].size(); ++j)
			{
				if (mx[i][j] > 0 && ++check[mx[i][j]] > 1)
				{
					result = std::make_pair(i + 1, j + 1);
					found = true;
					break;
				}
			}
			if (found)
			{
				break;
			}
		}

		return result;
	}
};
