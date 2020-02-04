#pragma once

#include <list>
#include <unordered_map>

///
/// Leetcode 146. LRU Cache
///
template<typename K, typename T>
class LruCache
{
	int size;
	std::list<std::pair<K, T>> ql;
	std::unordered_map<K, typename std::list<std::pair<K, T>>::iterator> ht;

public:
	LruCache(int sz) : size(sz)
	{
	}

	/// Returns an item by key, null - if not found.
	/// Moves requested item to the top of the cache.
	const T* Get(K key)
	{
		auto it = ht.find(key);
		if (it != ht.cend())
		{
			ql.splice(ql.cbegin(), ql, it->second);
		}

		return it != ht.cend() ? &((it->second)->second) : nullptr;
	}

	/// Puts an item to the cache by key: either updates the existing or inserts a new one.
	/// Each time moves the item to the top of the cache.
	void Put(K key, const T& item)
	{
		auto it = ht.find(key);
		if (it != ht.cend())
		{
			*(it->second) = std::make_pair(key, item);
			ql.splice(ql.begin(), ql, it->second);
			ht[key] = it->second;
		}
		else
		{
			if (ql.size() == size)
			{
				ht.erase(ql.back().first);
				ql.pop_back();
			}
			ql.push_front(std::make_pair(key, item));
			ht[key] = ql.begin();
		}
	}

	/// Returns all cache items
	const std::list<std::pair<K, T>>& GetAll() const
	{
		return ql;
	}
};
