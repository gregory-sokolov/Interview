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

	cout << "- Anagrams -" << endl;
	{
		vector<string> vs4 = { "My", "palm", "level", "in", "this", "node", "is", "almost", "done", "and", "it's", "oden", "by", "lamp" };
		cout << "Text: ";
		for (auto&& word : vs4)
		{
			cout << word << " ";
		}
		cout << endl;
		vector<vector<string>> anagrams;
		Strings::FindAnagrams(vs4, anagrams);
		cout << "Anagrams: ";
		unsigned index = 0;
		for (auto entry = anagrams.begin(); entry != anagrams.end(); ++entry)
		{
			cout << "{";
			for (auto ai = entry->begin(); ai != entry->end(); ++ai)
			{
				cout << *ai << (ai != entry->end() - 1 ? ", " : "}");
			}
			cout << (index++ < anagrams.size() - 1 ? ", " : "");
		}
		cout << endl;
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
		unsigned index = 0;
		for (auto msi = ms1.begin(); msi != ms1.end(); ++msi)
		{
			auto is = Strings::IsMatch(msi->first.c_str(), msi->second.c_str());
			cout << "\"" << msi->first << "\", \"" << msi->second << "\": " << (is ? "true" : "false") << (index++ < ms1.size() - 1 ? ", " : "");
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

	cout << "- Levenshtein distance (LD) -" << endl;
	{
		vector<pair<string, string>> testLD =
		{
			{ "", "" },
			{ "", "a" },
			{ "a", "" },
			{ "aaa", "aaa" },
			{ "aabaa", "aacaa" },
			{ "abc", "defgh" },
			{ "intention", "execution" },
			{ "democrat", "republican" },
		    { "exponential", "polynomial" },
			{ "subexponential", "subpolynomial" }
		};
		for (unsigned i = 0; i < testLD.size(); ++i)
		{
			auto input = testLD[i];
			cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i + 1 << ": " << setfill('\0') <<
				input.first << " -> " << input.second << ": ";
			auto result = Strings::LevenshteinDistance(input.first, input.second);
			cout << "ld = " << result.first << endl;
			if (result.second.size() > 0)
			{
				string src, dst, edit;
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(src),
					[](const std::pair<char, char> x) { return !x.first && x.second ? ' ' : x.first; });
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(dst),
					[](const std::pair<char, char> x) { return x.first && !x.second ? ' ' : x.second; });
				std::transform(result.second.cbegin(), result.second.cend(), back_inserter(edit),
					[](const std::pair<char, char> x)
				{
					return x.first && !x.second ? 'D' : (!x.first && x.second ? 'I' : (x.first != x.second ? 'R' : 'M'));
				});
				!edit.empty() ? edit.erase(edit.cend() - 1) : edit.cend();
				cout << src << endl;
				cout << dst << endl;
				cout << edit << endl;
			}
			cout << "--" << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "- Word breaking -" << endl;
	{
		set<string> dictionary =
		{
			"no", "in", "is", "it", "ack", "now", "led", "eve", "owl", "win",
			"know", "even", "lack", "edge", "here", "tick",
			"event", "noise", "ledge", "seven", "turel", "where",
			"venture", "heretic", "acknowledge"
		};
		vector<string> testWB =
		{
			"noiseventurelacknowledge", "nowhereticknowin",
			"abcdefghijk", ""
		};
		for (auto si = testWB.begin(); si != testWB.end(); ++si)
		{
			cout << "Input: " << si->c_str() << endl;
			auto result = Strings::SplitByWords(si->c_str(), dictionary);
			cout << "Resut: [";
			for (auto it = result.cbegin(); it != result.cend(); ++it)
			{
				cout << *it << (it != result.cend() - 1 ? ", " : "");
			}
			cout << "]" << endl;
		}
		cout << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

