#pragma once

// List node
struct ListNode
{
	ListNode* next;
	int data;

	ListNode() : data(0), next(nullptr) {}
	ListNode(int value) : data(value), next(nullptr) {}
	ListNode(int value, ListNode* node) : data(value), next(node) {}
};

// Single linked list
class SList
{
public:
	SList() : head(nullptr), size(0) {}
	SList(ListNode* node) : head(node), size(node ? 1 : 0)
	{
		for (auto ni = node; ni->next; ni = ni->next) { ++size; }
	}
	~SList()
	{
		if (!head) return;
		ListNode* n = head, *t = nullptr;
		while (n->next)
		{
			t = n;
			n = n->next;
			delete t;
		}
		size = 0;
	}

	unsigned getSize() { return size; }
	void clear() { head = nullptr; size = 0; }

	int getHead() { return head ? head->data : 0; }
	int getTail() { return head ? tail_i(head)->data : 0; }

	void addHead(int value)
	{
		ListNode* n = new(std::nothrow) ListNode(value);
		if (n)
		{
			if (head)
			{
				n->next = head;
			}
			head = n;
			++size;
		}
	}
	void addTail(int value)
	{
		ListNode* n = new(std::nothrow) ListNode(value);
		if (n)
		{
			ListNode* t = tail_i(head);
			if (t)
			{
				t->next = n;
			}
			else
			{
				head = n;
			}
			++size;
		}
	}

	int removeHead()
	{
		if (!head) return 0;

		ListNode* h = head;
		head = h->next;
		--size;

		int d = h->data;
		delete h;
		return d;
	}
	int removeTail()
	{
		if (!head) return 0;

		ListNode* pt = head;
		for (unsigned i = 0; i < size - 2; ++i, pt = pt->next);

		ListNode* t = pt->next;
		pt->next = nullptr;
		--size;

		int d = t->data;
		delete t;
		return d;
	}

	// MS Question
	void reverse()
	{
		ListNode* n = head, *p = nullptr, *t = nullptr;
		while (n)
		{
			t = n->next;
			n->next = p;
			p = n;
			n = t;
		}
		head = p;
	}

	// MS Question (list.erase(std::unique(list.begin(), list.end()), list.end()))
	void unique()
	{
		for (ListNode* i = head; i; i = i->next)
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
		if (l.getSize() != size) return false;
		for (ListNode* i = l.getHeadNode(), *j = head; i && j; i = i->next, j = j->next)
		{
			if (i->data != j->data) return false;
		}
		return true;
	}

	// Test methods
	ListNode* getHeadNode() { return head; } // it's an iterator
	int getTailR() { return head ? tail_r(head)->data : 0; }
	void print()
	{
		for (ListNode* n = head; n; n = n->next)
		{
			std::cout << n->data << (n->next ? "->" : "");
		}
		std::cout << std::endl;
	}
	void printR()
	{
		print_r(head);
		std::cout << std::endl;
	}
	// MS Question
	int removeNthFromTail(unsigned nth)
	{
		ListNode* pt = head;
		for (unsigned i = 0; i < size - nth - 1; ++i, pt = pt->next);

		ListNode* t = pt->next;
		pt->next = t->next;
		--size;

		int d = t->data;
		delete t;
		return d;
	}

private:
	ListNode* head;
	unsigned size;

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
			std::cout << n->data << (n->next ? "->" : "");
			print_r(n->next);
		}
	}
};

/// Finds list tails
ListNode* GetListTail(ListNode* n)
{
	if (n->next)
	{
		return GetListTail(n->next);
	}
	return n;
}

/// Merges two lists
void MergeLists(SList& l1, SList& l2)
{
	GetListTail(l1.getHeadNode())->next = l2.getHeadNode();
	l2.clear();
}

/// EPI 7.0. Adds two integers represented as singly linked lists
/// Adding digits one by one, moving the carry to the next partial sum.
/// Time: O(n), space: O(n)
ListNode* AddNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* result = nullptr;

	unsigned dec = 0;
	for (ListNode* li = l1, *lj = l2, *ln = result; li || lj || dec > 0; li = li ? li->next : li, lj = lj ? lj->next : lj)
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