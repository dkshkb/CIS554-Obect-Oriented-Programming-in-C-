//HW4 by Yuhao Chen
//SU Net ID: ychen436 SUID: 603743399
//Due : April 6, Tuesday


#include <iostream>
#include <vector>
//#include <list>
//#include <string>

using namespace std;
template <class T> class ThreeD {
public:
	T ht;
	T wid;
	T dep;
	ThreeD() :ht(0), wid(0), dep(0) {}
	ThreeD(T i, T j, T k) :ht(i), wid(j), dep(k) {}
	T getVol() const { return ht * wid * dep; }
	bool operator==(const ThreeD<T>& t) { return getVol() == t.getVol(); }
};

template <class T> class node {
public:
	T value;
	node<T>* next;
	node<T>* previous;
	node<T>() { next = nullptr; previous = nullptr; }
	node<T>(T v) { value = v; next = nullptr; previous = nullptr; }
	bool operator==(const node<T>& t) const { return value == t.value; }
};

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);

template <class T> class linked_list {
public:
	node<T>* head;
	node<T>* tail;
	linked_list() { head = tail = nullptr; }
	linked_list(const initializer_list<T>& V);
	void push_front(T t);
	void push_back(T t);
	bool operator==(const linked_list<T>& L) const;

	linked_list(const linked_list<T>& L); //copy constructor
	linked_list(linked_list<T>&& L); //move constructor
	~linked_list();//destructor
	void operator=(const linked_list<T>& L);//L-value operator=; copy assignment
	void operator=(linked_list<T>&& L);//R-value operator= ; move assignment
	template <class T> friend ostream& operator<<(ostream& str, const linked_list<T>& L);
};

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L);

template <class T> linked_list<T>::linked_list(const initializer_list<T>& V) : linked_list() {
	//Your code

	/*if (V.size() == 0) {
	
		head = tail = nullptr;
	}
	else if (V.size() == 1) {

		head = tail = new node<T>(*(V.begin()));
	}
	else {
	
		head = tail = new node<T>(*(V.begin()));
		node<T>* curr_node = head;
		for (int i = 0; i < V.size() - 1; i++) {
		
			node<T>* p1 = new node<T>(*(V.begin() + 1 + i));
			tail = p1;
			curr_node->next = p1;
			p1->previous = curr_node;
			curr_node = curr_node->next;
		}
	}*/

	for (T i : V) {
	
		this->push_back(i);
	}

	cout << "initializer_list LL" << endl;
}

template <class T> linked_list<T>::~linked_list() {  //destructor										
	//Your code
	while (head != nullptr) {
	
		node<T>* p1 = head->next;
		delete head;
		head = p1;
	}
	cout << "Destructor LL" << endl;
}

template <class T> linked_list<T>::linked_list(const linked_list<T>& L) : linked_list() { //copy constructor																			  																		  //num_nodes = 0;
	//Your code
	if (L.head == nullptr) {
	
		head = tail = nullptr;
	}
	else {
		node<T>* it = L.head;
		while (it != nullptr) {
		
			this->push_back(it->value);
			it = it->next;
		}
	}
	cout << "Copy Constructor LL" << endl;
}
template <class T> linked_list<T>::linked_list(linked_list<T>&& L) {//move constructor
	//Your code
	head = L.head;
	L.head = nullptr;
	cout << "Move Constructor LL" << endl;
}

template <class T> void linked_list<T>::operator=(const linked_list<T>& L) { //Lvalue operator=
//Your code
	//delete
	while (head != nullptr) {

		node<T>* p1 = head->next;
		delete head;
		head = p1;
	}
	//do the assignment
	if (L.head == nullptr) {

		head = tail = nullptr;
	}
	else {
		node<T>* it = L.head;
		while (it != nullptr) {

			this->push_back(it->value);
			it = it->next;
		}
	}

	cout << "Copy Assignment LL" << endl;

}

template<class T> void linked_list<T>::operator=(linked_list<T>&& L) {//R-value operator=
	//Your code
	//delete
	while (head != nullptr) {

		node<T>* p1 = head->next;
		delete head;
		head = p1;
	}

	//do the assignment
	head = L.head;
	L.head = nullptr;

	cout << "Move Assignment LL" << endl;
}


template <class T> void linked_list<T>::push_front(T t) {
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }
	else {
		p->next = head;
		head->previous = p;
		head = p;
	}
}

template <class T> void linked_list<T>::push_back(T t)
{
	node<T>* p = new node<T>(t);
	if (head == nullptr) { head = tail = p; }

	else {
		p->previous = tail;
		tail->next = p;
		tail = p;
	}
}

template <class T> bool linked_list<T>::operator==(const linked_list<T>& L) const {
	//Your code
	cout << "operator== LL" << endl;

	if (head == nullptr) {
	
		if (L.head == nullptr) return true;
		else return false;
	}
	else {
	
		if (L.head == nullptr) return false;
		node<T>* it1 = head;
		node<T>* it2 = L.head;
		while (it1 != nullptr) {
		
			if (it2 == nullptr) return false;
			if (!(it1->value == it2->value)) return false;
			it1 = it1->next;
			it2 = it2->next;
		}
		if (it2 == nullptr)  return true;
		else return false;
	}

}

template <class X> class NODE {
public:
	X value;
	NODE<X>* l_child;
	NODE<X>* r_child;
	NODE<X>* next;
	NODE<X>() : l_child(nullptr), r_child(nullptr), next(nullptr) {}
	NODE<X>(X t) : l_child(nullptr), r_child(nullptr), next(nullptr), value(t) {}
};

template <class X> class Triangle {
public:
	NODE<X>* head;
	Triangle() : head(nullptr) {};
	Triangle(const initializer_list<initializer_list<X>>& I);//initializer_list
	~Triangle();// {};//destructor
	Triangle(const Triangle<X>& T); //copy constructor
	void operator=(const Triangle<X>& T); //copy assignment (Lvalue assignment)
	Triangle<X> ThreeTimes(); //ThreeTimes
	Triangle(Triangle<X>&& T);//move constructor
	void operator=(Triangle<X>&& T);//move assignment (Rvalue assignment)
	bool operator==(const Triangle<X>& T);
};

template <class X> bool Triangle<X>::operator==(const Triangle<X>& T) {
	//Your code
	//find the number of levels of the triangle
	if (head == nullptr) {
	
		if (T.head == nullptr) return true;
		else return false;
	}
	if (T.head == nullptr) {

		if (head == nullptr) return true;
		else return false;
	}

	NODE<X>* h = T.head;
	int level1 = 1;
	while (h->l_child != nullptr) {

		level1++;
		h = h->l_child;
	}
	
	h = head;
	int level2 = 1;
	while (h->l_child != nullptr) {

		level2++;
		h = h->l_child;
	}

	if (level1 != level2) return false;
	int level = level1;

	// do the comparison
	NODE<X>* it1 = T.head;
	NODE<X>* it2 = head;
	for (int i = 1; i <= level; i++) {
	
		NODE<X>* it3 = it1;
		NODE<X>* it4 = it2;
		for (int j = 0; j < i; j++) {
		
			if (!(it3->value == it4->value)) return false;

			it3 = it3->next;
			it4 = it4->next;
		}

		it1 = it1->l_child;
		it2 = it2->l_child;
	}

	return true;
}


template <class X> void Triangle<X>::operator=(Triangle<X>&& T) {//Move assignment (Rvalue assignment)
	//Your code

	//delete the current Triangle
	if (head != nullptr) {

		int curr_level = 1;
		while (head != nullptr) {

			NODE<X>* next_level = head->l_child;
			//delete this level
			for (int i = 0; i < curr_level; i++) {

				NODE<X>* next_p = head->next;
				delete head;
				head = next_p;
			}
			curr_level++;
			head = next_level;
		}
	}

	//Do the move assignment
	head = T.head;
	T.head = nullptr;
	cout << "Move Assignment Triangle" << endl;
}

template <class X> Triangle<X>::Triangle(Triangle<X>&& T) {//move constructor
	//Your code
	head = T.head;
	T.head = nullptr;
	cout << "Move Constructor Triangle" << endl;

}

template <class X> Triangle<X> Triangle<X>::ThreeTimes() {//ThreeTimes
	//Your code

	Triangle<X> temp{ *this }; //copy constructor
	
	if (temp.head == nullptr) return temp;

	//find the number of levels of the triangle
	NODE<X>* h = temp.head;
	int level = 1;
	while (h->l_child != nullptr) {

		level++;
		h = h->l_child;
	}

	//do the three times
	NODE<X>* level_ptr = temp.head;
	for (int i = 1; i <= level; i++) {
	
		NODE<X>* it = level_ptr;
		for (int j = 0; j < i; j++) {
		
			it->value = it->value * 3;
			it = it->next;
		}
		
		level_ptr = level_ptr->l_child;
	}

	cout << "ThreeTimes Triangle" << endl;
	return temp;

	//******************************

	//if (head == nullptr) return *this;

	////find the number of levels of the triangle
	//NODE<X>* h = head;
	//int level = 1;
	//while (h->l_child != nullptr) {

	//	level++;
	//	h = h->l_child;
	//}

	////do the three times
	//NODE<X>* level_ptr = head;
	//for (int i = 1; i <= level; i++) {

	//	NODE<X>* it = level_ptr;
	//	for (int j = 0; j < i; j++) {

	//		it->value = it->value * 3;
	//		it = it->next;
	//	}

	//	level_ptr = level_ptr->l_child;
	//}

	//cout << "ThreeTimes Triangle" << endl;
	//return *this;
}

template <class X> Triangle<X>::~Triangle() {// {};//destructor
	//Your code

	if (head != nullptr) {
	
		//find the number of levels of the triangle
		NODE<X>* h = head;
		int level = 1;
		while (h->l_child != nullptr) {

			level++;
			h = h->l_child;
		}

		for (int curr_level = 1; curr_level <= level; curr_level++) {

			NODE<X>* next_level = head->l_child;
			//delete this level
			for (int i = 0; i < curr_level; i++) {

				NODE<X>* next_p = head->next;
				//cout << "delete " << head->value << " ";
				delete head;
				head = next_p;
			}
			//cout << endl;
			head = next_level;
		}
	}
	cout << "Destructor Triangle" << endl;

}

template <class X> void Triangle<X>::operator=(const Triangle<X>& T) {//copy assignment
	//Your code
	
	//delete the current Triangle
	if (head != nullptr) {

		int curr_level = 1;
		while (head != nullptr) {

			NODE<X>* next_level = head->l_child;
			//delete this level
			for (int i = 0; i < curr_level; i++) {

				NODE<X>* next_p = head->next;
				delete head;
				head = next_p;
			}
			curr_level++;
			head = next_level;
		}
	}

	//Do the copy assignment
	NODE<X>* h = T.head;
	int level;
	if (h == nullptr) level = 0;
	else level = 1;
	while (h->l_child != nullptr) {

		level++;
		h = h->l_child;
	}

	if (level == 0) {
		head = nullptr;
	}
	else if (level == 1) {

		head = new NODE<X>((T.head)->value);
		head->next = head;
	}
	else {

		head = new NODE<X>((T.head)->value);
		head->next = head;
		head->l_child = new NODE<X>(((T.head)->l_child)->value);
		head->r_child = new NODE<X>(((T.head)->r_child)->value);
		head->l_child->next = head->r_child;
		head->r_child->next = head->l_child;

		NODE<X>* curr_level_first = (T.head)->l_child;
		NODE<X>* new_cur_level_first = head->l_child;

		for (int i = 1; i < level - 1; i++) {

			NODE<X>* new_level_it = new_cur_level_first;
			NODE<X>* level_it = curr_level_first;
			for (int j = 0; j < i + 1; j++) {

				if (j == 0) {

					new_level_it->l_child = new NODE<X>(level_it->l_child->value);
					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->next->l_child = new_level_it->r_child;
					new_level_it->l_child->next = new_level_it->r_child;
				}
				else if (j == i) {

					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->l_child->next = new_level_it->r_child;
					new_level_it->r_child->next = new_level_it->next->l_child;

				}
				else {

					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->l_child->next = new_level_it->r_child;
					new_level_it->next->l_child = new_level_it->r_child;
				}

				new_level_it = new_level_it->next;
				level_it = level_it->next;
			}

			new_cur_level_first = new_cur_level_first->l_child;
			curr_level_first = curr_level_first->l_child;
		}
	}


	cout << "Copy Assignment Triangle" << endl;

}

template <class X> Triangle<X>::Triangle(const Triangle<X>& T) { //copy constructor
	//Your code
	NODE<X>* h = T.head;
	int level;
	if (h == nullptr) level = 0;
	else level = 1;
	while (h->l_child != nullptr) {

		level++;
		h = h->l_child;
	}
	
	if (level == 0) {
		head = nullptr;
	}
	else if (level == 1) {
	
		head = new NODE<X>((T.head)->value);
		head->next = head;
	}
	else {
	
		head = new NODE<X>((T.head)->value);
		head->next = head;
		head->l_child = new NODE<X>(((T.head)->l_child)->value);
		head->r_child = new NODE<X>(((T.head)->r_child)->value);
		head->l_child->next = head->r_child;
		head->r_child->next = head->l_child;

		NODE<X>* curr_level_first = (T.head)->l_child;
		NODE<X>* new_cur_level_first = head->l_child;

		for (int i = 1; i < level - 1; i++) {
		
			NODE<X>* new_level_it = new_cur_level_first;
			NODE<X>* level_it = curr_level_first;
			for (int j = 0; j < i + 1; j++) {

				if (j == 0) {
				
					new_level_it->l_child = new NODE<X>(level_it->l_child->value);
					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->next->l_child = new_level_it->r_child;
					new_level_it->l_child->next = new_level_it->r_child;
				}
				else if (j == i) {
				
					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->l_child->next = new_level_it->r_child;
					new_level_it->r_child->next = new_level_it->next->l_child;

				}
				else {
				
					new_level_it->r_child = new NODE<X>(level_it->r_child->value);
					new_level_it->l_child->next = new_level_it->r_child;
					new_level_it->next->l_child = new_level_it->r_child;
				}

				new_level_it = new_level_it->next;
				level_it = level_it->next;
			}

			new_cur_level_first = new_cur_level_first->l_child;
			curr_level_first = curr_level_first->l_child;
		}
	}
		
	cout << "Copy Constructor Triangle" << endl;
}


template <class X> Triangle<X>::Triangle(const initializer_list<initializer_list<X>>& I) {
	//Your code
	int level = I.size();
	if (level == 0) {
		head = nullptr;
	}
	else if (level == 1) {
	
		X n = *((I.begin())->begin());
		head = new NODE<X>(n);
		head->next = head;
	}
	else {
		X n = *((I.begin())->begin());
		head = new NODE<X>(n);
		head->next = head;
		
		NODE<X>* curr_level_first = head;
		for (int i = 0; i < level - 1; i++) {
		
			NODE<X>* curr_node = curr_level_first;

			if (i == 0) {
			
				curr_node->l_child = new NODE<X>(*((I.begin() + 1)->begin() ));
				curr_node->r_child = new NODE<X>(*((I.begin() + 1)->begin() + 1));
				(curr_node->l_child)->next = curr_node->r_child;
				(curr_node->r_child)->next = (curr_node->next)->l_child;
			}
			else {

				for (int j = 0; j < (*(I.begin() + i)).size(); j++) {

					if (j == 0) {

						curr_node->l_child = new NODE<X>(*((I.begin() + i + 1)->begin() + j));
						curr_node->r_child = new NODE<X>(*((I.begin() + i + 1)->begin() + j + 1));
						(curr_node->next)->l_child = curr_node->r_child;
						(curr_node->l_child)->next = curr_node->r_child;


					}
					else if (j == (*(I.begin() + i)).size() - 1) {

						curr_node->r_child = new NODE<X>(*((I.begin() + i + 1)->begin() + j + 1));
						(curr_node->l_child)->next = curr_node->r_child;
						(curr_node->r_child)->next = (curr_node->next)->l_child;
					}
					else {

						curr_node->r_child = new NODE<X>(*((I.begin() + i + 1)->begin() + j + 1));
						(curr_node->next)->l_child = curr_node->r_child;
						(curr_node->l_child)->next = curr_node->r_child;
					}

					curr_node = curr_node->next;
				}
			}

			curr_level_first = curr_level_first->l_child;
		}

	}

	cout << "initializer_list Triangle" << endl;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t);


template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L);



template <class X> ostream& operator<<(ostream& str, const Triangle<X>& T);

int main() {


	Triangle<int> T1{ {1},  {2,3},  {4, 5, 6}, {7,8, 9, 10} };//initializer_list
	cout << T1 << endl;
	Triangle<int> T2{ T1 };
	cout << T2 << endl;

	Triangle<int> T3;
	T3 = T1;
	cout << T3 << endl;

	Triangle<int> T4;
	T4 = T1.ThreeTimes();
	cout << T4 << endl;
	
	Triangle<linked_list<ThreeD<int>>> T5{ {{{3,4,5},{7,1,4},{6,7,3}}}, {{ {5,4,8 },{4,2,16  }, {7, 8, 4} } ,{ { {8,2,4},{8,4,4}}} } };

	//////};
	cout << T5 << endl;

	Triangle<linked_list<ThreeD<int>>>  T6{ {{{3,5,4},{7,2,2},{6,7,3}}}, {{ {5,2,16 },{4,1,32  }, {7, 8, 4} } ,{ { {4,4,4},{4,8,4}}} } };

	cout << T6 << endl;

	if (T5 == T6) cout << "EQUAL" << endl;
	else cout << "NOT EQUQL" << endl;

	Triangle<linked_list<ThreeD<int>>>* p1 = new Triangle<linked_list<ThreeD<int>>>
	{ {{{3,4,5},{7,1,4},{6,7,3}}}, {{ {5,4,8 },{4,2,16  }, {7, 8, 4} } ,{ { {8,2,4},{8,4,4}}} } };
	cout << *p1 << endl;
	delete p1;
	return 0;
}

template <class T> ostream& operator<<(ostream& str, const ThreeD<T>& t) {
	//Your code

	str << "(" << t.ht << ", " << t.wid << ", " << t.dep << ")";
	return str;
}

template <class T> ostream& operator<<(ostream& str, const linked_list<T>& L) {
	//Your code

	str << "[ ";
	node<T>* it = L.head;
	
	while (it != nullptr) {
	
		str << it->value << " ";
		it = it->next;
	}
	str << " ]";
	return str;
}


template <class X> ostream& operator<<(ostream& str, const Triangle<X>& T) {
	//Your code
	NODE<X>* h = T.head;

	int level;
	if (h == nullptr) level = 0;
	else level = 1;
	while (h->l_child != nullptr) {
	
		level++;
		h = h->l_child;
	}
	NODE<X>* curr_level_first = T.head;
	for (int i = 0; i < level ; i++) {
	
		str << "{ ";
		for (int j = 0; j < i + 1; j++) {
		
			str << curr_level_first->value << " ";
			curr_level_first = curr_level_first->next;
		}
		str << "}" << endl;
		
		if (curr_level_first->l_child == nullptr) break;
		curr_level_first = curr_level_first->l_child;
	} 
	return str;
}


