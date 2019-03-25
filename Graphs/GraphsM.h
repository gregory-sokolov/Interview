#pragma once

#include <utility>
#include <vector>
#include <queue>

///
/// Graph as adjacency matrix
///
class GraphsM
{
public:
	/// EPI 16.1. Searching a maze
	/// Time: O(n), space: O(1)
	enum CellType { Path = 0, Block = 1, Start = 7, Exit = 9 };
	struct MazeCell
	{
		MazeCell() = default;
		MazeCell(unsigned r, unsigned c) : row(r), col(c) {}
		unsigned row = 0;
		unsigned col = 0;
	};
	static std::vector<std::pair<int, int>> SearchMaze(const std::vector<std::vector<int>>& mx)
	{
		unsigned rows = mx.size(), cols = mx[0].size();

		MazeCell start;
		std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols));
		for (unsigned i = 0; i < rows; ++i)
		{
			for (unsigned j = 0; j < cols; ++j)
			{
				visited[i][j] = mx[i][j] == CellType::Block || mx[i][j] == CellType::Start;
				if (mx[i][j] == CellType::Start)
				{
					start.row = i;
					start.col = j;
				}
			}
		}

		std::vector<std::pair<int, int>> result;
		std::queue<MazeCell> qmc;
		qmc.push(start);
		while (!qmc.empty())
		{
			auto cell = qmc.front();
			qmc.pop();
			result.push_back(std::make_pair(cell.row, cell.col));

			if (mx[cell.row][cell.col] == CellType::Exit)
			{
				break;
			}

			if (cell.col < cols - 1 && !visited[cell.row][cell.col + 1])
			{
				qmc.push(MazeCell(cell.row, cell.col + 1));
				visited[cell.row][cell.col + 1] = true;
			}
			if (cell.row < rows - 1 && !visited[cell.row + 1][cell.col])
			{
				qmc.push(MazeCell(cell.row + 1, cell.col));
				visited[cell.row + 1][cell.col] = true;
			}
			if (cell.col > 0 && !visited[cell.row][cell.col - 1])
			{
				qmc.push(MazeCell(cell.row, cell.col - 1));
				visited[cell.row][cell.col - 1] = true;
			}
			if (cell.row > 0 && !visited[cell.row - 1][cell.col])
			{
				qmc.push(MazeCell(cell.row - 1, cell.col));
				visited[cell.row - 1][cell.col] = true;
			}
		}

		return result;
	}
};