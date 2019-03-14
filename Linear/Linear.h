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
	/// Time: O(n), space: O(n)
	static std::pair<unsigned, unsigned> SudokuChecker(const std::vector<std::vector<unsigned>>& board, unsigned section)
	{
		std::pair<unsigned, unsigned> result(0, 0);

		bool found = false;
		std::vector<unsigned> check(10, 0);
		for (unsigned i = 0; i < board.size(); ++i)
		{
			std::fill(check.begin(), check.end(), 0);
			for (unsigned j = 0; j < board[0].size(); ++j)
			{
				if (board[i][j] > 0 && ++check[board[i][j]] > 1)
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

		if (!found)
		{
			// @TODO: replace with transposing
			for (unsigned i = 0; i < board[0].size(); ++i)
			{
				std::fill(check.begin(), check.end(), 0);
				for (unsigned j = 0; j < board.size(); ++j)
				{
					if (board[j][i] > 0 && ++check[board[j][i]] > 1)
					{
						result = std::make_pair(j + 1, i + 1);
						found = true;
						break;
					}
				}
				if (found)
				{
					break;
				}
			}
		}

		std::vector<std::vector<unsigned>> unfolded(board.size(), std::vector<unsigned>(board[0].size()));
		unsigned size = board.size();
		for (unsigned i = 0; i < board.size(); ++i)
		{
			std::fill(check.begin(), check.end(), 0);
			for (unsigned j = 0; j < board[0].size(); ++j)
			{
				//unsigned k = (j/section)*section + j; 012, 345
				//unfolded[(i/section) (j/section)][(j/section) ] = board[i][j];
			}
		}
		for (unsigned i = 0; i < unfolded.size(); ++i)
		{
			std::fill(check.begin(), check.end(), 0);
			for (unsigned j = 0; j < unfolded[0].size(); ++j)
			{
				if (unfolded[i][j] > 0 && ++check[unfolded[i][j]] > 1)
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
