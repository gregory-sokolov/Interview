#pragma once

#include <iostream>
#include <limits>
#include <queue>
#include <deque>
#include <algorithm>

// Tree node
template<typename T>
struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	T data;

	TreeNode() : left(NULL), right(NULL) {}
	TreeNode(T value) : left(NULL), right(NULL), data(value) {}
};

// Binary search tree
template<typename T>
class BSTree
{
public:
	BSTree() : root(NULL), size(0) {}

	BSTree(const BSTree<T>& tree) : BSTree()
	{
		tree.TraversePreOrder([this](T value) { Insert(value); });
	}

	~BSTree()
	{
		// @TODO:
	}

	TreeNode<T>* getRoot() const { return root; }
	unsigned getSize() const { return size; }

	void Insert(T value)
	{
		TreeNode<T>* node = new(std::nothrow) TreeNode<T>(value);
		if (node)
		{
			if (!root)
			{
				root = node;
			}
			else
			{
				TreeNode<T>* tn = root;
				while (tn)
				{
					if (value <= tn->data)
					{
						if (!tn->left)
						{
							tn->left = node;
							break;
						}
						tn = tn->left;
					}
					else
					{
						if (!tn->right)
						{
							tn->right = node;
							break;
						}
						tn = tn->right;
					}
				}
			}
			++size;
		}
	}

	T GetMin() const
	{
		TreeNode<T>* tn = root;
		while (tn->left)
		{
			tn = tn->left;
		}
		return tn->data;
	}
	T GetMax() const
	{
		TreeNode<T>* tn = root;
		while (tn->right)
		{
			tn = tn->right;
		}
		return tn->data;
	}
	bool HasValue(T& value) const
	{
		TreeNode<T>* tn = search_r(root, value);
		return tn ? true : false;
	}

	/// Depth-first search/traversal (DFS)
	template<typename V>
	T* Dfs(V& visit) const
	{
		auto result = dfs_r(root, visit);
		return result != NULL ? &(result->data) : NULL;
	}

	/// Order traversal
	template<typename V>
	void TraversePreOrder(V& visit) const
	{
		preorder_r<V>(root, visit);
	}
	template<typename V>
	void TraverseInOrder(V& visit) const
	{
		inorder_r<V>(root, visit);
	}
	template<typename V>
	void TraversePostOrder(V& visit) const
	{
		postorder_r<V>(root, visit);
	}

	/// Breadth-first search/traversal (BFS).
	/// Classical BFS with single node visiting.
	template<typename V>
	void Bfs(V& visit) const
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
	template<typename V>
	void Bfsl(V& visit) const
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

	/// Mirrors the tree
	void Mirror()
	{
		mirror_r(root);
	}

	/// Checks if the tree is a BST
	bool IsBsTree() const
	{
		return isBst_r(root, LONG_MIN, LONG_MAX);
	}

	/// Finds all paths in the tree
	template<typename V>
	void AllPaths(V& visit) const
	{
		std::deque<T> dtn;
		allPaths_r(root, dtn, visit);
	}

	/// Lowest Common Ancestor (LCA)
	T* SearchLca(T& value1, T& value2) const
	{
		auto lca = lca_r(root, value1, value2);
		return lca != NULL ? &(lca->data) : NULL;
	}

	T* SearchLcaNbst1(T& value1, T& value2) const
	{
		auto lca = lca_nbst_1_r(root, value1, value2);
		return lca != NULL ? &(lca->data) : NULL;
	}

	template<typename V>
	T* SearchLcaNbst2(V& visit) const
	{
		auto lca = lca_nbst_2_r(root, visit);
		return lca != NULL ? &(lca->data) : NULL;
	}

private:
	TreeNode<T>* root;
	unsigned size;

	template<typename V>
	void preorder_r(TreeNode<T>* node, V& visit) const
	{
		if (node)
		{
			visit(node->data);
			preorder_r<V>(node->left, visit);
			preorder_r<V>(node->right, visit);
		}
	}

	template<typename V>
	void inorder_r(TreeNode<T>* node, V& visit) const
	{
		if (node)
		{
			inorder_r<V>(node->left, visit);
			visit(node->data);
			inorder_r<V>(node->right, visit);
		}
	}

	template<typename V>
	void postorder_r(TreeNode<T>* node, V& visit) const
	{
		if (node)
		{
			inorder_r<V>(node->left, visit);
			inorder_r<V>(node->right, visit);
			visit(node->data);
		}
	}

	template<typename V>
	TreeNode<T>* dfs_r(TreeNode<T>* node, V& visit) const
	{
		TreeNode<T>* result = NULL;
		if (node != NULL)
		{
			if (visit(node->data))
			{
				result = node;
			}
			else
			{
				result = dfs_r(node->left, visit);
				if (result == NULL)
				{
					result = dfs_r(node->right, visit);
				}
			}
		}

		return result;
	}

	TreeNode<T>* search_r(TreeNode<T>* tn, T& value) const
	{
		if (tn)
		{
			if (value < tn->data) return search_r(tn->left, value);
			else if (value > tn->data) return search_r(tn->right, value);
		}
		return tn;
	}

	void mirror_r(TreeNode<T>* tn)
	{
		if (tn)
		{
			if (tn->left || tn->right)
			{
				TreeNode<T>* t = tn->left;
				tn->left = tn->right;
				tn->right = t;
			}

			mirror_r(tn->left);
			mirror_r(tn->right);
		}
	}

	bool isBst_r(TreeNode<T>* tn, T min, T max) const
	{
		bool result = true;
		if (tn != NULL)
		{
			result = tn->data > min && tn->data <= max;
			if (result && tn->left != NULL)
			{
				result = tn->left->data <= tn->data ? isBst_r(tn->left, min, tn->data) : false;
			}
			if (result && tn->right != NULL)
			{
				result = tn->right->data > tn->data ? isBst_r(tn->right, tn->data, max) : false;
			}
		}

		return result;
	}

	/// Builds all paths in-place into deque in DFS style
	template<typename V>
	void allPaths_r(TreeNode<T>* node, std::deque<T>& dtn, V& visit) const
	{
		if (node != NULL)
		{
			dtn.push_back(node->data);
			if (node->left == NULL && node->right == NULL)
			{
				visit(dtn);
			}
			else
			{
				allPaths_r(node->left, dtn, visit);
				allPaths_r(node->right, dtn, visit);
			}
			dtn.pop_back();
		}
	}

	TreeNode<T>* lca_r(TreeNode<T>* node, T& v1, T& v2) const
	{
		TreeNode<T>* result = NULL;
		if (node != NULL)
		{
			if (std::max(v1, v2) < node->data)
			{
				result = lca_r(node->left, v1, v2);
			}
			else if (std::min(v1, v2) > node->data)
			{
				result = lca_r(node->right, v1, v2);
			}
			else
			{
				result = node;
			}
		}

		return result;
	}

	// Algorithm from EPI.
	// Time: O(n), space: O(1)
	TreeNode<T>* lca_nbst_1_r(TreeNode<T>* node, T& v1, T& v2) const
	{
		if (node == NULL)
		{
			return NULL;
		}
		else if (node->data == v1 || node->data == v2)
		{
			return node;
		}

		TreeNode<T>* left = lca_nbst_1_r(node->left, v1, v2);
		TreeNode<T>* right = lca_nbst_1_r(node->right, v1, v2);

		if (left != NULL && right != NULL)
		{
			return node;
		}
		else
		{
			return left != NULL ? left : right;
		}
	}

	template<typename C>
	TreeNode<T>* lca_nbst_2_r(TreeNode<T>* node, C& check) const
	{
		TreeNode<T>* result = node;
		if (node != NULL)
		{
			check.Reset();
			check(node->data);
			if (check.HasNone())
			{
				dfs_r(node->left, check);
				if (check.HasAll())
				{
					result = lca_nbst_2_r(node->left, check);
				}
				else if (check.HasNone())
				{
					result = lca_nbst_2_r(node->right, check);
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
