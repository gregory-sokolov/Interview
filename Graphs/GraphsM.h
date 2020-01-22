#pragma once

#include <utility>
#include <limits>
#include <iterator>
#include <functional>
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
		std::queue<MazeCell> qmc({ start });
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

	/// EPI 16.10.1. Shortest Path (Dijkstra Algorithm)
	/// Implements standard Dijkstra algorithm to find the shortest path from one specified graph vertex to all other vertices.
	/// Starting from the initial node, we mark adjacent nodes down with their minimal weights (distances):
	/// new_weight = min(old_weight, edge_cost + init_weight)
	/// Each new iteration looks up the adjacent node with the minimal weight.
	/// Once all node neighbours are considered, the node is marked as visited. The algorithm stops when all nodes are visited.
	/// The implementation below uses minimum-heap to store already marked nodes for the fastest access to the minimal value on the heap's top.
	/// Newly calculated weights for nodes are not updated but just added to the existing weight-index pairs (since 'update' is not allowed in standard heap).
	/// The duplicates with bigger values downfall somewhere to the bottom of the heap and don't go to the resulting node set.
	/// They are removed later when discovered as duplicates against the results.
	/// Time: O(E*log(V)), space: O(V^2)
	struct Vertex
	{
		unsigned weight = std::numeric_limits<unsigned>::max();
		bool visited = false;
	};

	static std::vector<unsigned> ShortestPath(const std::vector<std::vector<unsigned>>& mx)
	{
		unsigned n = mx[0].size();
		constexpr unsigned max = std::numeric_limits<unsigned>::max();
		std::vector<unsigned> result(n, max);
		std::priority_queue<std::pair<unsigned, unsigned>, std::vector<std::pair<unsigned, unsigned>>,
			std::greater<std::pair<unsigned, unsigned>>> min_heap;
		min_heap.push(std::make_pair(0, 0));

		while (!min_heap.empty())
		{
			auto vx = min_heap.top();
			if (result[vx.second] == max)
			{
				auto adj = mx[vx.second];
				for (unsigned i = 0; i < adj.size(); ++i)
				{
					if (adj[i] > 0 && result[i] == max)
					{
						min_heap.push(std::make_pair(vx.first + adj[i], i));
					}
				}
				result[vx.second] = vx.first;
			}
			min_heap.pop();
		}

		for (unsigned i = 0; i < result.size(); ++i)
		{
			result[i] = result[i] == max ? 0 : result[i];
		}
		return result;
	}
};