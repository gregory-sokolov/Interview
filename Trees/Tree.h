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
	TreeNode* other = nullptr;

	TreeNode() = default;
	TreeNode(T value): data(value) {}
};
