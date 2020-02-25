#pragma once

#include "Tree.h"

// Tree node printer
template<typename T>
class NodePrinter
{
public:
	bool operator()(T value)
	{
		_vn.push_back(value);
		return false;
	}

	void print()
	{
		for (auto it = _vn.cbegin(); it != _vn.cend(); ++it)
		{
			std::cout << *it << (it != _vn.end() - 1 ? "-" : "");
		}
		std::cout << std::endl;
	}

private:
	std::vector<T> _vn;
};

// Tree level printer
template<typename T>
class LevelPrinter
{
public:
	void operator()(const std::vector<TreeNode<T>*>& vtn)
	{
		std::string level;
		bool nonEmpty = false;
		for (auto it = vtn.cbegin(); it != vtn.cend(); ++it)
		{
			level += *it != nullptr ? std::to_string((*it)->data) : "*";
			level += it != vtn.cend() - 1 ? " " : "";
			nonEmpty = nonEmpty || *it != nullptr;
		}
		if (nonEmpty)
		{
			std::cout << level << std::endl;
		}
	}
};

// Next pointer printer
template<typename T>
class NextPointerPrinter
{
public:
	void operator()(const std::vector<TreeNode<T>*>& nodes)
	{
		std::string level;
		if (!nodes.empty())
		{
			TreeNode<T>* tn = nodes[0];
			while (tn)
			{
				level += std::to_string(tn->data) + " ";
				tn = tn->other;
			}
			level = level.substr(0, level.size() - 1);
			std::cout << level << std::endl;
		}
	}
};

// Tree node pair checker 
template<typename T>
class PairChecker
{
public:
	PairChecker(T v1, T v2)
	{
		_values = std::make_pair(std::make_pair(v1, false), std::make_pair(v2, false));
	}

	void Reset()
	{
		_values.first.second = false;
		_values.second.second = false;
	}

	bool operator()(T value)
	{
		if (!_values.first.second) _values.first.second = _values.first.first == value;
		if (!_values.second.second) _values.second.second = _values.second.first == value;
		return HasAll();
	}

	bool HasAll()
	{
		return _values.first.second && _values.second.second;
	}

	bool HasNone()
	{
		return !_values.first.second && !_values.second.second;
	}

private:
	std::pair<std::pair<T, bool>, std::pair<T, bool>> _values;
};
