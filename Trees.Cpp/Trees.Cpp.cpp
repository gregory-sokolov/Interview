/// 
/// EPI. Chapter 9. Trees
///

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>

#include "Trees.h"
#include "TreeHelper.h"

using namespace std;

///
/// Tree testing program
///
int main()
{
	cout << "== Binary Trees ==" << endl;
	{
		BSTree<int> t1;
		vector<int> init = { 8, 4, 2, 1, 6, 5, 16, 7, 12, 20, 24 };
		for (auto&& vi : init) t1.Insert(vi);

		cout << "Pre-order (original):  ";
		NodePrinter<int> np1;
		t1.TraversePreOrder(np1);
		np1.print();

		cout << "In-order:  ";
		NodePrinter<int> np2;
		t1.TraverseInOrder(np2);
		np2.print();

		cout << "Post-order: ";
		NodePrinter<int> np3;
		t1.TraversePostOrder(np3);
		np3.print();

		cout << "Min value: " << t1.GetMin() << endl;
		cout << "Max value: " << t1.GetMax() << endl;

		bool b1 = t1.HasValue(init[7]);
		auto b2 = t1.Dfs([&init](int value) { return value == init[7]; });
		cout << "Value " << init[7] << " is in the tree: " << (b1 ? "true" : "false") << " (Search), " <<
			(b2 != NULL && *b2 == init[7] ? "true" : "false") << " (DFS)" << endl;
		int n = 13;
		b1 = t1.HasValue(n);
		b2 = t1.Dfs([n](int value) { return value == n; });
		cout << "Value " << n << " is in the tree: " << (b1 ? "true" : "false") << " (Search), " <<
			(b2 != NULL && *b2 == n ? "true" : "false") << " (DFS)" << endl;

		bool is = t1.IsBsTree();
		cout << "Is binary search tree: " << (is ? "true" : "false") << endl;

		cout << "In breadth: ";
		NodePrinter<int> np4;
		t1.TraverseInBreadth(np4);
		np4.print();

		cout << "Mirrored: ";
		BSTree<int> t2(t1);
		t2.Mirror();
		NodePrinter<int> np5;
		t2.TraverseInOrder(np5);
		np5.print();

		cout << "All paths: ";
		PathFinder<int> pf1;
		t1.AllPaths(pf1);
		pf1.print();

		cout << "LCA: ";
		vector<pair<int, int>> nodes = { make_pair(1, 4), make_pair(6, 7), make_pair(16, 24), make_pair(7, 24),
			make_pair(4, 35), make_pair(0, 20), make_pair(29, 11), make_pair(48, 90), make_pair(0, 100) };
		for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
		{
			auto lca = t1.SearchLca(ni->first, ni->second);
			cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
				(ni != nodes.end() - 1 ? ", " : "");
		}
		cout << endl;

		cout << "LCA 1 (non-BST): ";
		for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
		{
			auto lca = t1.SearchLcaNbst1(ni->first, ni->second);
			cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
				(ni != nodes.end() - 1 ? ", " : "");
		}
		cout << endl;

		cout << "LCA 2 (non-BST): ";
		for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
		{
			PairChecker<int> pc1(ni->first, ni->second);
			auto lca = t1.SearchLcaNbst2(pc1);
			cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
				(ni != nodes.end() - 1 ? ", " : "");
		}
		cout << endl;
	}

	cout << endl;
	system("PAUSE");
    return 0;
}

