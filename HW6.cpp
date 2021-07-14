//HW6 by Yuhao Chen
//SU Net ID: ychen436 SUID: 603743399
//HW6.  Due: Wednesday (May 5) at 11:59pm

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <set>
#include <unordered_set>

using namespace std;

class myCompareClass {
	//For all comparions, compare the sums of all int objects in the structures.
	//For Hashing function use h(sums int in the sturcture), where hash<int> h;
public:
	//myCompareClass() {}
	bool operator()(int* p1, int* p2) const { return *p1 < *p2; }
	bool operator()(list<set<int*, myCompareClass>*>* p1, list<set<int*, myCompareClass>*>* p2) const{
		int sum1{ 0 }, sum2{ 0 };
		for (auto i : *p1) {
		
			for (auto j : *i) {
			
				sum1 += *j;
			}
		}

		for (auto i : *p2) {

			for (auto j : *i) {

				sum2 += *j;
			}
		}

		return sum1 < sum2;
	}
	bool operator() (const map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >& M1,
		const map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >& M2)  const {
		int sum1{ 0 }, sum2{ 0 };
		
		for (auto i : M1) {
		
			auto j = get<0>(i);
			auto k = get<1>(i);

			for (auto j1 : *j) {
			
				for (auto j2 : *j1) {
				
					sum1 += *j2;
				}
			}

			for (auto k1 : *k) {
			
				sum1 += *k1;
			}
		}

		for (auto i : M2) {

			auto j = get<0>(i);
			auto k = get<1>(i);

			for (auto j1 : *j) {

				for (auto j2 : *j1) {

					sum2 += *j2;
				}
			}

			for (auto k1 : *k) {

				sum2 += *k1;
			}
		}

		return sum1 < sum2;

	}
};

class myCompareClass1 {
	//Need a functor for ==
	//For Hashing function use h(sums int in the sturcture), where hash<int> h;
public:
	//myCompareClass1() {}
	bool operator() (const map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >& M1,
		const map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >& M2)  const {
		int sum1{ 0 }, sum2{ 0 };
		
		for (auto i : M1) {
		
			auto j = get<0>(i);
			auto k = get<1>(i);

			for (auto j1 : *j) {
			
				for (auto j2 : *j1) {
				
					sum1 += *j2;
				}
			}

			for (auto k1 : *k) {
			
				sum1 += *k1;
			}
		}

		for (auto i : M2) {

			auto j = get<0>(i);
			auto k = get<1>(i);

			for (auto j1 : *j) {

				for (auto j2 : *j1) {

					sum2 += *j2;
				}
			}

			for (auto k1 : *k) {

				sum2 += *k1;
			}
		}

		return sum1 == sum2;

	}

	size_t operator() (const map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >& M)  const {
	
		hash<int> h;
		int sum = 0;
		for (auto i : M) {

			auto j = get<0>(i);
			auto k = get<1>(i);

			for (auto j1 : *j) {

				for (auto j2 : *j1) {

					sum += *j2;
				}
			}

			for (auto k1 : *k) {

				sum += *k1;
			}
		}

		return h(sum);
	}

};
//You need to implement overloaded operator<< .

ostream& operator<<(ostream& str, set<map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >, myCompareClass>& S1) {
	str << "<" << endl;
	for (auto i : S1) {
	
		str << "{ ";
		for (auto i1 : i) {
		
			str << " [ ";
			for (auto j : *get<0>(i1)) {
			
				str << "< ";
				for (auto j1 : *j) {
				
					str << *j1 << " ";
				}
				str << "> ";
			}
			str << "] ";

			str << "( ";
			for (auto k : *get<1>(i1)) {
			
				str << *k << " ";
			}
			str << ") ";

		}
		str << " }" << endl;
	}
	str << ">" << endl;

	return str;
}

ostream& operator<<(ostream& str, unordered_set< map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >, myCompareClass1, myCompareClass1> H1) {
	str << "<" << endl;
	for (auto i : H1) {

		str << "{ ";
		for (auto i1 : i) {

			str << " [ ";
			for (auto j : *get<0>(i1)) {

				str << "< ";
				for (auto j1 : *j) {

					str << *j1 << " ";
				}
				str << "> ";
			}
			str << "] ";

			str << "( ";
			for (auto k : *get<1>(i1)) {

				str << *k << " ";
			}
			str << ") ";

		}
		str << " }" << endl;
	}
	str << ">" << endl;

	return str;
}

int main() {
	//Create your initial values with at least 3 elements in every STL container. 
	set<map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >, myCompareClass> S1
	{
		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {3}, new int {7}, new int {5} },
				new set<int*, myCompareClass> { new int {2}, new int {5}, new int {8} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {6} }  },
				new vector<int*> {new int {7}, new int {11}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {17} },
				new set<int*, myCompareClass> { new int {3}, new int {8}, new int {5} },
				new set<int*, myCompareClass> { new int {1}, new int {3}, new int {6} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {4} },
				new set<int*, myCompareClass> { new int {18}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {13}, new int {6}, new int {2} }  },
				new vector<int*> {new int {5}, new int {11}, new int {13}}  }
		},

		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {3}, new int {7}, new int {5} },
				new set<int*, myCompareClass> { new int {8}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {6} }  },
				new vector<int*> {new int {7}, new int {19}, new int {13}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {17} },
				new set<int*, myCompareClass> { new int {8}, new int {3}, new int {5} },
				new set<int*, myCompareClass> { new int {1}, new int {3}, new int {6} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {1}, new int {7} },
				new set<int*, myCompareClass> { new int {1}, new int {15}, new int {2} },
				new set<int*, myCompareClass> { new int {6}, new int {16}, new int {20} }  },
				new vector<int*> {new int {5}, new int {19}, new int {4}}  }
		},

		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {6}, new int {5} },
				new set<int*, myCompareClass> { new int {3}, new int {5}, new int {4} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {9} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {13}, new int {7} },
				new set<int*, myCompareClass> { new int {1}, new int {11}, new int {15} },
				new set<int*, myCompareClass> { new int {8}, new int {3}, new int {6} }  },
				new vector<int*> {new int {5}, new int {12}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {3}, new int {4} },
				new set<int*, myCompareClass> { new int {12}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {13}, new int {16}, new int {2} }  },
				new vector<int*> {new int {5}, new int {17}, new int {2}}  }
		}
	};
	
	std::cout << S1 << endl;

	unordered_set< map < list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass >, myCompareClass1, myCompareClass1> H1
	{
		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {3}, new int {7}, new int {5} },
				new set<int*, myCompareClass> { new int {2}, new int {5}, new int {8} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {6} }  },
				new vector<int*> {new int {7}, new int {11}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {17} },
				new set<int*, myCompareClass> { new int {3}, new int {8}, new int {5} },
				new set<int*, myCompareClass> { new int {1}, new int {3}, new int {6} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {4} },
				new set<int*, myCompareClass> { new int {18}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {13}, new int {6}, new int {2} }  },
				new vector<int*> {new int {5}, new int {11}, new int {13}}  }
		},

		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {3}, new int {7}, new int {5} },
				new set<int*, myCompareClass> { new int {8}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {6} }  },
				new vector<int*> {new int {7}, new int {19}, new int {13}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {3}, new int {17} },
				new set<int*, myCompareClass> { new int {8}, new int {3}, new int {5} },
				new set<int*, myCompareClass> { new int {1}, new int {3}, new int {6} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {1}, new int {7} },
				new set<int*, myCompareClass> { new int {1}, new int {15}, new int {2} },
				new set<int*, myCompareClass> { new int {6}, new int {16}, new int {20} }  },
				new vector<int*> {new int {5}, new int {19}, new int {4}}  }
		},

		map< list<set<int*, myCompareClass>*>*, vector<int*>*, myCompareClass> {
			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {6}, new int {5} },
				new set<int*, myCompareClass> { new int {3}, new int {5}, new int {4} },
				new set<int*, myCompareClass> { new int {3}, new int {11}, new int {9} }  },
				new vector<int*> {new int {4}, new int {14}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {5}, new int {13}, new int {7} },
				new set<int*, myCompareClass> { new int {1}, new int {11}, new int {15} },
				new set<int*, myCompareClass> { new int {8}, new int {3}, new int {6} }  },
				new vector<int*> {new int {5}, new int {12}, new int {3}}  },

			{ new list<set<int*, myCompareClass>*>
				{new set<int*, myCompareClass> { new int {13}, new int {3}, new int {4} },
				new set<int*, myCompareClass> { new int {12}, new int {5}, new int {2} },
				new set<int*, myCompareClass> { new int {13}, new int {16}, new int {2} }  },
				new vector<int*> {new int {5}, new int {17}, new int {2}}  }
		}
	};
	
	//You can re-use the above.

	cout << H1 << endl;

	return 0;
}