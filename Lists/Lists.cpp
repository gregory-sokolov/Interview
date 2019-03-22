/// 
/// EPI. Chapter 7. Linked Lists
///

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

#include "Lists.h"

using namespace std;

int main()
{
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
		MergeLists(list1, list2);
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

		cout << "- Adding numbers -" << endl;
		SList list3, list4;
		list3.addTail(8), list3.addTail(2), list3.addTail(4), list3.addTail(9), list3.addTail(9);
		list4.addTail(9), list4.addTail(5), list4.addTail(7);
		cout << "Number 1: "; list3.print();
		cout << "Number 2: "; list4.print();
		list3.reverse(), list4.reverse();
		auto sum = AddNumbers(list3.getHeadNode(), list4.getHeadNode());
		SList list5(sum); list5.reverse();
		cout << "Sum: "; list5.print();

		SList list6;
		list6.addTail(8), list6.addTail(3), list6.addTail(4), list6.addTail(5), list6.addTail(6);
		bool b = list6.equals(list5);
		cout << "Is this list equals to previous sum? " << (b ? "True: " : "False: ");
		list6.print();
		list6.addTail(1);
		b = list6.equals(list5);
		cout << "If added tail = 1? " << (b ? "True: " : "False: ");
		list6.print();
		list6.removeTail(); list6.addHead(1);
		b = list6.equals(list5);
		cout << "If removed tail and added head = 1? " << (b ? "True: " : "False: ");
		list6.print();
		list6.removeHead();
		b = list6.equals(list5);
		cout << "If removed head? " << (b ? "True: " : "False: ");
		list6.print();
		SList list61;
		b = list61.equals(list5);
		cout << "How about an empty one? " << (b ? "True: " : "False: ");
		list61.print();
	}
	cout << endl;
	system("PAUSE");

    return 0;
}

