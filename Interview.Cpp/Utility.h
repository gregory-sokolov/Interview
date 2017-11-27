#pragma once

// Tree node printer
template<typename T>
class NodePrinter
{
public:
	void operator()(T value) 
	{ 
		vn.push_back(value); 
	}

	void print()
	{
		for (std::vector<T>::const_iterator it = vn.begin(); it != vn.end(); ++it)
		{
			std::cout << *it << (it != vn.end() - 1 ? "-" : "");
		}
		std::cout << std::endl;
	}

private:
	std::vector<T> vn;
};

// Tree path holder 
template<typename T>
class PathFinder
{
public:
	void operator()(std::deque<T> path)  
	{ 
		paths.push_back(path); 
	}

	void print()
	{
		for (std::vector<std::deque<T>>::const_iterator pi = paths.begin(); pi != paths.end(); ++pi)
		{
			for (std::deque<T>::const_iterator ni = pi->begin(); ni != pi->end(); ++ni)
			{
				std::cout << *ni << (ni != pi->end() - 1 ? "-" : "");
			}
			std::cout << (pi != paths.end() - 1 ? ", " : "");
		}
	}

private:
	std::vector<std::deque<T>> paths;
};

