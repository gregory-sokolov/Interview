/// 
/// EPI. Chapter 11. Searching Problems
///

#include "pch.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

#include "Heaps.h"

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	cout << "- Most Frequent Items -" << endl;
	{
		unsigned top = 3;
		vector<vector<int>> tests =
		{
			{ },
			{ 0 },
			{ 0, 0 },
			{ 0, 1 },
			{ 0, 0, 0, 0, 0, 0, 0 },
			{ 0, 0, 1, 1, 1, 2, 4, 4, 4, 4, 4 },
			{ 0, 1, 1, 2, 2, 2, 3, 4, 4, 4, 5 },
			{ 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 4, 5, 5, 7 }
		};
		for (auto vi = tests.begin(); vi != tests.end(); ++vi)
		{
			string input;
			for (auto it = vi->cbegin(); it != vi->cend(); ++it)
			{
				input += to_string(*it) + (it != vi->cend() - 1 ? ", " : "");
			}
			cout << input << ": ";

			cout << "[";
			auto results = Heaps::MostFrequent(*vi, top);
			for (auto it = results.cbegin(); it != results.cend(); ++it)
			{
				cout << it->first << ":" << it->second << (it != results.end() - 1 ? ", " : "");
			}
			cout << "]" << endl;
		}
	}
	cout << endl;

	cout << "- Closest Points -" << endl;
	{
		unsigned k = 4;
		pair<double, double> origin(0.0, 0.0);
		vector<pair<double, double>> vdpi =
		{
			make_pair(2.7, 1.8), make_pair(2.0, 5.9), make_pair(3.7, 3.4), make_pair(9.2, 0.4), make_pair(7.2, 7.5),
			make_pair(5.2, 2.6), make_pair(1.1, 1.3), make_pair(1.5, 2.7), make_pair(3.3, 8.1), make_pair(0.1, 9.9),
			make_pair(0.0, 0.0), make_pair(10.0, 10.0), make_pair(-4.56, 7.89), make_pair(0.3579, -0.2468), make_pair(-5.5, -7.7)
		};
		vector<pair<double, double>> vdpr;
		Heaps::GetClosestPoints(k, origin, vdpi, vdpr);
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

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

