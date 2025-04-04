/// 
/// EPI. Chapter 6. String Problems
///
#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "Strings.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Strings ==" << endl;

	cout << "- Reversions -" << endl;
	{
		vector<string> vs1 = { "", "a", "ab", "aba", "abb", "bbcc", "0123456789" };
		for (auto si = vs1.begin(); si != vs1.end(); ++si)
		{
			char* s = new char[si->size() + 1];
			strcpy_s(s, si->size() + 1, si->c_str());
			cout << *si << ": " << Strings::StrRev(s) << (si != vs1.end() - 1 ? ", " : "");
			delete[] s;
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Substrings -" << endl;
	{
		string s1 = "abcaabbccaaabbbaaa";
		cout << "Source: " << s1 << endl;
		vector<string> vs2 = { "", "a", "aa", "ab", "aaa", "aba", "abb", "abba", "bbcc", "xyz", "bbbaaac", "abcaabbccaaabbbaaa" };
		cout << "Substrings: ";
		for (auto pi = vs2.begin(); pi != vs2.end(); ++pi)
		{
			auto index = Strings::StrStr(s1.c_str(), pi->c_str());
			cout << *pi << ": " << index << (pi != vs2.end() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Splitting -" << endl;
	{
		string str = "Splitting a string in C++ is not that easy";
		cout << "Source: " << str << endl;
		vector<string> delims = { " ", "t", "in" };
		for (const auto& delim : delims)
		{
			auto result = Strings::Split(str, delim);
			cout << "\"" << delim << "\": ";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << *it << (it != result.cend() - 1 ? ", " : "");
			}
			cout << endl;
		}
	}
	cout << endl;

	cout << "- Palindromes -" << endl;
	{
		vector<string> vs3 = { "a", "aa", "ab", "aaa", "aba", "abb", "abba", "abaa", "abcba", "abccba" };
		for (auto si = vs3.begin(); si != vs3.end(); ++si)
		{
			auto is = Strings::IsPalindrome(si->c_str());
			cout << *si << ": " << (is ? "true" : "false") << (si != vs3.end() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Word encryption -" << endl;
	{
		vector<string> tests = { "", " ", "a", "aa", "ab", "aaa", "aba", "abc", "abcd", "abcxcba" },
					   answs = { "", " ", "a", "aa", "ab", "aaa", "baa", "bac", "bacd", "xbacbca" };
		for (unsigned i = 0; i < tests.size(); ++i)
		{
			auto result = Strings::EncryptWord(tests[i]);
			cout << tests[i] << ":" << answs[i] << ":" << result << (i != tests.size() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Find anagrams -" << endl;
	{
		vector<string> test = { "My", "palm", "level", "in", "this", "node", "is", "almost", "done", "and", "it's", "oden", "by", "lamp" };
		cout << "Text: ";
		for (const auto& word : test)
		{
			cout << word << " ";
		}
		cout << endl;

		auto result = Strings::FindAnagrams(test);
		cout << "Anagrams: ";
		for (auto entry = result.begin(); entry != result.end(); ++entry)
		{
			cout << "{";
			for (auto ai = entry->cbegin(); ai != entry->cend(); ++ai)
			{
				cout << *ai << (ai != entry->cend() - 1 ? ", " : "}");
			}
			cout << (entry != result.cend() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Group anagrams -" << endl;
	{
		vector<vector<string>> tests = 
		{ 
			{},
			{ "" },
			{ "", "" },
			{ "a" },
			{ "a", "a" },
			{ "a", "a", "a", "a" },
			{ "abcde" },
			{ "abcde", "zxywu" },
			{ "eat", "tea", "tan", "ate", "nat", "bat" } 
		};
		for (auto vs = tests.cbegin(); vs != tests.cend(); ++vs)
		{
			cout << "Input: ";
			for (auto word = vs->cbegin(); word != vs->cend(); ++word)
			{
				cout << (word->empty() ? "\"\"" : *word) << (word != vs->cend() - 1 ? ", " : "");
			}
			cout << endl;

			auto result = Strings::GroupAnagrams(*vs);
			cout << "Anagrams: " << endl;
			for (auto vs = result.cbegin(); vs != result.cend(); ++vs)
			{
				for (auto word = vs->cbegin(); word != vs->cend(); ++word)
				{
					cout << (word->empty() ? "\"\"" : *word) << (word != vs->cend() - 1 ? ", " : "");
				}
				cout << endl;
			}

			if (vs != tests.cend() - 1)
			{
				cout << "--" << endl;
			}
		}
	}
	cout << endl;

	cout << "- Simple regex -" << endl;
	{
		multimap<string, string> ms1 =
		{
			{ "a", "a" }, { "a", "b" }, { "a", ".*" },
			{ "aa", "aa" }, { "aa", "ab" }, { "aa", "a*" }, { "aa", "a.*" }, { "aa", "a.*a" }, { "aa", "aa*a" },
			{ "abbbc", "ab*c" }, { "abbc", "ab*bbc" }, { "abcbcd", "a.*c.*d" }
		};
		for (auto msi = ms1.begin(); msi != ms1.end(); ++msi)
		{
			auto is = Strings::IsMatch(msi->first.c_str(), msi->second.c_str());
			cout << "\"" << msi->first << "\", \"" << msi->second << "\": " << (is ? "true" : "false") << 
				(next(msi) != ms1.end() ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Expressions -" << endl;
	{
		vector<string> vs5 =
		{
			"", "**", "++", "2", "257", "1024567", "2*", "2+", "2*5", "2+5", "2+4+5", "2*4*5", "2*4+5", "2+4*5", "2*4+5*7", "2+4*5+7+5*4+2",
			"2**2++5", "2ab+ba5", "(2+4)*5", "0 +- 2*5", "2 + 0* 5", "1024567*1024567 + 1024567"
		};
		for (auto si = vs5.begin(); si != vs5.end(); ++si)
		{
			auto result = Strings::CalculateExpression(si->c_str());
			cout << *si << " = " << result << (si != vs5.end() - 1 ? ", " : "");
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

