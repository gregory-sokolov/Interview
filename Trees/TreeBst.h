#pragma once

#include <iostream>
#include <limits>
#include <queue>
#include <deque>
#include <algorithm>

/// Binary tree node
template<typename T>
struct TreeNode
{
	TreeNode* left;
	TreeNode* right;
	T data;

	TreeNode() : left(nullptr), right(nullptr) {}
	TreeNode(T value) : left(nullptr), right(nullptr), data(value) {}
};

/// Binary search tree (BST)
template<typename T>
class BSTree
{
public:
	BSTree() : root(nullptr), size(0) {}

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
		TreeNode<T>* node = new TreeNode<T>(value);
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

	/// Returns min value
	T GetMin() const
	{
		TreeNode<T>* tn = root;
		while (tn->left)
		{
			tn = tn->left;
		}
		return tn->data;
	}

	/// Returns max value
	T GetMax() const
	{
		TreeNode<T>* tn = root;
		while (tn->right)
		{
			tn = tn->right;
		}
		return tn->data;
	}

	/// Order traversals
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
			postorder_r<V>(node->left, visit);
			postorder_r<V>(node->right, visit);
			visit(node->data);
		}
	}
};

