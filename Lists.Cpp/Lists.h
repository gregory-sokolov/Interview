#pragma once

// List node
struct ListNode
{
	ListNode* next;
	int data;

	ListNode() : data(0), next(NULL) {}
	ListNode(int value) : data(value), next(NULL) {}
	ListNode(int value, ListNode* node) : data(value), next(node) {}
};

// Single linked list
class SList
{
public:
	SList() : head(NULL), size(0) {}
	~SList()
	{
		if (!head) return;
		ListNode* n = head, *t = NULL;
		while (n->next)
		{
			t = n;
			n = n->next;
			delete t;
		}
		size = 0;
	}

	unsigned getSize() { return size; }
	void clear() { head = NULL; size = 0; }

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
		pt->next = NULL;
		--size;

		int d = t->data;
		delete t;
		return d;
	}

	// MS Question
	void reverse()
	{
		ListNode* n = head, *p = NULL, *t = NULL;
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

// MS Question
ListNode* getListTail(ListNode* n)
{
	if (n->next)
	{
		return getListTail(n->next);
	}
	return n;
}

void mergeLists(SList& l1, SList& l2)
{
	getListTail(l1.getHeadNode())->next = l2.getHeadNode();
	l2.clear();
}

// MS Question
void bitwiseSum(SList& l1, SList& l2, SList& l3)
{
	l1.reverse(), l2.reverse(); // optional and conventional

	unsigned radix = 10, sum = 0, s = 0, c = 0;
	for (ListNode* n1 = l1.getHeadNode(), *n2 = l2.getHeadNode(); n1 || n2;
		n1 = n1 ? n1->next : NULL, n2 = n2 ? n2->next : NULL)
	{
		sum = (n1 ? n1->data : 0) + (n2 ? n2->data : 0) + c;
		s = sum%radix, c = sum / radix;
		l3.addHead(s);
	}
	if (c) l3.addHead(1);
}