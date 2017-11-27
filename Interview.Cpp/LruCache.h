#pragma once

#include <list>
#include <unordered_map>

// LRU Cache
template<typename K, typename T>
class LruCache
{
	int size;
	std::list<std::pair<K, T>> ql;
	std::unordered_map<K, typename std::list<std::pair<K, T>>::const_iterator> ht;

public:
	LruCache(int sz) : size(sz)
	{
	}

	void Insert(K id, const T& item)
	{
		if (ql.size() == size)
		{
			ht.erase(ql.back().first);
			ql.pop_back();
		}

		ql.push_front(std::make_pair(id, item));
		ht[id] = ql.cbegin();
	}

	const T* Get(K id)
	{
		auto it = ht.find(id);
		if (it != ht.cend())
		{
			ql.splice(ql.cbegin(), ql, it->second);
		}

		return it != ht.cend() ? &((it->second)->second) : NULL;
	}

	const std::list<std::pair<K, T>>& GetAll() const
	{
		return ql;
	}
};
