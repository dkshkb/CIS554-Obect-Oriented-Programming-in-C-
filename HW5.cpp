//HW5 by Yuhao Chen

//HW5 Due: April 23 (Friday) at 11:59PM
#include <iostream>
#include <memory>

using namespace std;

class node {
public:
	shared_ptr<node> east;
	weak_ptr<node> south;
	int value;
	node() {}
	node(int i) { value = i; }
};

class ring {
public:
	//Implement all functions described below


	shared_ptr<node> head;
	int num_rows;
	int num_cols;
	ring() {}

	//Implement all functions described below
	ring(int i, int j, int k);//constructor
	//i rows and j cols, values randomly distributed in 0 ... k-1
	~ring();//destructor; do as little work as possible
	ring(const ring& r); //copy constructor
	ring(ring&& r); //move constructo
	void operator=(ring&& r);//move assignment
	void operator=(const ring& r); //copy assignment
	ring(const initializer_list<initializer_list<int>>& V);//nested initializer_list
	void DelCol(int i);//delete col i of *this; row numbers start from 0
	void DelRow(int i);//delete row i of *this; col numbers start from 0
	ring Threetimes();
	//return a ring with the same dimenstion as *this, and the value of every node is three times of that of *this.

	friend ostream& operator<<(ostream& str, const ring& R);

};

ring::ring(int i, int j, int k) {
	
	//connect the north node
	num_rows = i;
	num_cols = j;
	head = nullptr;
	for (int id = 0; id < i * j; id++) {
		shared_ptr<node> p1 = make_shared<node>(rand() % k);
		p1->east = head;
		head = p1;
		p1.reset();
	}

	//find the last node, set the east of the last node
	shared_ptr<node> last = head;
	while (last->east != nullptr) {
	
		last = last->east;
	}
	last->east = head;
	last.reset();

	//connect the south node
	shared_ptr<node> p = head;
	for (int row = 0; row < i; row++) {
	
		for (int col = 0; col < j; col++) {
		
			p->south = p;
			if (row != i - 1) {
			
				for (int count = 0; count < j; count++) {
				
					p->south = ((p->south).lock())->east;
				}
			}
			else {
			
				if (col != j - 1) {
					
					for (int count = 0; count <= j; count++) {

						p->south = ((p->south).lock())->east;
					}

				}
				else {
				
					p->south = ((p->south).lock())->east;
				}
			}

			p = p->east;
		}
	}
	p.reset();

}

ostream& operator<<(ostream& str, const ring& R) {
	
	int i = 0;
	shared_ptr<node> p = R.head;
	if (p) {
		str << endl;
		if (p->east) {
			while (true) {
				//p points to first node at each row
				shared_ptr<node> it = p; // "it" is used to go through each row 
				while (true) {

					str << it->value << " ";

					if (it->east == it->south.lock()) { //reach the last node {}
					
						it.reset();
						str << endl;
						return str;
					}
					if (it->east == p->south.lock()) { //reach the end of row

						break;
					}

					it = it->east;
				}
				p = p->south.lock();

				str << endl;
			}
		} 
		// only one node
		else {
			str << endl << R.head->value << endl;
		}
	}
	p.reset();
	return str;
}

ring::~ring() {
	
	if (head) {

		if (head->east) {
			head->east.reset();
		}
		head.reset();
	}

	cout << "Destructor" << endl;
}

void ring::DelCol(int i) {

	if (i == 0) { // if I need to delete the first col
	
		// find the last node at the first row
		shared_ptr<node> first = head;
		shared_ptr<node> last = head;
		shared_ptr<node> curr_first = head; // to avoid the first node to be deleted auto too early
		head = head->east;
		while (true) {
		
			if (last->east == first->south.lock()) break;
			last = last->east;
		}

		//delete the first col
		while (true) {
			

			if (last->east == last->south.lock()) { //reach the last node at the last row

				last->east = last->east->east;
				last->south = last->east;

				break; 
			}

			last->east = last->east->east;
			last = last->south.lock();
		}

		//reset three pointers
		first.reset();
		last.reset();
		curr_first.reset();
	}
	else {

		// find the col before the col to be deleted
		shared_ptr<node> prev = head; 
		for (int count = 0; count < i - 1; count++) {
		
			prev = prev->east;
		}

		//delete the target col using the previous col
		shared_ptr<node> it = prev; // "it" is used to go through the previous col
		shared_ptr<node> curr_col_first = prev->east; // to keep avoid the first node of this col to be deleted in the beginning

		while (true) {
		

			if (curr_col_first == (it->south).lock()) { //reach the last row
			
				if (it->east->east == it->east->south.lock()) { // if we delete the last col
				
					it->east = (it->east)->east;
					it->south = it->east;
					break;
				}
				else { // if we don't delete the last col 
					it->east = (it->east)->east;
					it->south = (it->south).lock()->east;
					break;
				}
			} 

			it->east = (it->east)->east;
			it = (it->south).lock();
		}

		//reset three pointers
		prev.reset();
		it.reset();
		curr_col_first.reset();

	}

	num_cols--;
}

void ring::DelRow(int i) {

	if (i == 0) { // if we delete the first row
	
		// find the last node (right-bottom corner)
		shared_ptr<node> last_row = head; // last_row is a pointer to the first note at last row
		while (true) {
		
			if (last_row->south.lock() == head->east) break;
			last_row = last_row->east;
		}

		//modify the south pointer for the last row
		while (true) {
		
			if (last_row->south.lock() == last_row->east) { // hit the last node
			
				last_row->south = head->south.lock();
				last_row->east = head->south.lock(); // for the last node, I also have to change the east pointer 
				break;
			}

			// for the cases not the last node
			last_row->south = last_row->south.lock()->south.lock();
			last_row = last_row->east; // move to the next(east) node
		}

		head = head->south.lock(); // the first row will be deleted auto
		last_row.reset();


	}
	else { // if we don't delete the first row
	
		shared_ptr<node> prev_row = head; // the pointer to the row previous to the one to be deleted
		for (int count = 0; count < i - 1; count++) {
		
			prev_row = prev_row->south.lock();
		}

		shared_ptr<node> it = prev_row; // "it" is used to go through the whole row
		shared_ptr<node> curr_row = prev_row->south.lock();
		while (true) {
		
			if (it->east == curr_row) { // If I reach the end of the previous row
			
				if (it->south.lock()->east == it->south.lock()->south.lock()) { // if i'm deleteing the last row
				
					it->south = it->south.lock()->south.lock();
					it->east = it->south.lock();
					break;
				}
				else { // reach the end of the previous row, but not deleting the last row
				
					it->south = it->south.lock()->south.lock();
					it->east = curr_row->south.lock();
					break;
				}
			}
			it->south = it->south.lock()->south.lock();
			it = it->east;
		}

		prev_row.reset();
		it.reset();
	}

	num_rows--;
}

ring::ring(const initializer_list<initializer_list<int>>& V) {

	num_rows = V.size();

	if (num_rows == 0) {
	
		head = nullptr;
	}
	else {
		num_cols = V.begin()->size();

		if (num_cols == 0) head = nullptr;
		else { // the main part starts here

			auto it_row = V.end() - 1;
			while (true) {
			
				auto it_col = it_row->end() - 1;
				while (true) {
				
					shared_ptr<node> p = make_shared<node>(*(it_col));
					p->east = head;
					head = p;
					p.reset();
					if (it_col == it_row->begin()) {
					
						break;
					}
					it_col--;
				}

				if (it_row == V.begin()) {
				
					break;
				}
				it_row--;
			}

			//find the last node, set the east of the last node
			shared_ptr<node> last = head;
			while (last->east != nullptr) {

				last = last->east;
			}
			last->east = head;
			last.reset();

			//connect the south node
			shared_ptr<node> p = head;
			for (int row = 0; row < num_rows; row++) {

				for (int col = 0; col < num_cols; col++) {

					p->south = p;
					if (row != num_rows - 1) {

						for (int count = 0; count < num_cols; count++) {

							p->south = ((p->south).lock())->east;
						}
					}
					else {

						if (col != num_cols - 1) {

							for (int count = 0; count <= num_cols; count++) {

								p->south = ((p->south).lock())->east;
							}

						}
						else {

							p->south = ((p->south).lock())->east;
						}
					}

					p = p->east;
				}
			}
			p.reset();
		}

	}
}

ring::ring(const ring& r) { //copy constructor

	cout << "Copy Constructor" << endl;

	if (r.head == nullptr) head = nullptr;
	shared_ptr<node> it = r.head;
	while (true) {
	
		shared_ptr<node> p = make_shared<node>(it->value);
		p->east = head;
		head = p;
		p.reset();

		if (it->east == it->south.lock()) {
		
			break;
		}
		it = it->east;
	}

	//reverse
	it = head;
	head = nullptr;
	while (true) {
	
		shared_ptr<node> p = make_shared<node>(it->value);
		p->east = head;
		head = p;
		p.reset();

		if (it->east == it->south.lock()) {

			break;
		}
		it = it->east;
	}
	it.reset();

	// connect the last node's east to head
	shared_ptr<node> last = head;
	while (last->east != nullptr) {

		last = last->east;
	}
	last->east = head;
	last.reset();

	//find num_row & num_col
	num_rows = r.num_rows;
	num_cols = r.num_cols;

	//connect the south node
	shared_ptr<node> p = head;
	for (int row = 0; row < num_rows; row++) {

		for (int col = 0; col < num_cols; col++) {

			p->south = p;
			if (row != num_rows - 1) {

				for (int count = 0; count < num_cols; count++) {

					p->south = ((p->south).lock())->east;
				}
			}
			else {

				if (col != num_cols - 1) {

					for (int count = 0; count <= num_cols; count++) {

						p->south = ((p->south).lock())->east;
					}

				}
				else {

					p->south = ((p->south).lock())->east;
				}
			}

			p = p->east;
		}
	}
	p.reset();

} 

ring::ring(ring&& r) { //move constructor

	cout << "Move Constructor" << endl;
	head = r.head;
	r.head.reset();
} 

void ring::operator=(ring&& r) { //move assignment

	cout << "Move Assignment" << endl;
	
	// Do the deletion
	if (head) {

		if (head->east) {
			head->east.reset();
		}
		head.reset();
	}

	//Do the assignment
	head = r.head;
	r.head.reset();
}

void ring::operator=(const ring& r) { //copy assignment

	cout << "Copy Assignment" << endl;

	// Do the deletion
	if (head) {

		if (head->east) {
			head->east.reset();
		}
		head.reset();
	}

	// Do the assignment
	if (r.head == nullptr) head = nullptr;
	shared_ptr<node> it = r.head;
	while (true) {

		shared_ptr<node> p = make_shared<node>(it->value);
		p->east = head;
		head = p;
		p.reset();

		if (it->east == it->south.lock()) {

			break;
		}
		it = it->east;
	}

	//reverse
	it = head;
	head = nullptr;
	while (true) {

		shared_ptr<node> p = make_shared<node>(it->value);
		p->east = head;
		head = p;
		p.reset();

		if (it->east == it->south.lock()) {

			break;
		}
		it = it->east;
	}
	it.reset();

	// connect the last node's east to head
	shared_ptr<node> last = head;
	while (last->east != nullptr) {

		last = last->east;
	}
	last->east = head;
	last.reset();

	//find num_row & num_col
	num_rows = r.num_rows;
	num_cols = r.num_cols;

	//connect the south node
	shared_ptr<node> p = head;
	for (int row = 0; row < num_rows; row++) {

		for (int col = 0; col < num_cols; col++) {

			p->south = p;
			if (row != num_rows - 1) {

				for (int count = 0; count < num_cols; count++) {

					p->south = ((p->south).lock())->east;
				}
			}
			else {

				if (col != num_cols - 1) {

					for (int count = 0; count <= num_cols; count++) {

						p->south = ((p->south).lock())->east;
					}

				}
				else {

					p->south = ((p->south).lock())->east;
				}
			}

			p = p->east;
		}
	}
	p.reset();
} 

ring ring::Threetimes() {

	cout << "ThreeTimes" << endl;

	shared_ptr<node> rt;
	if (head == nullptr) rt = nullptr;
	shared_ptr<node> it = head;
	while (true) {

		shared_ptr<node> p = make_shared<node>(it->value * 3);
		p->east = rt;
		rt = p;
		p.reset();

		if (it->east == it->south.lock()) {

			break;
		}
		it = it->east;
	}

	//reverse
	it = rt;
	rt = nullptr;
	while (true) {

		shared_ptr<node> p = make_shared<node>(it->value);
		p->east = rt;
		rt = p;
		p.reset();

		if (it->east == it->south.lock()) {

			break;
		}
		it = it->east;
	}
	it.reset();

	// connect the last node's east to head
	shared_ptr<node> last = rt;
	while (last->east != nullptr) {

		last = last->east;
	}
	last->east = rt;
	last.reset();

	//connect the south node
	shared_ptr<node> p = rt;
	for (int row = 0; row < num_rows; row++) {

		for (int col = 0; col < num_cols; col++) {

			p->south = p;
			if (row != num_rows - 1) {

				for (int count = 0; count < num_cols; count++) {

					p->south = ((p->south).lock())->east;
				}
			}
			else {

				if (col != num_cols - 1) {

					for (int count = 0; count <= num_cols; count++) {

						p->south = ((p->south).lock())->east;
					}

				}
				else {

					p->south = ((p->south).lock())->east;
				}
			}

			p = p->east;
		}
	}
	p.reset();

	ring myRing;
	myRing.head = rt;
	myRing.num_cols = num_cols;
	myRing.num_rows = num_rows;
	return myRing;
}

int main() {

	ring R1(4, 6, 20);
	cout << R1 << endl;
	R1.DelCol(3);
	cout << R1 << endl;
	R1.DelCol(4);
	cout << R1 << endl;
	R1.DelCol(0);
	cout << R1 << endl;

	ring R2(5, 7, 20);
	cout << R2 << endl;
	R2.DelRow(3);
	cout << R2 << endl;
	R2.DelRow(3);
	cout << R2 << endl;
	R2.DelRow(0);
	cout << R2 << endl;

	shared_ptr<ring> p1 = make_shared<ring>(3, 5, 10);
	cout << *p1 << endl;
	p1.reset();

	ring R3 = { {10,20,30,40,50} , {100, 200, 300, 400, 500}, {1000, 2000, 3000, 4000, 5000} };//
	cout << R3 << endl;
	ring R4(R3);
	cout << R4 << endl;
	ring R5;
	R5 = R3;
	cout << R5 << endl;
	ring R6;
	R6 = R5.Threetimes();
	cout << R6 << endl;

	return 0;
}
