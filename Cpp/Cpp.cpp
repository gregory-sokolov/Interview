// 
// C++: Exercises
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

#include "Cpp.h"

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

		// STL: std::transform one vector to another
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

		// STL: binary search
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
