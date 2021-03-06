/// 
/// Tree Problems
///

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>

#include "Tree.h"
#include "Trie.h"
#include "TreeBst.h"
#include "TreeHelper.h"
#include "Trees.h"

using namespace std;

int main()
{
	cout << "== Binary Trees ==" << endl;
	{
		BSTree<int> bst1;
		vector<int> init1 = { 8, 4, 2, 1, 6, 5, 16, 7, 12, 20, 24 };
		for (const auto& vi : init1) { bst1.Insert(vi); }
		auto root = bst1.GetRoot();

		BSTree<int> bstPerf;
		vector<int> init2 = { 8, 4, 2, 1, 3, 6, 5, 16, 7, 12, 10, 20, 18, 14, 24 };
		for (const auto& vi : init2) { bstPerf.Insert(vi); }
		auto rootPerf = bstPerf.GetRoot();

		cout << "- Traversal Orders -" << endl;
		{
			cout << "Pre-order (original):  ";
			NodePrinter<int> np1;
			bst1.TraversePreOrder(np1);
			np1.print();

			cout << "In-order:  ";
			NodePrinter<int> np2;
			bst1.TraverseInOrder(np2);
			np2.print();

			cout << "Post-order: ";
			NodePrinter<int> np3;
			bst1.TraversePostOrder(np3);
			np3.print();
		}
		cout << endl;

		cout << "- Value Detection -" << endl;
		{
			cout << "Min value: " << bst1.GetMin() << endl;
			cout << "Max value: " << bst1.GetMax() << endl;

			bool b1 = Trees::DfsValueR(root, init1[7]);
			auto b2 = Trees::DfsR(root, [&init1](int value) { return value == init1[7]; });
			cout << "Value: " << init1[7] << ", found: " << (b1 ? "true" : "false") << " (DFS by value), " <<
				(b2 != nullptr && b2->data == init1[7] ? "true" : "false") << " (DFS general)" << endl;
			int n = 13;
			b1 = Trees::DfsValueR(root, n);
			b2 = Trees::DfsR(root, [n](int value) { return value == n; });
			cout << "Value: " << n << ", found: " << (b1 ? "true" : "false") << " (DFS by value), " <<
				(b2 != nullptr && b2->data == n ? "true" : "false") << " (DFS general)" << endl;
		}
		cout << endl;

		cout << "- BST Check -" << endl;
		{
			bool is = Trees::IsBst(root);
			cout << "Is binary search tree: " << (is ? "true" : "false") << endl;
		}
		cout << endl;

		cout << "- BST from a sorted array -" << endl;
		{
			vector<int> vi = { -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			cout << "Input: ";
			for (unsigned i = 0; i < vi.size(); ++i)
			{
				cout << vi[i] << (i != vi.size() - 1 ? ", " : "");
			}
			cout << endl;

			auto bstRoot = Trees::ConstructTree<int>(vi);
			LevelPrinter<int> lp1;
			Trees::BfsByLevel<int, LevelPrinter<int>>(bstRoot, lp1);
		}
		cout << endl;

		cout << "- Breadth-First Search (BFS) -" << endl;
		{
			cout << "BFS: ";
			NodePrinter<int> np1;
			Trees::Bfs<int, NodePrinter<int>>(root, np1);
			np1.print();

			cout << "BFS by levels: " << endl;
			LevelPrinter<int> lp1;
			Trees::BfsByLevel<int, LevelPrinter<int>>(root, lp1);

			cout << "Next pointer: " << endl;
			Trees::SetNextPointers(rootPerf);
			NextPointerPrinter<int> npp1;
			Trees::BfsByLevel<int, NextPointerPrinter<int>>(rootPerf, npp1);
		}

		cout << "- Mirroring -" << endl;
		{
			BSTree<int> bst2(bst1);
			Trees::MirrorR(bst2.GetRoot());

			cout << "Mirrored: ";
			NodePrinter<int> np1;
			bst2.TraverseInOrder(np1);
			np1.print();
		}
		cout << endl;

		cout << "- Path Processing -" << endl;
		{
			auto maxDepth = Trees::MaxDepth(root);
			cout << "Max tree depth: " << maxDepth;
			cout << endl;

			auto minMax = Trees::minMaxPathR(root);
			cout << "Min/max path sum: {" << minMax.first << ", " << minMax.second << "}";
			cout << endl;

			cout << "All paths: ";
			auto allPaths = Trees::AllPaths(root);
			for (auto pi = allPaths.cbegin(); pi != allPaths.cend(); ++pi)
			{
				for (auto ni = pi->cbegin(); ni != pi->cend(); ++ni)
				{
					cout << *ni << (ni != pi->cend() - 1 ? "-" : "");
				}
				cout << (pi != allPaths.cend() - 1 ? ", " : "");
			}
			cout << endl;

			cout << "K-th smallest element: ";
			vector<unsigned> vk = { 2, 5, 10 };
			for (auto ki = vk.cbegin(); ki != vk.cend(); ++ki)
			{
				auto result = Trees::kthSmallest(root, *ki);
				cout << "[" << *ki << "]:" << result << (ki != vk.cend() - 1 ? ", " : "");
			}
			cout << endl;
		}
		cout << endl;

		cout << "- Lowest Common Ancestor (LCA) -" << endl;
		{
			cout << "LCA (BST): ";
			vector<pair<int, int>> nodes = { make_pair(1, 4), make_pair(6, 7), make_pair(16, 24), make_pair(7, 24),
				make_pair(4, 35), make_pair(0, 20), make_pair(29, 11), make_pair(48, 90), make_pair(0, 100) };
			for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
			{
				auto lca = Trees::LcaBstR(root, ni->first, ni->second);
				cout << "(" << ni->first << "," << ni->second << ")-" << (lca != nullptr ? to_string(lca->data) : "?") <<
					(ni != nodes.end() - 1 ? ", " : "");
			}
			cout << endl;

			cout << "LCA 1 (non-BST): ";
			for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
			{
				auto lca = Trees::LcaNbst1R(root, ni->first, ni->second);
				cout << "(" << ni->first << "," << ni->second << ")-" << (lca != nullptr ? to_string(lca->data) : "?") <<
					(ni != nodes.end() - 1 ? ", " : "");
			}
			cout << endl;

			cout << "LCA 2 (non-BST): ";
			for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
			{
				PairChecker<int> pc1(ni->first, ni->second);
				auto lca = Trees::LcaNbst2R(root, pc1);
				cout << "(" << ni->first << "," << ni->second << ")-" << (lca != nullptr ? to_string(lca->data) : "?") <<
					(ni != nodes.end() - 1 ? ", " : "");
			}
			cout << endl;
		}
		cout << endl;

		cout << "- Trie -" << endl;
		{
			Trie t1;
			vector<string> input =
			{
				"in", "inn", "inbound", "introspection", "intro",
				"it", "item",
				"team", "tea", "ten", "text",
				"the", "thy", "them", "then", "theme", "threshold",
				"to", "tone", "tomahawk"
			};
			for (const auto& word : input)
			{
				t1.Insert(word);
			}

			cout << "Checking: ";
			vector<string> tests = { "", " ", "a", "ab", "i", "in", "intro", "t", "th", "tea", "them", "theme", "themes", "therefore", "tone" };
			for (auto it = tests.begin(); it != tests.end(); ++it)
			{
				bool full = t1.Contains(*it), prefix = t1.StartsWith(*it);
				cout << (it->empty() ? "\"\"" : *it) << ":" << (int)full << ":" << (int)prefix << (it != tests.end() - 1 ? ", " : "");
			}
			cout << endl;

			cout << "Removing: ";
			vector<string> removals = { "", " ", "a", "them", "themes", "inbound" };
			for (auto it = removals.begin(); it != removals.end(); ++it)
			{
				t1.Remove(*it);
				bool full = t1.Contains(*it), prefix = t1.StartsWith(*it);
				cout << (it->empty() ? "\"\"" : *it) << ":" << (int)full << ":" << (int)prefix << (it != removals.end() - 1 ? ", " : "");
			}
			cout << endl;
		}
		cout << endl;
	}

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

