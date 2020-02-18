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

/// N-ary tree node
template<typename T>
struct TreeNodeN
{
	T data;
	std::vector<TreeNodeN*> children;
};