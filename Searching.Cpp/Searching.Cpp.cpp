/// 
/// EPI. Chapter 11. Searching Problems
///

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <map>

#include "Searching.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "- Linear: Two Maximums -" << endl;
	{
		vector<int> vi01 = { 1, 7, -2, 6, 12, 7, 7, 3, 10, -8, 16, 0 };
		auto result = Searching::FindTwoMaximums(vi01);

		cout << "Source (" + to_string(vi01.size()) + "): ";
		for (auto it = vi01.cbegin(); it != vi01.cend(); ++it)
		{
			cout << *it << (it != vi01.cend() - 1 ? ", " : "");
		}
		cout << endl;
		cout << "Result: (" << to_string(result.first) << ", " << to_string(result.second) << ")" << endl;
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

