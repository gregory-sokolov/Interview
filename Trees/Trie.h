#pragma once

#include <string>
#include <unordered_map>

/// Leetcode 208. Trie
/// Implements a trie - prefix tree.
/// Uses hash table to store children of each node and minimize memory usage (space < O(2^A) in normal case).
/// Time complexity for all operations: O(n*A), n - word length, A - alphabet size

struct TrieNode
{
	char value = '\0';
	bool valid = false;
	std::unordered_map<char, TrieNode*> children;

	TrieNode() = default;
	explicit TrieNode(char c) : value(c) {}
};

class Trie
{
public:
	// Constructor
	Trie() {}

	// Destructor
	~Trie() 
	{
		delete_r(&_root);
	}

	// Inserts a word into the trie
	// Time: O(n*A)
	void Insert(std::string word)
	{
		insert(word);
	}

	// Returns if only the whole word is in the trie
	// Time: O(n*A)
	bool Contains(std::string prefix)
	{
		return search(prefix, false);
	}

	// Returns true if there is any word in the trie that starts with the given prefix
	// Time: O(n*A)
	bool StartsWith(std::string prefix)
	{
		return search(prefix, true);
	}

	// Removes a word from the trie
	// Time: O(n*A)
	void Remove(std::string word)
	{
		remove(word);
	}

private:
	TrieNode _root;

	// Inserts a key
	void insert(std::string key)
	{
		TrieNode* tn = &_root;
		for (unsigned i = 0; i < key.size(); ++i)
		{
			auto found = tn->children.find(key[i]);
			auto next = found != tn->children.cend() ? found->second : nullptr;
			if (!next)
			{
				next = new TrieNode(key[i]);
				tn->children[key[i]] = next;
			}
			next->valid = next->valid || i == key.size() - 1;
			tn = next;
		}
	}

	// Searches for a key
	bool search(std::string key, bool prefix)
	{
		bool result = !key.empty();

		TrieNode* tn = &_root;
		for (unsigned i = 0; i < key.size() && tn; ++i)
		{
			auto found = tn->children.find(key[i]);
			result = found != tn->children.cend();
			tn = result ? found->second : nullptr;
		}

		return result && (prefix || (tn && tn->valid));
	}

	// Removes a key
	void remove(std::string key)
	{
		TrieNode* tn = &_root;
		for (unsigned i = 0; i < key.size() && tn; ++i)
		{
			auto found = tn->children.find(key[i]);
			tn = found != tn->children.cend() ? found->second : nullptr;
			if (tn && i == key.size() - 1)
			{
				tn->valid = false;
			}
		}
	}

	// Frees memory
	void delete_r(TrieNode* tn)
	{
		if (tn->children.empty())
		{
			delete tn;
		}
		else
		{
			for (const auto& entry : tn->children)
			{
				delete_r(entry.second);
			}
		}
	}
};