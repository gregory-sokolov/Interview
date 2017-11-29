// Graphs.Cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Graphs.h"
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

		cout << "DFT: ";
		GraphVertexPrinter<char, int> gvp1;
		g1.Dfs(gvp1);
		gvp1.print();

		cout << "BFT: ";
		GraphVertexPrinter<char, int> gvp2;
		g1.Bfs(gvp2);
		gvp2.print();

		cout << "Copy (DFT): ";
		Graph<char, int> g2(g1);
		GraphVertexPrinter<char, int> gvp3;
		g2.Dfs(gvp3);
		gvp3.print();
	}
	cout << endl;

	cout << "Program has completed" << endl;
	system("PAUSE");
	return 0;
}

