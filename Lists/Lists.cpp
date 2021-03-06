/// 
/// EPI. Chapter 7. Linked Lists
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>

#include "Lists.h"

using namespace std;

int main()
{
	cout << "== Linked lists ==" << endl;
	{
		cout << "- Basic operations -" << endl;
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
			cout << endl;

			cout << "List (R) of size " << list1.getSize() << ": ";
			list1.printR();
			cout << endl;

			int t1 = list1.getTail(), t2 = list1.getTailR();
			cout << "Tail (I): " << t1 << ", Tail (R): " << t2 << endl;

			int h1 = list1.removeHead(), t3 = list1.removeTail();
			cout << "Removed head: " << h1 << ", tail: " << t3 << ", List: ";
			list1.print();
			cout << endl;

			int nth = 2, t4 = list1.removeNthFromTail(nth);
			cout << "Removed node [" << nth << "] from tail: " << t4 << ", List: ";
			list1.print();
			cout << endl;

			list1.reverse();
			cout << "Reverted list: ";
			list1.print();
			cout << endl;
			list1.reverse();
			cout << "Reverted back: ";
			list1.print();
			cout << endl;

			list1.unique();
			cout << "Removed duplicates: ";
			list1.print();
			cout << endl;

			SList list5, list6;
			list5.addTail(8), list5.addTail(3), list5.addTail(4), list5.addTail(5), list5.addTail(6);
			list6.addTail(8), list6.addTail(3), list6.addTail(4), list6.addTail(5), list6.addTail(6);
			bool b = list6.equals(list5);
			cout << "Is this list equals to previous sum? " << (b ? "True: " : "False: ");
			list6.print();
			cout << endl;
			list6.addTail(1);
			b = list6.equals(list5);
			cout << "If added tail = 1? " << (b ? "True: " : "False: ");
			list6.print();
			cout << endl;
			list6.removeTail(); list6.addHead(1);
			b = list6.equals(list5);
			cout << "If removed tail and added head = 1? " << (b ? "True: " : "False: ");
			list6.print();
			cout << endl;
			list6.removeHead();
			b = list6.equals(list5);
			cout << "If removed head? " << (b ? "True: " : "False: ");
			list6.print();
			cout << endl;
			SList list7;
			b = list7.equals(list5);
			cout << "How about an empty one? " << (b ? "True: " : "False: ");
			list7.print();
			cout << endl;
		}
		cout << endl;

		cout << "- Adding numbers -" << endl;
		{
			SList list3, list4;
			list3.addTail(8), list3.addTail(2), list3.addTail(4), list3.addTail(9), list3.addTail(9);
			list4.addTail(9), list4.addTail(5), list4.addTail(7);
			cout << "Number 1: "; list3.print(); cout << endl;
			cout << "Number 2: "; list4.print(); cout << endl;
			list3.reverse(); list4.reverse();
			auto sum = Lists::AddNumbers(list3.getHeadNode(), list4.getHeadNode());
			SList list5(sum); list5.reverse();
			cout << "Sum: "; list5.print(); cout << endl;
		}
		cout << endl;

		cout << "- Merging sorted lists -" << endl;
		{
			vector<pair<vector<int>, vector<int>>> testListMerge =
			{
				{ {}, {} },
				{ { 0 }, {} },
				{ {}, { 0 } },
				{ { 1 }, { 9 } },
				{ { 9 }, { 1 } },
				{ { 0, 0, 0 }, { 0, 0, 0, 0 } },
				{ { 2, 5, 9 }, { 20, 25 } },
				{ { 29, 75 }, { 3, 11, 19 } },
				{ { 0, 2, 4, 6, 8, 10, 12 }, { 1, 3, 5, 7, 9, 11, 13, 15 } },
				{ { 2, 2, 7, 9, 12, 12, 15, 21 }, { 8, 9, 9, 11, 19, 19 } },
			};
			for (unsigned i = 0; i < testListMerge.size(); ++i)
			{
				cout << "Test " << setiosflags(ios::right) << setw(2) << setfill('0') << i << endl;
				SList list1(testListMerge[i].first), list2(testListMerge[i].second);
				cout << "L1: "; list1.print(); 
				cout << ", ";
				cout << "L2: "; list2.print();
				cout << endl;
				auto merged = Lists::MergeSortedLists(list1.getHeadNode(), list2.getHeadNode());
				list2.clear(); // List 2 no longer contains correct links because of in-place merge
				SList result(merged);
				cout << "Result: "; result.print();
				cout << endl;
			}
		}
		cout << endl;
	}
	cout << endl;
	system("PAUSE");

    return 0;
}

