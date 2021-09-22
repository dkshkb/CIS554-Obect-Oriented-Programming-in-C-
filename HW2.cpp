//HW2 by Yuhao Chen

//HW2 Due: March 11, Thursday, at 11:59pm
//Implement three member functions of class Tree: 
//mirrorCopy, minHeap, and sort.

#include <iostream>
#include <string>
using namespace std;
//int m = 50;
class Node {
public:
	int value;
	Node* l_child;
	Node* r_child;
	Node() : l_child(nullptr), r_child(nullptr) {}
	Node(int i) :value(i), l_child(nullptr), r_child(nullptr) {}

};



class Tree { //an n-level full binary tree of 2^n - 1 nodes
public:
	Node* root;
	Tree() : root(nullptr) {}
	Node* makeTree(int n, int m);
	void printTree1(Node* p); //in-order printing
	void printTree2(Node* p); //pre-order printing
	void printTree3(Node* p); //post-order printing
	void mirror(Node* p);
	int sum(Node* p);



	/*
	HW2: Implement the following three member functions.
	*/

	Node* mirrorCopy(Node* p);//5 points
	//Create an external mirror copy of a tree rooted at a node pointed by p
	//and return a pointer pointing to the root of this external tree.
	//Note that the function will not change the original tree.
	//You are required to implement this function with recursion.


	void minHeap(Node* p);//8 points
	//Recall that in a Min Heap, at all nodes, 
	//value(parent)<= value(l_child) and value(parent) <= value(r_child).
	//This function re-structures the tree, whose root is pointed by p, into a Min Heap.
	//You are required to use recursion.

	pair<Node*, Node* >  sort(Node* p);//22 points
	//sorting such that
	//ascending sequence in pre-order traversal
	//This function returns a pair of pointers,  which point to the node with the smallest
	//value and the node with the largest values in the tree rooted at node pointed by p .
	//printTree2 will give a sorted sequence.
	//You are required to use recursion, but additional while loop is allowed.
};

Node* Tree::mirrorCopy(Node* p) {

	//Your code
	Node* treeCopy = new Node();
	if (!p || !p->l_child) return p;
	else {
		treeCopy->value = p->value;
		treeCopy->l_child = mirrorCopy(p->r_child);
		treeCopy->r_child = mirrorCopy(p->l_child);
	}

	return treeCopy;
}
void Tree::minHeap(Node* p) {
	if (!p || !(p->l_child)) return;
	minHeap(p->l_child);
	minHeap(p->r_child);
	if (p->value > p->l_child->value || p->value > p->r_child->value) {
		if (p->l_child->value <= p->r_child->value) {
			swap(p->value, p->l_child->value);
			minHeap(p->l_child);
		}
		else {

			swap(p->value, p->r_child->value);
			minHeap(p->r_child);
		}
	}

}
pair<Node*, Node* >  Tree::sort(Node* p) {

	//Your code
	pair<Node*, Node* > ret;
	if (!p->l_child | !p) {
		ret.first = p;
		ret.second = p;
		return ret;
	}

	while (true) {

		if (p->value > p->r_child->value) {
			swap(p->value, p->r_child->value);
		}

		if (p->value > p->l_child->value) {
			swap(p->value, p->l_child->value);
		}

		if (p->r_child->value < p->l_child->value) {
			swap(p->l_child->value, p->r_child->value);
		}

		auto left = sort(p->l_child);
		auto right = sort(p->r_child);

		if (left.second->value > right.first->value) {
			swap(left.second->value, right.first->value);
		}

		auto left1 = sort(p->l_child);
		auto right1 = sort(p->r_child);

		if (p->value <= p->l_child->value && p->l_child->value <= p->r_child->value && left.second->value <= right.first->value) {
			break;
		}
	}

	ret.first = p;
	ret.second = new Node();
	ret.second = p;
	while (ret.second->r_child) {
		ret.second = ret.second->r_child;
	}

	return ret;
}




int Tree::sum(Node* p) {
	if (!p) return 0;
	if (!p->l_child) return p->value;
	return p->value + sum(p->l_child) + sum(p->r_child);
}

void Tree::mirror(Node* p) {
	if (!p || !p->l_child) return;
	mirror(p->l_child);
	mirror(p->r_child);
	swap(p->l_child, p->r_child);
}



Node* Tree::makeTree(int n, int m) { //Create an n-level full binary tree with 
							  //with random values between 0 ... m-1
							  //and returns a pointer to the root.

	Node* p = new Node(rand() % m);
	if (n == 1) return p;
	p->l_child = makeTree(n - 1, m);
	p->r_child = makeTree(n - 1, m);
	return p;
}

void Tree::printTree1(Node* p) { //in-order printing
	if (p == nullptr) return;
	printTree1(p->l_child);
	cout << p->value << " ";
	printTree1(p->r_child);
}

void Tree::printTree2(Node* p) { //pre-order printing

	if (p == nullptr) return;
	cout << p->value << " ";
	printTree2(p->l_child);
	printTree2(p->r_child);
}
void Tree::printTree3(Node* p) { //post-order printing
	if (p == nullptr) return;
	printTree3(p->l_child);
	printTree3(p->r_child);
	cout << p->value << " ";
}


int main() {
	Tree T1;
	T1.root = T1.makeTree(4, 20);
	T1.printTree1(T1.root);
	cout << endl;
	T1.printTree2(T1.root);
	cout << endl;
	T1.printTree3(T1.root);
	cout << endl;
	Tree T2;
	T2.root = T1.mirrorCopy(T1.root);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;

	T2.minHeap(T2.root);
	T2.printTree1(T2.root);
	cout << endl;
	T2.printTree2(T2.root);
	cout << endl;
	T2.printTree3(T2.root);
	cout << endl;

	Tree T3;
	T3.root = T3.makeTree(5, 20);
	T3.sort(T3.root);

	T3.printTree1(T3.root);
	cout << endl;
	T3.printTree2(T3.root);
	cout << endl;
	T3.printTree3(T3.root);
	cout << endl;

	cout << "*******************************************" << endl;
	Tree test;
	test.root = test.makeTree(7, 40);
	test.printTree2(test.root);
	cout << endl;
	Tree test2;
	test2.root = test.mirrorCopy(test.root);
	cout << "mirror copy: ";
	test2.printTree2(test2.root);
	cout << endl;
//	cout << "minheap: ";
///	test.minHeap(test.root);
//	test.printTree2(test.root);
//	cout << endl;
	cout << "sort: ";
	test.sort(test.root);
	test.printTree2(test.root);



	return 0;
}
