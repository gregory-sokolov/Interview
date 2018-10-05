#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <numeric>

/// 
/// EPI. Chapter 6. String Problems
///
class Strings
{
public:
	/// 
	/// Returns string length
	/// 
	static unsigned Length(const char* s)
	{
		unsigned n = 0;
		if (s != NULL)
		{
			for (n = 0; s[n]; ++n) {}
		}

		return n;
	}

	/// 
	/// Reverts a string in place
	/// 
	static const char* StrRev(char* s)
	{
		if (s != NULL)
		{
			for (int i = 0, j = Length(s) - 1; i < j; ++i, --j)
			{
				// std::swap(s[i], s[j]);
				char t = s[i];
				s[i] = s[j];
				s[j] = t;
			}
		}

		return s;
	}

	/// 
	/// Finds an index of the first substring
	/// 
	static int StrStr(const char* s, const char* p)
	{
		if (s != NULL && p != NULL)
		{
			for (unsigned i = 0; i < Length(s); ++i)
			{
				for (unsigned j = 0; j < Length(p); ++j)
				{
					if (s[i + j] != p[j] || s[i + j] == '\0')
					{
						break;
					}

					if (j == Length(p) - 1)
					{
						return (int)i;
					}
				}
			}
		}

		return -1;
	}

	///
	/// Returns true if an input string is a palindrome
	///
	static bool IsPalindrome(const char* s)
	{
		if (s == NULL) return false;
		
		bool result = true;
		for (unsigned i = 0, n = Length(s); i <= n; ++i, --n)
		{
			if (s[i] != s[n - 1])
			{
				result = false;
				break;
			}
		}

		return result;
	}

	/// 
	/// Performs full-string primitive regex matching (with only '.' and '*')
	/// 
	static bool IsMatch(const char* s, const char* p)
	{
		// Exit on reaching end of string (full-string)
		if (*p == '\0') return *s == '\0';

		// Next is not '*', match current character
		if (*(p + 1) != '*')
		{
			return (*p == *s || (*p == '.' && *s != '\0')) && IsMatch(s + 1, p + 1);
		}

		// Next is '*', do exhaustive search
		while (*p == *s || (*p == '.' && *s != '\0'))
		{
			if (IsMatch(s, p + 2)) return true;
			++s;
		}

		return IsMatch(s, p + 2);
	}

	/// 
	/// Parses an expression of numbers, + and * and calcultes the result
	/// 
	static long long CalculateExpression(const char* s)
	{
		if (s == NULL) return 0;
		
		long long result = 0, product = LLONG_MAX;
		std::string number;
		for (unsigned i = 0; s[i]; ++i)
		{
			if (isdigit(s[i]))
			{
				number += s[i];
			}
			if(s[i] == '*')
			{
				product = GetProduct(number, product);
				number = "";
			}
			if (s[i] == '+' || s[i + 1] == '\0')
			{
				product = GetProduct(number, product);
				number = "";
				result += product == LLONG_MAX ? 0 : product;
				product = LLONG_MAX;
			}
		}

		return result;
	}
	/// Calculates the product
	static long long GetProduct(std::string number, long long product)
	{
		return number == "" ? product : (product == LLONG_MAX ? std::stol(number) : product*std::stol(number));
	}

	/// Returns all anagrams from the list of strings.
	/// Hash table unordered_map provides lookup operation in O(1).
	/// Time: O(n), space: O(n)
	static void FindAnagrams(const std::vector<std::string>& text, std::vector<std::vector<std::string>>& results)
	{
		std::unordered_map<std::string, std::vector<std::string>> filter;
		for (auto&& word : text)
		{
			std::string key = word;
			std::sort(key.begin(), key.end());

			if (filter.find(key) == filter.end())
			{
				std::vector<std::string> vs = { word };
				filter[key] = vs;
			}
			else
			{
				filter[key].push_back(word);
			}
		}

		for (auto it = filter.begin(); it != filter.end(); ++it)
		{
			if (it->second.size() > 1)
			{
				results.push_back(it->second);
			}
		}
	}

	/// EPI 15.11.1. Levenstein distance (edit distance). 
	/// Returns the number of edit operations required to transform one string s1 to another s2.
	/// Types of standard operations: 
	/// I - insert, D - delete, R - replace, M - match
	/// Time: O(m*n), space: O(m*n)
	static int LevensteinDistance(const std::string& s1, const std::string& s2)
	{
		// Input checks
		if (s1.empty() && s2.empty() || s1 == s2)
		{
			return 0;
		}
		else if (s1.empty() && !s2.empty())
		{
			return s2.size();
		}
		else if (!s1.empty() && s2.empty())
		{
			return s1.size();
		}

		// Initialization
		unsigned m = s1.size(), n = s2.size();
		std::vector<std::vector<unsigned>> mx(m + 1, std::vector<unsigned>(n + 1));
		for (unsigned i = 0; i <= m; ++i)
		{
			mx[i][0] = i;
		}
		for (unsigned i = 0; i <= n; ++i)
		{
			mx[0][i] = i;
		}

		// The DP algorithm
		for (unsigned i = 1; i <= m; ++i)
		{
			for (unsigned j = 1; j <= n; ++j)
			{
				if (s1[i - 1] == s2[j - 1])
				{
					mx[i][j] = mx[i - 1][j - 1];
				}
				else
				{
					mx[i][j] = 1 + std::min(std::min(mx[i][j - 1], mx[i - 1][j]), mx[i - 1][j - 1]);
				}
			}
		}

		// TODO: debug tracing
		std::cout << std::endl;
		for (unsigned i = 0; i < m + 1; ++i)
		{
			for (unsigned j = 0; j < n + 1; ++j)
			{
				std::cout << std::setiosflags(std::ios::right) << std::setw(3) << mx[i][j];
			}
			std::cout << std::endl;
		}

		// Editorial prescription
		/*for (unsigned i = m; i >= 0; --i)
		{
			for (unsigned j = n; j >= 0; --j)
			{
				if (mx[i][j] == mx[i - 1][j - 1])
				{

				}
				else if (mx[i][j])
			}
		}*/

		return mx[m][n];
	}

	/// EPI 15.12. Word breaking (bedbathandbeyond problem).
	/// Checks if the text is a consequent concatenation of words and returns that sequence.
	/// Time: O(n^2), space: O(n)
	static std::vector<std::string> SplitByWords(const std::string& s, const std::set<std::string>& d)
	{
		std::deque<std::pair<std::string, unsigned>> words;
		std::string token;
		for (unsigned i = 0; i < s.size(); ++i)
		{
			token += s[i];
			if (d.find(token) != d.cend())
			{
				words.push_back(std::make_pair(token, i));
				token.clear();
			}

			if (i == s.size() - 1 && !token.empty() && !words.empty())
			{
				token = words.back().first;
				i = words.back().second;
				words.pop_back();
			}

			// TODO: debug tracing
			if (token.empty())
			{
				LogResults(words, i + 1);
			}
		}

		std::vector<std::string> results;
		std::transform(words.cbegin(), words.cend(), back_inserter(results),
			[](const std::pair<std::string, unsigned>& x) { return x.first; });
		return results;
	}

	/// Log helper
	static void LogResults(std::deque<std::pair<std::string, unsigned>> words, unsigned i)
	{
		std::cout << std::setiosflags(std::ios::right) << std::setw(2) << std::setfill('0') << i << ": [ ";
		for (auto it = words.cbegin(); it != words.cend(); ++it)
		{
			std::cout << it->first << (it->first != words.crbegin()->first ? ", " : "");
		}
		std::cout << " ]" << std::endl;
	}
};