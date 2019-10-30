#pragma once

#include <vector>

// List node
struct ListNode
{
	ListNode* next = nullptr;
	int data = 0;

	ListNode() {}
	ListNode(int value) : data(value) {}
	ListNode(int value, ListNode* node) : data(value), next(node) {}
};

// Single linked list
class SList
{
public:
	SList() : _head(nullptr), _size(0) {}
	SList(ListNode* node) : SList()
	{
		ListNode* prev = nullptr;
		for (auto ni = node; ni; ni = ni->next) 
		{ 
			auto n = new ListNode(ni->data);
			if (_head == nullptr)
			{
				_head = n;
				prev = _head;
			}
			else
			{
				if (prev) 
				{
					prev->next = n;
				}
				prev = n;
			}
			++_size; 
		}
	}
	SList(std::vector<int> values) : SList()
	{
		for (const auto& vi : values)
		{
			addTail(vi);
		}
	}

	~SList()
	{
		if (_head == nullptr) return;
		ListNode* n = _head, *t = nullptr;
		while (n->next)
		{
			t = n;
			n = n->next;
			delete t;
		}
		_size = 0;
	}

	unsigned getSize() { return _size; }
	void clear() { _head = nullptr; _size = 0; }

	int getHead() { return _head ? _head->data : 0; }
	int getTail() { return _head ? tail_i(_head)->data : 0; }

	void addHead(int value)
	{
		ListNode* n = new ListNode(value);
		if (n)
		{
			if (_head)
			{
				n->next = _head;
			}
			_head = n;
			++_size;
		}
	}
	void addTail(int value)
	{
		ListNode* n = new ListNode(value);
		if (n)
		{
			ListNode* t = tail_i(_head);
			if (t)
			{
				t->next = n;
			}
			else
			{
				_head = n;
			}
			++_size;
		}
	}

	int removeHead()
	{
		if (!_head) return 0;

		ListNode* h = _head;
		_head = h->next;
		--_size;

		int d = h->data;
		delete h;
		return d;
	}
	int removeTail()
	{
		if (!_head) return 0;

		ListNode* pt = _head;
		for (unsigned i = 0; i < _size - 2; ++i, pt = pt->next);

		ListNode* t = pt->next;
		pt->next = nullptr;
		--_size;

		int d = t->data;
		delete t;
		return d;
	}

	// MS Question
	void reverse()
	{
		ListNode* n = _head, *p = nullptr, *t = nullptr;
		while (n)
		{
			t = n->next;
			n->next = p;
			p = n;
			n = t;
		}
		_head = p;
	}

	// MS Question (list.erase(std::unique(list.begin(), list.end()), list.end()))
	void unique()
	{
		for (ListNode* i = _head; i; i = i->next)
		{
			ListNode* j = i->next, *p = i;
			while (j)
			{
				if (i->data == j->data)
				{
					p->next = j->next;
					delete j;
					j = p->next;
				}
				else
				{
					j = j->next;
					p = p->next;
				}
			}
		}
	}

	bool equals(SList& l)
	{
		if (l.getSize() != _size) return false;
		for (ListNode* i = l.getHeadNode(), *j = _head; i && j; i = i->next, j = j->next)
		{
			if (i->data != j->data) return false;
		}
		return true;
	}


	// MS Question
	int removeNthFromTail(unsigned nth)
	{
		ListNode* pt = _head;
		for (unsigned i = 0; i < _size - nth - 1; ++i, pt = pt->next);

		ListNode* t = pt->next;
		pt->next = t->next;
		--_size;

		int d = t->data;
		delete t;
		return d;
	}

	// Test methods
	ListNode* getHeadNode() { return _head; }
	int getTailR() { return _head ? tail_r(_head)->data : 0; }
	void print()
	{
		if (_head == nullptr)
		{
			std::cout << "-";
		}
		for (ListNode* n = _head; n; n = n->next)
		{
			std::cout << n->data << (n->next ? "-" : "");
		}
	}
	void print(ListNode* node)
	{
		if (node == nullptr)
		{
			std::cout << "-";
		}
		for (auto n = node; n; n = n->next)
		{
			std::cout << n->data << (n->next ? "-" : "");
		}
	}
	void printR()
	{
		print_r(_head);
	}

private:
	ListNode* _head;
	unsigned _size;

	ListNode* tail_i(ListNode* n)
	{
		ListNode* t = n;
		while (t && t->next)
		{
			t = t->next;
		}
		return t;
	}
	ListNode* tail_r(ListNode* n)
	{
		if (n && n->next)
		{
			return tail_r(n->next);
		}
		return n;
	}

	void print_r(ListNode* n)
	{
		if (n)
		{
			std::cout << n->data << (n->next ? "-" : "");
			print_r(n->next);
		}
	}
};

///
/// EPI. Chapter 7. Lists
///
class Lists
{
public:
	/// EPI 7.0. Adds two integers represented as singly linked lists
	/// Adding digits one by one, moving the carry to the next partial sum.
	/// Time: O(n), space: O(n)
	static ListNode* AddNumbers(ListNode* l1, ListNode* l2)
	{
		ListNode* result = nullptr;

		unsigned dec = 0;
		for (ListNode* li = l1, *lj = l2, *ln = result;
			 li || lj || dec > 0;
			 li = li ? li->next : li, lj = lj ? lj->next : lj)
		{
			auto sum = (li ? li->data : 0) + (lj ? lj->data : 0) + dec;
			auto node = new ListNode(sum % 10);
			if (ln == nullptr)
			{
				result = ln = node;
			}
			else
			{
				ln->next = node;
				ln = ln->next;
			}
			dec = sum / 10;
		}

		return result;
	}

	/// EPI 7.1. Merges two sorted singly linked lists
	/// Performs in-place merge of two lists.
	/// We consider the list with the smallest head node as a destination and the other one as a source.
	/// We move along the first list and compare its node values with the destination head,
	/// and whenever we encounter a greater value, we link the head into the source and then exchange src and dst.
	/// Continuing until either of lists is empty and in the end appending the second list's remainder if it exists.
	/// Time: O(n), space: O(1)
	static ListNode* MergeSortedLists(ListNode* l1, ListNode* l2)
	{
		// Validity checks
		if (l1 == nullptr && l2 == nullptr) return nullptr;
		if (l1 != nullptr && l2 == nullptr) return l1;
		if (l1 == nullptr && l2 != nullptr) return l2;

		// Tracking pointers
		ListNode* cr1 = l1, *cr2 = l2;
		if (cr1->data > cr2->data)
		{
			// Pick the smallest head
			cr1 = l2;
			cr2 = l1;
		}

		ListNode* result = cr1;
		while (cr1)
		{
			if (cr1->next && cr2)
			{
				if (cr1->next->data > cr2->data)
				{
					// Relink nodes
					ListNode* tmp = cr1->next;
					cr1->next = cr2;
					cr1 = cr2;
					cr2 = tmp;
				}
				else
				{
					cr1 = cr1->next;
				}
			}
			else
			{
				// End of list
				if (cr2)
				{
					// Append l2 remainder
					cr1->next = cr2;
					cr1 = nullptr;
				}
				else
				{
					cr1 = cr1->next;
				}
			}
		}

		return result;
	}
};