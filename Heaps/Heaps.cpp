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
	cout << "- K-th largest item -" << endl;
	{
		vector<pair<unsigned, vector<int>>> tests =
		{
			{ 0, {} },
			{ 2, {} },

			{ 0, { 0 } },
			{ 1, { 0 } },
			{ 2, { 0 } },

			{ 0, { 0, 0 } },
			{ 1, { 0, 0 } },
			{ 2, { 0, 0 } },

			{ 0, { 1, 2 } },
			{ 1, { 1, 2 } },
			{ 2, { 1, 2 } },
			{ 3, { 1, 2 } },

			{ 1, { 2, 1, 3 } },
			{ 2, { 2, 1, 3 } },
			{ 3, { 2, 1, 3 } },
			{ 4, { 2, 1, 3 } },

			{ 3, { 7, 2, 9, 1, 12, 8, 3, 15, 0, -1, -2, 7, 2, 19 } },
			{ 5, { 7, 2, 9, 1, 12, 8, 3, 15, 0, -1, -2, 7, 2, 19 } },
			{ 7, { 7, 2, 9, 1, 12, 8, 3, 15, 0, -1, -2, 7, 2, 19 } }
		};
		for (auto vi = tests.begin(); vi != tests.end(); ++vi)
		{
			cout << "k = " << vi->first << endl;
			if (!vi->second.empty())
			{
				for (unsigned i = 0; i < vi->second.size(); ++i)
				{
					cout << setiosflags(ios::right) << setw(2) << vi->second[i] << (i != vi->second.size() - 1 ? ", " : "");
				}
			}
			else
			{
				cout << "[]";
			}
			cout << endl;

			auto result = Heaps::KthLargest(vi->second, vi->first);
			if (!result.empty())
			{
				for (unsigned i = 0; i < result.size(); ++i)
				{
					cout << setiosflags(ios::right) << setw(2) << result[i] << (i != result.size() - 1 ? ", " : "");
				}
			}
			else
			{
				cout << "[]";
			}
			cout << endl;

			if (vi != tests.cend() - 1)
			{
				cout << "--" << endl;
			}
		}
	}
	cout << endl;

	cout << "- Online median -" << endl;
	{
		vector<vector<int>> tests =
		{
			{ },
			{ 0 },
			{ 0, 0 },
			{ 0, 1 },
			{ 1, 2 },
			{ 2, 1 },
			{ 1, 2, 3 },
			{ 2, 1, 3 },
			{ 3, 2, 1 },
			{ 3, 1, 2 },
			{ 7, 2, 9, 1, 12, 8, 3, 15, 0, -1, -2, 7, 2, 19 }
		};
		for (auto vi = tests.begin(); vi != tests.end(); ++vi)
		{
			for (unsigned i = 0; i < vi->size(); ++i)
			{
				cout << setiosflags(ios::right) << setw(3) << (*vi)[i] << (i != vi->size() - 1 ? ", " : "");
			}
			cout << endl;

			auto result = Heaps::OnlineMedian(*vi);
			for (unsigned i = 0; i < result.size(); ++i)
			{
				cout << setiosflags(ios::right) << setw(3) << setprecision(2) << 
					result[i] << (i != result.size() - 1 ? ", " : "");
			}
			cout << endl;

			if (vi != tests.cend() - 1)
			{
				cout << "--" << endl;
			} 
		}
	}
	cout << endl;

	cout << "- Closest points -" << endl;
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

