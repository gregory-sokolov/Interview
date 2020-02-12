#pragma once

///
/// Tree Structures
///

/// Binary tree node
template<typename T>
struct TreeNode
{
	T data;
	TreeNode* left = nullptr;
	TreeNode* right = nullptr;

	TreeNode* next = nullptr;

	TreeNode() = default;
	TreeNode(T value): data(value) {}
};

/// Non-binary tree
template<typename T>
struct TreeNodeNb
{
	T data;
	std::vector<TreeNodeNb*> children;
};