#pragma once

#include <utility>
#include <vector>
#include <algorithm>
#include <cmath>
#include <limits>

///
/// Linear operations: array and matrix problems
///
class Linear
{
public:
	/// EPI 6.3. Max difference
	/// Finds maximum difference between array elements a[i] and a[j], so that j > i.
	/// Search maximum value moving forward the array, then search the minimum going backward from that point.   
	/// Time: O(n), space: O(1)
	static unsigned MaxDiff(const std::vector<unsigned>& a)
	{
		if (a.empty())
		{
			return 0;
		}

		unsigned max = 0, imax = 0;
		for (unsigned i = 0; i < a.size(); ++i)
		{
			if (a[i] > max)
			{
				max = a[i];
				imax = i;
			}
		}

		unsigned min = a[0];
		if (imax > 0)
		{
			min = std::numeric_limits<unsigned>::max();
			for (int i = imax - 1; i >= 0; --i)
			{
				min = a[i] < min ? a[i] : min;
			}
		}

		return max - min;
	}

	/// EPI 6.14.1. Sudoku checker
	/// Checks that input board matrix is a valid Sudoku assignment.
	/// Tedious duplicate checking problem in a matrix line by line.
	/// Firstly, check duplicates in all rows, then in all columns, and finally in all 3x3 sections.
	/// To generalize checking procedure, for column check the matrix is transposed, 
	/// for section check all sections are unfolded into lines with tricky index formula.
	/// Time: O(n), space: O(n)
	static std::pair<int, int> SudokuChecker1(const std::vector<std::vector<unsigned>>& board)
	{
		unsigned section = (unsigned)std::sqrt(board.size());
		if (board.empty() ||
			board.size() != board[0].size() ||
			section*section != board.size())
		{
			return std::make_pair(-1, -1);
		}

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
			result = std::make_pair(result.second, result.first);

			if (result.first == 0 && result.second == 0)
			{
				for (unsigned i = 0; i < board.size(); ++i)
				{
					for (unsigned j = 0; j < board[0].size(); ++j)
					{
						modified[section*(i/section) + j/section][section*(i%section) + j%section] = board[i][j];
						
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

	/// EPI 6.14.2 Sudoku checker
	/// Does the same check with less space (bit vector, no matrix copying) but with code duplication.
	/// Uses another method of section check.
	/// Time: O(n), space: O(1)
	static std::pair<int, int> SudokuChecker2(const std::vector<std::vector<unsigned>>& board)
	{
		unsigned section = (unsigned)std::sqrt(board.size());
		if (board.empty() ||
			board.size() != board[0].size() ||
			section * section != board.size())
		{
			return std::make_pair(-1, -1);
		}

		std::pair<int, int> result(0, 0);
		std::vector<bool> check(10, false);
		for (unsigned i = 0; i < board.size(); ++i)
		{
			std::fill(check.begin(), check.end(), false);
			for (unsigned j = 0; j < board[0].size(); ++j)
			{
				if (board[i][j] > 0 && check[board[i][j]])
				{
					return std::make_pair(i + 1, j + 1);
				}
				else
				{
					check[board[i][j]] = true;
				}
			}
		}
		for (unsigned i = 0; i < board[0].size(); ++i)
		{
			std::fill(check.begin(), check.end(), false);
			for (unsigned j = 0; j < board.size(); ++j)
			{
				if (board[j][i] > 0 && check[board[j][i]])
				{
					return std::make_pair(j + 1, i + 1);
				}
				else
				{
					check[board[j][i]] = true;
				}
			}
		}
		for (unsigned I = 0; I < section; ++I)
		{
			for (unsigned J = 0; J < section; ++J)
			{
				std::fill(check.begin(), check.end(), false);
				for (unsigned i = 0; i < section; ++i)
				{
					for (unsigned j = 0; j < section; ++j)
					{
						if (board[section*I + i][section*J + j] > 0 && check[board[section*I + i][section*J + j]])
						{
							return std::make_pair(section*I + i + 1, section*J + j + 1);
						}
						else
						{
							check[board[section*I + i][section*J + j]] = true;
						}
					}
				}
			}
		}

		return result;
	}
};
