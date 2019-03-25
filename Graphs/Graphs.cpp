///
/// EPI 16. Graph Problems
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "GraphsM.h"
#include "GraphsV.h"
#include "GraphHelper.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Graphs ==" << endl;
	{
		Graph<char, int> g1;
		vector<pair<pair<char, char>, int>> init1 =
		{
			make_pair(make_pair('a', 'b'), 3), make_pair(make_pair('a', 'c'), 2), make_pair(make_pair('c', 'b'), 1),
			make_pair(make_pair('b', 'd'), 4), make_pair(make_pair('b', 'd'), 4), make_pair(make_pair('b', 'd'), 5),
			make_pair(make_pair('f', 'e'), 1), make_pair(make_pair('e', 'd'), 3),
			make_pair(make_pair('g', 'h'), 7), make_pair(make_pair('i', 'h'), 9),
		};
		for (auto&& vi : init1)
		{
			g1.AddEdge(vi.first.first, vi.first.second, vi.second);
		}
		g1.AddVertex('k');

		cout << "- Depth-first traversal (DFS) -" << endl;
		{
			GraphVertexPrinter<char, int> gvp1;
			g1.Dfs(gvp1);
			gvp1.print();
		}
		cout << endl;

		cout << "- Breadth-first traversal (BFS) -" << endl;
		{
			GraphVertexPrinter<char, int> gvp2;
			g1.Bfs(gvp2);
			gvp2.print();
		}
		cout << endl;

		cout << "- Cloning a graph -" << endl;
		{
			Graph<char, int> g2(g1);
			GraphVertexPrinter<char, int> gvp3;
			g2.Dfs(gvp3);
			gvp3.print();
		}
		cout << endl;

		cout << "- Searching a maze -" << endl;
		{
			vector<vector<int>> testMaze = 
			{
				{ 1, 1, 0, 0, 9 },
				{ 1, 0, 0, 1, 0 },
				{ 1, 0, 1, 1, 0 },
				{ 0, 0, 0, 1, 0 },
				{ 1, 0, 0, 0, 0 },
				{ 7, 0, 1, 0, 1 }
			};
			auto result = GraphsM::SearchMaze(testMaze);
			cout << "Maze: (" + to_string(testMaze.size()) + "*" + to_string(testMaze[0].size()) + "): " << endl;
			for (auto row = testMaze.cbegin(); row != testMaze.cend(); ++row)
			{
				for (auto it = row->cbegin(); it != row->cend(); ++it)
				{
					cout << setiosflags(ios::right) << setw(2) << *it << (it != row->cend() - 1 ? " " : "");
				}
				cout << endl;
			}
			cout << "Path (" << result.size() << "): ";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << it->first << "," << it->second << (it != result.cend() - 1 ? " - " : "");
			}
			cout << endl;

		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

