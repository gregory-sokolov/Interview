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
	/// Splits a string by delimiter
	/// 
	static std::vector<std::string> Split(std::string s, std::string delim)
	{
		std::vector<std::string> result;
		size_t last = 0, dlen = delim.size();
		for (size_t next = s.find(delim, last);
			next != std::string::npos;
			last = next + dlen, next = s.find(delim, last))
		{
			result.push_back(s.substr(last, next - last));
		}
		result.push_back(s.substr(last));

		return result;
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

	/// Facebook. Shuffling word encryption
	/// You've devised a simple encryption method for alphabetic strings that shuffles the characters.
	/// When you encrypt a string S, you start with an initially - empty resulting string R and append characters to it as follows:
	/// - append the middle character of S(if S has even length, then we define the middle character as the left - most of the two central characters)
	///	- append the encrypted version of the substring of S that's to the left of the middle character (if non-empty)
	/// - append the encrypted version of the substring of S that's to the right of the middle character (if non-empty)
	/// For example, to encrypt the string "abc", we first take "b", and then append the encrypted version of "a" (which is just "a") and the encrypted version of "c" (which is just "c") to get "bac".
	static std::string EncryptWord(std::string s)
	{
		if (s.empty() || s.size() == 1)
		{
			return s;
		}
		if (s.size() == 2)
		{
			return std::string({ s[0], s[1] });
		}

		unsigned m = s.size() / 2, mc = m - (s.size() % 2 == 0 ? 1 : 0);
		std::string result(1, s[mc]);

		std::string left = s.substr(0, mc);
		result += EncryptWord(left);

		std::string right = s.substr(mc + 1, m);
		result += EncryptWord(right);

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
	static std::vector<std::vector<std::string>> FindAnagrams(const std::vector<std::string>& text)
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

		std::vector<std::vector<std::string>> results;
		for (auto it = filter.begin(); it != filter.end(); ++it)
		{
			if (it->second.size() > 1)
			{
				results.push_back(it->second);
			}
		}
		return results;
	}

	/// Leetcode 69. Group anagrams
	/// Groups all anagrams in the list of strings.
	/// Time: O(n*k*log(k)), space: O(n)
	static std::vector<std::vector<std::string>> GroupAnagrams(const std::vector<std::string>& strings)
	{
		std::unordered_map<std::string, std::vector<std::string>> ht;
		for (unsigned i = 0; i < strings.size(); ++i)
		{
			std::string sorted = strings[i];
			std::sort(sorted.begin(), sorted.end());
			if (ht.find(sorted) != ht.cend())
			{
				ht[sorted].push_back(strings[i]);
			}
			else
			{
				ht[sorted] = std::vector<std::string>({ strings[i] });
			}
		}

		std::vector<std::vector<std::string>> results;
		std::transform(ht.cbegin(), ht.cend(), std::back_inserter(results),
			[](const std::pair<std::string, std::vector<std::string>>& p)
			{ 
				return std::vector<std::string>(p.second.cbegin(), p.second.cend()); 
			});
		return results;
	}
};