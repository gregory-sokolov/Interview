// Structures.Cpp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "Structures.h"

using namespace std;

int main()
{
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
				lru1.Put(to_string(*it), *it);
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

	cout << "Program has completed" << endl;
	system("PAUSE");
	return 0;
}

