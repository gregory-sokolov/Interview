#pragma once

#include <vector>
#include <deque>
#include <queue>
#include <limits>
#include <algorithm>

#include "Tree.h"
#include "TreeBst.h"

///
/// Tree Problems
///
class Trees
{
public:
	/// Depth-first search (DFS)
	/// Time: O(V) - all nodes are visited, space: O(h), h - tree height
	template<typename T, typename V>
	static TreeNode<T>* DfsR(TreeNode<T>* node, V& visit)
	{
		TreeNode<T>* result = nullptr;
		if (node != nullptr)
		{
			if (visit(node->data))
			{
				result = node;
			}
			else
			{
				result = DfsR(node->left, visit);
				if (result == nullptr)
				{
					result = DfsR(node->right, visit);
				}
			}
		}

		return result;
	}

	/// Depth-first search of a specific value
	template<typename T>
	static TreeNode<T>* DfsValueR(TreeNode<T>* tn, T& value)
	{
		if (tn)
		{
			if (value < tn->data) return DfsValueR(tn->left, value);
			else if (value > tn->data) return DfsValueR(tn->right, value);
		}
		return tn;
	}

	/// Mirrors a tree
	template<typename T>
	static void MirrorR(TreeNode<T>* tn)
	{
		if (tn)
		{
			if (tn->left || tn->right)
			{
				TreeNode<T>* t = tn->left;
				tn->left = tn->right;
				tn->right = t;
			}

			MirrorR(tn->left);
			MirrorR(tn->right);
		}
	}

	/// Checks if the tree is a BST
	public: template<typename T>
	static bool IsBst(TreeNode<T>* root)
	{
		return IsBstR(root, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
	}
	private: template<typename T>
	static bool IsBstR(TreeNode<T>* tn, T min, T max)
	{
		bool result = true;
		if (tn != nullptr)
		{
			result = tn->data > min&& tn->data <= max;
			if (result && tn->left != nullptr)
			{
				result = tn->left->data <= tn->data ? IsBstR(tn->left, min, tn->data) : false;
			}
			if (result && tn->right != nullptr)
			{
				result = tn->right->data > tn->data ? IsBstR(tn->right, tn->data, max) : false;
			}
		}

		return result;
	}

	/// EPI 9.7/EPI 14.7/Leetcode 108. Reconstructing BST from a sorted array
	/// Recursive solution: selects a pivot median in the input array, sets it to the current node and
	/// continues with the left and right parts of the array.
	/// Time: O(n) - traverse the array, space: O(log(n)) - height of the tree in recursion
	public:	template<typename T>
	static TreeNode<T>* ConstructTree(const std::vector<int>& a)
	{
		TreeNode<T>* root = InsertR<T>(a, 0, a.size());
		return root;
	}
	private: template<typename T>
	static TreeNode<T>* InsertR(const std::vector<int>& a, int start, int end)
	{
		TreeNode<T>* tn = nullptr;
		if (start < end)
		{
			int median = start + (end - start)/2;
			tn = new TreeNode<T>(a[median]);
			tn->left = InsertR<T>(a, start, median);
			tn->right = InsertR<T>(a, median + 1, end);
		}

		return tn;
	}

	/// Leetcode 104. Finds max tree depth
	public: static unsigned MaxDepth(TreeNode<int>* tn)
	{
		return tn ? std::max(MaxDepth(tn->left), MaxDepth(tn->right)) + 1 : 0;
	}

	/// Finds paths with max and min sum
	static std::pair<int, int> minMaxPathR(TreeNode<int>* tn)
	{
		int min = 0, max = 0;
		if (tn)
		{
			auto pl = minMaxPathR(tn->left);
			auto pr = minMaxPathR(tn->right);
			min = std::min(pl.first + tn->data, pr.first + tn->data);
			max = std::max(pl.second + tn->data, pr.second + tn->data);
		}

		return std::make_pair(min, max);
	}

	/// Constructs a vector with all tree paths using DFS
	public: static std::vector<std::deque<int>> AllPaths(TreeNode<int>* root)
	{
		std::vector<std::deque<int>> result;
		std::deque<int> path;
		AllPathsR(root, path, result);

		return result;
	}
	private: static void AllPathsR(TreeNode<int>* tn, std::deque<int>& dq, std::vector<std::deque<int>>& result)
	{
		if (tn != nullptr)
		{
			dq.push_back(tn->data);
			if (tn->left == nullptr && tn->right == nullptr)
			{
				result.push_back(dq);
			}
			else
			{
				AllPathsR(tn->left, dq, result);
				AllPathsR(tn->right, dq, result);
			}
			dq.pop_back();
		}
	}

	/// Leetcode 230. K-th Smallest Element
	public: static int kthSmallest(TreeNode<int>* root, int k)
	{
		unsigned count = 0;
		auto node = kthSmallestR(root, k, count);

		return node->data;
	}
	private: static TreeNode<int>* kthSmallestR(TreeNode<int>* tn, int k, unsigned& count)
	{
		TreeNode<int>* result = nullptr;
		if (tn)
		{
			result = kthSmallestR(tn->left, k, count);
			if (!result)
			{
				if (++count == k)
				{
					return tn;
				}
				result = kthSmallestR(tn->right, k, count);
			}
		}

		return result;
	}

	/// Breadth-first search/traversal (BFS)
	/// Time: O(V) - every node is visited once, space: O(V) - holding all nodes in the queue in worst case
	/// In contrast with graphs, where time complexity is O(V + E), for trees the O(E) factor is redundant.
	public: template<typename T, typename V>
	static void Bfs(TreeNode<T>* root, V& visit)
	{
		TreeNode<T>* tn = root;
		std::queue<TreeNode<T>*> qtn({ tn });

		while (!qtn.empty())
		{
			tn = qtn.front();
			qtn.pop();

			if (tn != nullptr)
			{
				visit(tn->data);
				qtn.push(tn->left);
				qtn.push(tn->right);
			}
		}
	}

	/// Breadth-first traversal with by-level visiting (BFSL)
	template<typename T, typename V>
	static void BfsByLevel(TreeNode<T>* root, V& visit)
	{
		std::queue<TreeNode<T>*> qtn({ root });
		std::vector<TreeNode<T>*> vlv = { root };
		visit(vlv);
		vlv.clear();

		while (!qtn.empty())
		{
			TreeNode<T>* tn = qtn.front();
			qtn.pop();
			if (tn != nullptr)
			{
				vlv.push_back(tn->left);
				vlv.push_back(tn->right);
			}

			if (qtn.empty() && !vlv.empty())
			{
				visit(vlv);
				for (auto&& vi : vlv)
				{
					qtn.push(vi);
				}
				vlv.clear();
			}
		}
	}

	/// Leetcode 116. Populating next right pointers in each node
	template<typename T>
	static void SetNextPointers(TreeNode<T>* root)
	{
		if (!root) return;
		
		std::queue<TreeNode<T>*> q;
		q.push(root);

		while (!q.empty())
		{
			std::vector<TreeNode<T>*> vlv;
			while (!q.empty())
			{
				vlv.push_back(q.front());
				q.pop();
			}

			for (unsigned i = 0; i < vlv.size(); ++i)
			{
				vlv[i]->other = i < vlv.size() - 1 ? vlv[i + 1] : nullptr;
				if (vlv[i]->left)
				{
					q.push(vlv[i]->left);
				}
				if (vlv[i]->right)
				{
					q.push(vlv[i]->right);
				}
			}
		}
	}

	/// EPI 14.13. Lowest Common Ancestor on BST (LCA) 
	public: template<typename T>
	static TreeNode<T>* LcaBstR(TreeNode<T>* node, T& v1, T& v2)
	{
		TreeNode<T>* result = nullptr;
		if (node != nullptr)
		{
			if (std::max(v1, v2) < node->data)
			{
				result = LcaBstR(node->left, v1, v2);
			}
			else if (std::min(v1, v2) > node->data)
			{
				result = LcaBstR(node->right, v1, v2);
			}
			else
			{
				result = node;
			}
		}

		return result;
	}

	/// EPI 9.11. Lowest Common Ancestor on non-BST (LCA) 
	/// First simple algorithm. 
	/// Time: O(n), space: O(1)
	template<typename T>
	static TreeNode<T>* LcaNbst1R(TreeNode<T>* node, T& v1, T& v2)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		else if (node->data == v1 || node->data == v2)
		{
			return node;
		}

		TreeNode<T>* left = LcaNbst1R(node->left, v1, v2);
		TreeNode<T>* right = LcaNbst1R(node->right, v1, v2);

		if (left != nullptr && right != nullptr)
		{
			return node;
		}
		else
		{
			return left != nullptr ? left : right;
		}
	}

	/// Second algorithm with pair checking.
	template<typename T, typename C>
	static TreeNode<T>* LcaNbst2R(TreeNode<T>* node, C& check)
	{
		TreeNode<T>* result = node;
		if (node != nullptr)
		{
			check.Reset();
			check(node->data);
			if (check.HasNone())
			{
				DfsR(node->left, check);
				if (check.HasAll())
				{
					result = LcaNbst2R(node->left, check);
				}
				else if (check.HasNone())
				{
					result = LcaNbst2R(node->right, check);
				}
				else
				{
					result = node;
				}
			}
		}

		return result;
	}
};



