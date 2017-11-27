#pragma once

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
		for (std::vector<T>::const_iterator it = _vn.begin(); it != _vn.end(); ++it)
		{
			std::cout << *it << (it != _vn.end() - 1 ? "-" : "");
		}
		std::cout << std::endl;
	}

private:
	std::vector<T> _vn;
};

// Tree path holder 
template<typename T>
class PathFinder
{
public:
	void operator()(std::deque<T> path)
	{
		_paths.push_back(path);
	}

	void print()
	{
		for (std::vector<std::deque<T>>::const_iterator pi = _paths.begin(); pi != _paths.end(); ++pi)
		{
			for (std::deque<T>::const_iterator ni = pi->begin(); ni != pi->end(); ++ni)
			{
				std::cout << *ni << (ni != pi->end() - 1 ? "-" : "");
			}
			std::cout << (pi != _paths.end() - 1 ? ", " : "");
		}
		cout << endl;
	}

private:
	std::vector<std::deque<T>> _paths;
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
