/// 
/// EPI. Chapter 13. Sorting
///

#include "stdafx.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#include "Threading.h"

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	cout << "== Threading ==" << endl << endl;

	cout << "- Buddy Chat -" << endl;
	{
		Threading::BuddyChat chat;
		Threading::BuddyChat::Buddy alice("Alice"), bob("Bob");
		std::thread t1([&] { chat.Talk(alice, bob, { "How are you?", "Bye" }); });
		std::thread t2([&] { chat.Talk(bob, alice, { "Hello", "Fine", "See you" }); });
		alice.say("Hi");
		t1.join();
		t2.join();
	}
	cout << endl;

	cout << "== Completed ==" << endl;
	system("PAUSE");
	return 0;
}

