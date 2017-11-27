// Interview.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <bitset>
#include <limits>
#include <cmath>
#include <ctime>

#include "Interview.h"
#include "Bitwise.h"
#include "Numerical.h"
#include "Strings.h"
#include "Combinatorics.h"
#include "LruCache.h"
#include "LinkedList.h"
#include "BStree.h"
#include "BSTreeHelper.h"
#include "Graph.h"
#include "GraphHelper.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
    cout << "Program has started" << endl;

    cout << "== Classes ==" << endl;
    {
        cout << "Slice-effect started" << endl;
        AAA* a = new AAA(10);
        AAA* b = new BBB(20);
        *a = *b;
        delete a;
        //delete b; // double delete because of slice-effect
        cout << "Slice-effect completed" << endl;

        auto pva = new vector<AAA*>(2);
        auto pvb = new vector<BBB*>(5);
        //pva = pvb; // template covariance error

        Converter cv;
        auto ci = (int)cv;
        cout << "Class to int: " << ci << endl;
        //Derived d; // pure virtual call

        class A {};
        class B : public A {};
        //for (unsigned int i = 100; i >= 0; i--)
        //	printf("%d", i);
        // eternal loop

        int x = 27;
        const int сх = x;
        const int& rx = x;
        typeInferer(x);
        typeInferer(сх);
        typeInferer(rx);
        typeInferer(27);

        auto ax = rx;
        auto& arx = x;
        const auto& arcx = x;
    }
    cout << endl;

    cout << "== Bitwise ==" << endl;
    {
        cout << "- Bit Count -" << endl;

        vector<long long> numbers =
        {
            0, 1, 2, 3, 5, 9, 0x7F, 0xFF, 0x7FFFFFFF, 0x0001000100010001, LLONG_MAX - 1, LLONG_MAX,
            -1, -2, -3, -8, -9, -0x0001000100010001, LLONG_MIN + 1, LLONG_MIN
        };
        cout << "-- Simple method --" << endl;
        for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
        {
            cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountSmp(*it) << (it != numbers.cend() - 1 ? ", " : "") << endl;
        }
        cout << "-- 'The lowest bit' method --" << endl;
        for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
        {
            cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountOpt(*it) << (it != numbers.cend() - 1 ? ", " : "") << endl;
        }
        cout << "-- Lookup table method --" << endl;
        vector<unsigned short> table;
        Bitwise::GenerateWordTable(table);
        for (auto it = numbers.cbegin(); it != numbers.cend(); ++it)
        {
            cout << (bitset<64>)*it << ":" << *it << ":" << " -> " << Bitwise::GetBitCountTbl(*it, table) << (it != numbers.cend() - 1 ? ", " : "") << endl;
        }
        cout << endl;

        cout << "- Bit Swap -" << endl;
        bitset<16> number(string("1000000010010110"));
        vector<pair<unsigned short, unsigned short>> indices = { { 0, 0 },{ 0, 1 },{ 1, 2 },{ 2, 6 },{ 0, 7 },{ 7, 8 },{ 0, 15 },{ 14, 15 } };
        for (auto it = indices.cbegin(); it != indices.cend(); ++it)
        {
            bitset<16> result = Bitwise::SwapBits(number.to_ullong(), it->first, it->second);
            cout << number << ":(" << it->first << "," << it->second << ") -> " << result << (it != indices.cend() - 1 ? ", " : "") << endl;
        }
        cout << endl;

        cout << "- Bit Reverse -" << endl;
        vector<bitset<16>> numbers2 = { bitset<16>(string("1110000000011111")), bitset<16>(string("0000111111110000")),
            bitset<16>(string("1111111100000000")), bitset<16>(string("1000000101111110")) };
        for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
        {
            bitset<16> result = Bitwise::ReverseBits((unsigned short)it->to_ulong());
            cout << *it << " -> " << result << (it != numbers2.cend() - 1 ? ", " : "") << endl;
        }
        cout << endl;

        cout << "- Power Set -" << endl;
        vector<string> inputSet = { "A", "B", "C", "D" };
        auto powerSet = Bitwise::GenereatePowerSet(inputSet);
        cout << "Initial set: { ";
        for (auto item = inputSet.cbegin(); item != inputSet.cend(); ++item)
        {
            cout << *item << (item != inputSet.cend() - 1 ? ", " : "");
        }
        cout << " }" << endl;
        cout << "Power set (" << powerSet.size() << "): ";
        for (auto subset = powerSet.cbegin(); subset != powerSet.cend(); ++subset)
        {
            cout << "{ ";
            for (auto it = subset->cbegin(); it != subset->cend(); ++it)
            {
                cout << *it << (it != subset->cend() - 1 ? "," : "");
            }
            cout << (subset != powerSet.cend() - 1 ? " }, " : " }");
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");

    cout << "== Numerical ==" << endl;
    {
        cout << "- Square roots -" << endl;
        cout << "Integers: ";
        vector<unsigned> numbers1 =
        {
            0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
            20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
            49, 55, 81, 92, 100, 288, 289, 290, 10000, 99980001
        };
        for (auto it = numbers1.cbegin(); it != numbers1.cend(); ++it)
        {
            cout << *it << ":" << Numerical::Sqrt(*it) << (it != numbers1.cend() - 1 ? ", " : "");
        }
        cout << endl;
        const int digits = 5;
        double precision = 1 / pow(10, digits);
        cout << "Doubles BS (" << digits << "-digits)";
        vector<double> numbers2 =
        {
            0.0, 0.02, 0.04, 0.09, 1, 1.96, 2.0, 3.0, 4, 6.5536, 62.2521, 99999998.00000001
        };
        for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
        {
            cout << *it << ":" << Numerical::Sqrt(*it, precision) << (it != numbers2.cend() - 1 ? ", " : "");
        }
        cout << endl;
        cout << "Doubles N-R (" << digits << "-digits)";
        for (auto it = numbers2.cbegin(); it != numbers2.cend(); ++it)
        {
            cout << *it << ":" << Numerical::SqrtNewton(*it, precision) << (it != numbers2.cend() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "- Permutations -" << endl;
        vector<vector<unsigned>> results1;
        unsigned* pmt0 = NULL;
        cout << "Permutation input: (empty)" << endl;
        Combinatorics::PermutationsR(pmt0, 0, 0, results1);
        cout << "Permutation count: " << results1.size() << endl;
        cout << "Permutations: ";
        for (auto it = results1.begin(); it < results1.end(); ++it)
        {
            copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
            cout << " ";
        }
        cout << endl << endl;

        unsigned pmti[] = { 1, 2, 3, 4 };
        cout << "Permutation input: ";
        copy(pmti, pmti + sizeof(pmti) / sizeof(int), ostream_iterator<unsigned>(cout));
        cout << endl;
        Combinatorics::PermutationsR(pmti, sizeof(pmti) / sizeof(unsigned), sizeof(pmti) / sizeof(unsigned), results1);
        cout << "Permutation count: " << results1.size() << endl;
        cout << "Permutations: ";
        for (auto it = results1.begin(); it < results1.end(); ++it)
        {
            copy(it->begin(), it->end(), ostream_iterator<unsigned>(cout));
            cout << " ";
        }
        cout << endl << endl;

        vector<vector<char>> results2;
        char pmts[] = { 'a', 'b', 'c' };
        cout << "Permutation input: ";
        copy(pmts, pmts + sizeof(pmts) / sizeof(char), ostream_iterator<char>(cout));
        cout << endl;
        Combinatorics::PermutationsR(pmts, sizeof(pmts) / sizeof(char), sizeof(pmts) / sizeof(char), results2);
        cout << "Permutation count: " << results2.size() << endl;
        cout << "Permutations: ";
        for (auto it = results2.begin(); it < results2.end(); ++it)
        {
            copy(it->begin(), it->end(), ostream_iterator<char>(cout));
            cout << " ";
        }
        cout << endl << endl;

        cout << "- Sequences to sum -" << endl;
        vector<int> vi1 = { 7, 3, 5, 2, 10, 5, 0, 15, 0, 0, 12, 3 };
        //vector<int> vi2 = { 1, 2, 2, 0, 5, -5, 0, 8, -8, 1, 7, -3 };
        cout << "Input array: ";
        for (auto it = vi1.cbegin(); it != vi1.cend(); ++it)
        {
            cout << *it << (it != vi1.end() - 1 ? ", " : "");
        }
        cout << endl;
        long long sum = 15;
        // long long sum = 0;
        cout << "Sum to match: " << sum << endl;
        vector<deque<pair<unsigned, int>>> matches;
        Numerical::GetSumSequences(vi1, sum, matches);
        cout << "Sequences: " << (matches.size() != 0 ? to_string(matches.size()) : "not found") << endl;
        for (auto mi = matches.begin(); mi != matches.end(); ++mi)
        {
            cout << "[";
            for (auto it = mi->cbegin(); it != mi->cend(); ++it)
            {
                cout << it->first << (it != mi->end() - 1 ? "," : "]: ");
            }
            for (auto it = mi->cbegin(); it != mi->cend(); ++it)
            {
                cout << it->second << (it != mi->end() - 1 ? " " : "");
            }
            cout << (mi != matches.end() - 1 ? ", " : "");
        }
        cout << endl << endl;

        vector<int> vi2 = { -2, 2, 0, 0, 5, -5, 0, 1, -4, -1, 0, -7 };
        cout << "Input array: ";
        for (auto it = vi2.cbegin(); it != vi2.cend(); ++it)
        {
            cout << *it << (it != vi2.end() - 1 ? ", " : "");
        }
        cout << endl;
        auto kadane = Numerical::FindMaxSumSubarray(vi2);
        cout << "Max sum subarray (Kadane's): " << kadane.first << ", [" <<
            kadane.second.first << ", " << kadane.second.second << "]";
        cout << endl << endl;

        cout << "- Combinations: three-sum -" << endl;
        vector<int> vi3 = { 1, 2, 2, 5, -5, 8, 8, 1, 7, -3 };
        vector<int> vi4(vi3);
        cout << "Input array: ";
        copy(vi3.begin(), vi3.end(), ostream_iterator<int>(cout, ", "));
        cout << endl;
        for (auto&& sum : { 10, 23 })
        {
            cout << "Sum to match: " << sum << endl;
            auto found = Numerical::HasThreeSum(vi4, sum);
            cout << "Any combination found: " << (found ? "true" : "false") << endl;
            vector<vector<int>> matches;
            Numerical::ThreeSumCombinations(vi3, sum, matches);
            cout << "All combinations: " << matches.size() << endl;
            for (auto mi = matches.begin(); mi != matches.end(); ++mi)
            {
                cout << "[" << mi->at(0) << "," << mi->at(2) << "," << mi->at(4) << "]: " <<
                    mi->at(1) << " " << mi->at(3) << " " << mi->at(5) << (mi != matches.end() - 1 ? ", " : "");
            }
            cout << endl;
        }
        int low = 0, high = 20;
        cout << "Non-matching sums in range [" << low << "; " << high << "]: ";
        for (int sum = low; sum < high; ++sum)
        {
            auto found = Numerical::HasThreeSum(vi4, sum);
            if (!found)
            {
                cout << sum << (sum < high - 1 ? ", " : "");
            }
        }
        cout << endl;

        cout << "- Closest Points -" << endl;
        unsigned k = 4;
        pair<double, double> origin(0.0, 0.0);
        vector<pair<double, double>> vdpi =
        {
            make_pair(2.7, 1.8), make_pair(2.0, 5.9), make_pair(3.7, 3.4), make_pair(9.2, 0.4), make_pair(7.2, 7.5),
            make_pair(5.2, 2.6), make_pair(1.1, 1.3), make_pair(1.5, 2.7), make_pair(3.3, 8.1), make_pair(0.1, 9.9),
            make_pair(0.0, 0.0), make_pair(10.0, 10.0), make_pair(-4.56, 7.89), make_pair(0.3579, -0.2468), make_pair(-5.5, -7.7)
        };
        vector<pair<double, double>> vdpr;
        Numerical::GetClosestPoints(k, origin, vdpi, vdpr);
        cout << "Origin: " << "(" << origin.first << ";" << origin.second << ")" << ", count: " << k << endl;
        cout << "Points: ";
        for (auto pi = vdpi.begin(); pi != vdpi.end(); ++pi)
        {
            cout << "(" << pi->first << ";" << pi->second << ")" << (pi != vdpi.end() - 1 ? ", " : "");
        }
        cout << endl;
        cout << "Closest: ";
        for (auto pi = vdpr.begin(); pi != vdpr.end(); ++pi)
        {
            cout << "(" << pi->first << ";" << pi->second << ")" << (pi != vdpr.end() - 1 ? ", " : "");
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");

    cout << "== Strings ==" << endl;
    {
        cout << "- Reversions -" << endl;
        vector<string> vs1 = { "", "a", "ab", "aba", "abb", "bbcc", "0123456789" };
        for (auto si = vs1.begin(); si != vs1.end(); ++si)
        {
            char* s = new char[si->size() + 1];
            strcpy_s(s, si->size() + 1, si->c_str());
            cout << *si << ": " << Strings::StrRev(s) << (si != vs1.end() - 1 ? ", " : "");
            delete[] s;
        }
        cout << endl;

        cout << "- Substrings -" << endl;
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

        cout << "- Palindromes -" << endl;
        vector<string> vs3 = { "a", "aa", "ab", "aaa", "aba", "abb", "abba", "abaa", "abcba", "abccba" };
        for (auto si = vs3.begin(); si != vs3.end(); ++si)
        {
            auto is = Strings::IsPalindrome(si->c_str());
            cout << *si << ": " << (is ? "true" : "false") << (si != vs3.end() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "- Interconversions: int -> string -" << endl;
        vector<int> vs31 = { 0, 1, 12, 147, 65536, INT_MAX, -1, -16, -65536, INT_MIN };
        for (auto vi = vs31.cbegin(); vi != vs31.cend(); ++vi)
        {
            auto result = Strings::IntToString(*vi);
            cout << *vi << ": " << result << (vi != vs31.cend() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "- Interconversions: string -> int -" << endl;
        vector<string> vs32 = { "0", "1", "12", "147", "65536", "2147483647", "-1", "-16", "-65536", "-2147483648" };
        for (auto si = vs32.cbegin(); si != vs32.cend(); ++si)
        {
            auto result = Strings::StringToInt(*si);
            cout << *si << ": " << result << (si != vs32.cend() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "- Anagrams -" << endl;
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

        cout << "- Simple regex -" << endl;
        multimap<string, string> ms1 =
        {
            { "a", "a" },{ "a", "b" },{ "a", ".*" },
            { "aa", "aa" },{ "aa", "ab" },{ "aa", "a*" },{ "aa", "a.*" },{ "aa", "a.*a" },{ "aa", "aa*a" },
            { "abbbc", "ab*c" },{ "abbc", "ab*bbc" },{ "abcbcd", "a.*c.*d" }
        };
        index = 0;
        for (auto msi = ms1.begin(); msi != ms1.end(); ++msi)
        {
            auto is = Strings::IsMatch(msi->first.c_str(), msi->second.c_str());
            cout << "\"" << msi->first << "\", \"" << msi->second << "\": " << (is ? "true" : "false") << (index++ < ms1.size() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "- Expressions -" << endl;
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
    system("PAUSE");

    cout << "== LRU Cache ==" << endl;
    {
        vector<int> vsi1 = { 2, 5, 3, 2, 15, 3, 5, 7, 2, 10, 1, 3, 17, 3, 5, 9, 5 };
        int size = 4;
        LruCache<string, int> lru1(size);
        cout << "Cache size: " << size << endl;

        for (auto it = vsi1.begin(); it != vsi1.end(); ++it)
        {
            auto item = lru1.Get(to_string(*it));
            if (item == NULL)
            {
                lru1.Insert(to_string(*it), *it);
            }

            string status = item != NULL ? "cache hit" : "added as new";
            cout << setiosflags(ios::right) << setw(3) << *it << " -> " << setw(13) << status + "," << " [ ";
            auto cache = lru1.GetAll();
            for (auto ci = cache.begin(); ci != cache.end(); ++ci)
            {
                cout << to_string(ci->second) << " ";
            }
            cout << "]" << endl;
        }
    }
    cout << endl;
    system("PAUSE");

    cout << "== Linked lists ==" << endl;
    {
        SList list1, list2;
        list1.clear(); list2.clear();
        cout << "Empty list size: " << list1.getSize() << endl;

        list1.addHead(3); list2.addTail(2);
        list1.addHead(2); list2.addTail(3);
        list1.addHead(1); list2.addTail(2);
        list1.addHead(0); list2.addTail(5);
        list1.addTail(4); list2.addHead(6);
        list1.addTail(5); list2.addHead(7);
        list1.addTail(6); list2.addHead(9);
        list1.addTail(7); list2.addHead(8);

        cout << "List (I) of size " << list1.getSize() << ": ";
        list1.print();

        cout << "List (R) of size " << list1.getSize() << ": ";
        list1.printR();

        int t1 = list1.getTail(), t2 = list1.getTailR();
        cout << "Tail (I): " << t1 << ", Tail (R): " << t2 << endl;

        int h1 = list1.removeHead(), t3 = list1.removeTail();
        cout << "Removed head: " << h1 << ", tail: " << t3 << ", List: ";
        list1.print();

        int nth = 2, t4 = list1.removeNthFromTail(nth);
        cout << "Removed node [" << nth << "] from tail: " << t4 << ", List: ";
        list1.print();

        cout << "List 1: ";
        list1.print();
        cout << "List 2: ";
        list2.print();
        mergeLists(list1, list2);
        cout << "List 1 after merge: ";
        list1.print();
        cout << "List 2 after merge: ";
        list2.print();

        list1.reverse();
        cout << "Reverted list: ";
        list1.print();
        list1.reverse();
        cout << "Reverted back: ";
        list1.print();

        list1.unique();
        cout << "Removed duplicates: ";
        list1.print();

        SList list3, list4, list5;
        list3.addHead(8), list3.addHead(2), list3.addHead(4), list3.addHead(9), list3.addHead(9);
        list4.addTail(8), list4.addTail(5), list4.addTail(7);
        bitwiseSum(list3, list4, list5);
        cout << "Bitwise node sum (given in reverted order):" << endl;
        cout << "Number 1: "; list3.print();
        cout << "Number 2: "; list4.print();
        cout << "Sum is:   "; list5.reverse(); list5.print();

        SList list6;
        list6.addHead(9), list6.addHead(9), list6.addHead(4), list6.addHead(2), list6.addHead(8);
        bool b = list6.equals(list3);
        cout << "Is this list equals to \"Number 1\" (True/False)? " << (b ? "True: " : "False: ");
        list6.print();
        list6.addTail(1);
        b = list6.equals(list3);
        cout << "If added tail = 1? " << (b ? "True: " : "False: ");
        list6.print();
        list6.removeTail(); list6.addHead(1);
        b = list6.equals(list3);
        cout << "If removed tail and added head = 1? " << (b ? "True: " : "False: ");
        list6.print();
        list6.removeHead();
        b = list6.equals(list3);
        cout << "If removed head? " << (b ? "True: " : "False: ");
        list6.print();
        SList list61;
        b = list61.equals(list3);
        cout << "How about an empty one? " << (b ? "True: " : "False: ");
        list61.print();
    }
    cout << endl;
    system("PAUSE");

    cout << "== Binary Trees ==" << endl;
    {
        BSTree<int> t1;
        vector<int> init = { 8, 4, 2, 1, 6, 5, 16, 7, 12, 20, 24 };
        for (auto&& vi : init) t1.Insert(vi);

        cout << "Pre-order (original):  ";
        NodePrinter<int> np1;
        t1.TraversePreOrder(np1);
        np1.print();

        cout << "In-order:  ";
        NodePrinter<int> np2;
        t1.TraverseInOrder(np2);
        np2.print();

        cout << "Post-order: ";
        NodePrinter<int> np3;
        t1.TraversePostOrder(np3);
        np3.print();

        cout << "Min value: " << t1.GetMin() << endl;
        cout << "Max value: " << t1.GetMax() << endl;

        bool b1 = t1.HasValue(init[7]);
        auto b2 = t1.Dfs([&init](int value) { return value == init[7]; });
        cout << "Value " << init[7] << " is in the tree: " << (b1 ? "true" : "false") << " (Search), " <<
            (b2 != NULL && *b2 == init[7] ? "true" : "false") << " (DFS)" << endl;
        int n = 13;
        b1 = t1.HasValue(n);
        b2 = t1.Dfs([n](int value) { return value == n; });
        cout << "Value " << n << " is in the tree: " << (b1 ? "true" : "false") << " (Search), " <<
            (b2 != NULL && *b2 == n ? "true" : "false") << " (DFS)" << endl;

        bool is = t1.IsBsTree();
        cout << "Is binary search tree: " << (is ? "true" : "false") << endl;

        cout << "In breadth: ";
        NodePrinter<int> np4;
        t1.TraverseInBreadth(np4);
        np4.print();

        cout << "Mirrored: ";
        BSTree<int> t2(t1);
        t2.Mirror();
        NodePrinter<int> np5;
        t2.TraverseInOrder(np5);
        np5.print();

        cout << "All paths: ";
        PathFinder<int> pf1;
        t1.AllPaths(pf1);
        pf1.print();

        cout << "LCA: ";
        vector<pair<int, int>> nodes = { make_pair(1, 4), make_pair(6, 7), make_pair(16, 24), make_pair(7, 24),
            make_pair(4, 35), make_pair(0, 20), make_pair(29, 11), make_pair(48, 90), make_pair(0, 100) };
        for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            auto lca = t1.SearchLca(ni->first, ni->second);
            cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
                (ni != nodes.end() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "LCA 1 (non-BST): ";
        for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            auto lca = t1.SearchLcaNbst1(ni->first, ni->second);
            cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
                (ni != nodes.end() - 1 ? ", " : "");
        }
        cout << endl;

        cout << "LCA 2 (non-BST): ";
        for (auto ni = nodes.begin(); ni != nodes.end(); ++ni)
        {
            PairChecker<int> pc1(ni->first, ni->second);
            auto lca = t1.SearchLcaNbst2(pc1);
            cout << "(" << ni->first << "," << ni->second << ")-" << (lca != NULL ? to_string(*lca) : "?") <<
                (ni != nodes.end() - 1 ? ", " : "");
        }
        cout << endl;
    }
    cout << endl;
    system("PAUSE");

    cout << "== Graphs ==" << endl;
    {
        Graph<char, int> g1;
        vector<pair<pair<char, char>, int>> init1 =
        {
            make_pair(make_pair('a', 'b'), 3), make_pair(make_pair('a', 'c'), 2), make_pair(make_pair('c', 'b'), 1),
            make_pair(make_pair('b', 'd'), 4), make_pair(make_pair('b', 'd'), 4), make_pair(make_pair('b', 'd'), 5),
            make_pair(make_pair('f', 'e'), 1), make_pair(make_pair('e', 'd'), 3),
            make_pair(make_pair('g', 'h'), 7), make_pair(make_pair('i', 'h'), 9),
        };
        for (auto&& vi : init1)
        {
            g1.AddEdge(vi.first.first, vi.first.second, vi.second);
        }
        g1.AddVertex('k');

        cout << "DFT: ";
        GraphVertexPrinter<char, int> gvp1;
        g1.Dfs(gvp1);
        gvp1.print();

        cout << "BFT: ";
        GraphVertexPrinter<char, int> gvp2;
        g1.Bfs(gvp2);
        gvp2.print();

        cout << "Copy (DFT): ";
        Graph<char, int> g2(g1);
        GraphVertexPrinter<char, int> gvp3;
        g2.Dfs(gvp3);
        gvp3.print();
    }
    cout << endl;


	cout << "== C++ Various ==" << endl;
	{
		// Projection: std::transform one vector to another
		vector<pair<int, int>> vpii = { make_pair(1, 2), make_pair(3, 1), make_pair(5, 4), make_pair(7, 8) };
		vector<int> vt;
		transform(vpii.cbegin(), vpii.cend(), back_inserter(vt), [](const pair<int, int>& p) { return p.first; });
		cout << "Source: ";
		for (auto it = vpii.cbegin(); it != vpii.cend(); ++it)
		{
			cout << "(" + to_string(it->first) + "," + to_string(it->second) + ")" << (it != vpii.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Result: ";
		for (auto it = vt.cbegin(); it != vt.cend(); ++it)
		{
			cout << *it << (it != vt.cend() - 1 ? ", " : "");
		}
		cout << endl << endl;

		// Binary search
		vector<int> vi01 = { 1, 1, 2, 3, 5, 7, 7, 9, 10, 12, 15, 17 };
		auto bs1 = lower_bound(vi01.cbegin(), vi01.cend(), 7);
		auto bs2 = lower_bound(vi01.cbegin(), vi01.cend(), 12);
		auto bs3 = upper_bound(vi01.cbegin(), vi01.cend(), 7);
		auto bs4 = upper_bound(vi01.cbegin(), vi01.cend(), 12);
		auto bs5 = lower_bound(vi01.cbegin(), vi01.cend(), 4);
		auto bs6 = lower_bound(vi01.cbegin(), vi01.cend(), 21);
		auto bs7 = upper_bound(vi01.cbegin(), vi01.cend(), 4);
		auto bs8 = upper_bound(vi01.cbegin(), vi01.cend(), 21);

		cout << "Source (" + to_string(vi01.size()) + "): ";
		for (auto it = vi01.cbegin(); it != vi01.cend(); ++it)
		{
			cout << *it << (it != vi01.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Value: 7, lower_bound: [" << bs1 - vi01.cbegin() << "]" << endl;
		cout << "Value: 12, lower_bound: [" << bs2 - vi01.cbegin() << "]" << endl;
		cout << "Value: 7, upper_bound: [" << bs3 - vi01.cbegin() << "]" << endl;
		cout << "Value: 12, upper_bound: [" << bs4 - vi01.cbegin() << "]" << endl;
		cout << "Value: 4, lower_bound: [" << bs5 - vi01.cbegin() << "]" << endl;
		cout << "Value: 21, lower_bound: [" << bs6 - vi01.cbegin() << "]" << endl;
		cout << "Value: 4, upper_bound: [" << bs7 - vi01.cbegin() << "]" << endl;
		cout << "Value: 21, upper_bound: [" << bs8 - vi01.cbegin() << "]" << endl;
		cout << endl;
	}
	cout << endl;

    cout << "Program has completed" << endl;
    system("PAUSE");
    return 0;
}
