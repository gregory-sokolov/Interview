#pragma once

// Graph vertex printer
template<typename T, typename C>
class  GraphVertexPrinter
{
public:
	bool operator()(const T& key, C cost)
	{
		vv.push_back(std::make_pair(key, cost));
		return false;
	}

	void print()
	{
		for (std::vector<std::pair<T, C>>::const_iterator it = vv.begin(); it != vv.end(); ++it)
		{
			std::cout << it->first << "(" << it->second << ")" <<(it != vv.end() - 1 ? " - " : "");
		}
		std::cout << std::endl;
	}

private:
	std::vector<std::pair<T, C>> vv;
};