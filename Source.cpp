//HW1 by Yuhao Chen
//SU Net ID:ychen436 SUID:603743399
//CIS554 HW1  Due: March 1 (Monday) at 11:59pm.
//All operations have to be directly performed on the DoublyLinkedList.
//You are not allowed to copy the node values to external structures, perform operations
//on the external structures, and copy the results back to the DoublyLinedList.

#include <iostream>
using namespace std;

class node {
public:
	int value;
	node* next;
	node* previous;
	//constructors to initialize object contents

	node(int i) { value = i; next = previous = nullptr; }
	node() { next = previous = nullptr; }
};

class DoublyLinkedList {
public:
	node* head;
	node* tail;
	//constructor
	DoublyLinkedList() { head = tail = nullptr; }
	DoublyLinkedList(int n, int m);
	void print_f();
	void print_r();
	DoublyLinkedList(const initializer_list<int>& I);
	void reverse();
	void sort();//You are only allowed to change next and previous of nodes, but not value;
	void remove_all(int k);//Remove all nodes with value k .

};

void DoublyLinkedList::remove_all(int k) {//Remove all nodes with value k;
	//Your code
	if (!head) return;
	auto current_node = head;
	if (!head->next) {
		if (head->value == k) {
			head = nullptr;
			tail = nullptr;
		}
		return;
	}
	while (current_node) {
		auto next_node = current_node->next;
		auto previous_node = current_node->previous;
		if (current_node->value == k) {
			if (!current_node->previous) {
				next_node->previous = nullptr;
				head = next_node;   //forgot this line
				delete current_node;
			}
			else if (!next_node) {
				previous_node->next = nullptr;
				tail = previous_node;   //forgot this line
				delete current_node;
			}
			else {
				previous_node->next = current_node->next;
				next_node->previous = previous_node;
				delete current_node;
			}
		}
		current_node = next_node;
	}
}

void DoublyLinkedList::sort() {
	//Your code
	//Using selection sort
	if (!head || !head->next) return;
	node* current_node{ head };
	while (current_node) {
		auto next_node = current_node->next;
		if (!next_node) return;
		auto previous_node = current_node->previous;
		auto min_node = current_node;
		auto p = current_node->next;
		while (p) {
			if (p->value < min_node->value) {
				min_node = p;
			}
			p = p->next;
		}

		//swap p0 (currrent node), p1 (selected node with min value)
		auto p0 = current_node;
		auto p0_p = p0->previous;
		auto p0_n = p0->next;
		auto p1 = min_node;
		auto p1_p = p1->previous;
		auto p1_n = p1->next;
		if (p0_n == p1) { // p0 is next to p1
			if (p0_p) p0_p->next = p1;
			else head = p1;
			p1->previous = p0_p;
			p1->next = p0;
			p0->previous = p1;
			p0->next = p1_n;
			if (p1_n) p1_n->previous = p0;
			else tail = p0;
		}
		else { // there are at least one node between p0 and p1
			if (p0_p) p0_p->next = p1;
			else head = p1;
			p1->previous = p0_p;
			p1->next = p0_n;
			if (p0_n) p0_n->previous = p1;
			if (p1_p) p1_p->next = p0;
			p0->previous = p1_p;
			p0->next = p1_n;
			if (p1_n) p1_n->previous = p0;
			else tail = p0;
		}
		current_node = p1->next;
	}
}


void DoublyLinkedList::reverse() {
	if (!head || !head->next) return;
	auto current_node = head;
	while (current_node) {
		auto current_next = current_node->next;
		current_node->next = current_node->previous;
		current_node->previous = current_next;
		current_node = current_next;

	}
	auto head1 = head;
	head = tail;
	tail = head1;

}

DoublyLinkedList::DoublyLinkedList(int n, int m) {//construct a linked list of n modes with values in 0..m-1
//Your code
	head = nullptr;
	tail = nullptr;
	if (n >= 1) {
		node* n1 = new node(rand() % m);
		n1->previous = nullptr;
		n1->next = nullptr;
		head = n1;
		tail = n1;
	}
	for (int i = 1; i < n; ++i) {
		node* n2 = new node(rand() % m);
		n2->next = head;
		n2->previous = nullptr;
		head->previous = n2;
		head = n2;
	}
}

DoublyLinkedList::DoublyLinkedList(const initializer_list<int>& I) : DoublyLinkedList() {
	//Your code
	auto n1{ I.end() - 1 };
	for (size_t i = 0; i < I.size(); ++i) {
		node* n2 = new node(*n1);
		n2->next = head;
		n2->previous = nullptr;
		if (head) { head->previous = n2; }
		head = n2;
		n1--;
	}
	if (head) {
		node* find_tail = head;
		while (find_tail->next) {
			find_tail = find_tail->next;
		}
		tail = find_tail;
	}
}


void DoublyLinkedList::print_f() {//print forward from head
//Your code
	auto current_node = head;
	while (current_node) {
		cout << current_node->value << " ";
		current_node = current_node->next;
	}
	cout << endl;
}
void DoublyLinkedList::print_r() {//print backward from tail
	//Your code
	auto current_node = tail;
	while (current_node) {
		cout << current_node->value << " ";
		current_node = current_node->previous;
	}
	cout << endl;
}


int main() {
	DoublyLinkedList L1(20, 10);
	L1.print_f();
	L1.print_r();
	L1.reverse();
	L1.print_f();
	L1.print_r();
	L1.remove_all(7);
	L1.print_f();
	L1.print_r();
	L1.sort();
	L1.print_f();
	L1.print_r();

	DoublyLinkedList L2{ 4,5,6,7,8 };//Declare and call initializer_list
	L2.print_f();//4 5 6 7 8
	L2.print_r();

//	DoublyLinkedList L3{ 1, 2, 3 };
//	L3.print_f();
//	L3.remove_all(1);
//	L3.print_f();
	return 0;
}