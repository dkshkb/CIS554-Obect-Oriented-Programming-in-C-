//HW3 by Yuhao Chen
//SU Net ID: ychen436 SUID:603743399
//Due: 11:59PM, March 20 (Saturday)

#include <iostream>
#include <list>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <iomanip>
using namespace std;

class course {
public:
	string name;
	int section;
	int credits;
	string grade;
	course() {}
	course(string n, int s, int c, string g) { name = n; section = s; credits = c; grade = g; }

	//You might need to implement some overloaded operators here.
	bool operator==(const course& C) const { return name == C.name; }
	bool operator<(const course& c) const { return name < c.name; }
	float num_grade();
};

float course::num_grade() {
	map<string, float> M{
		{"A", 4.0},{"A-", 3.6666}, {"B+", 3.3333}, {"B", 3.0},
		{"B-", 2.6666}, {"C+", 2.3333}, {"C", 2.0}, {"C-", 1.6666},
		{"D", 1.0}, {"D-", 0.666}, {"F", 0}
	};
	return M[grade];
}

ostream& operator<<(ostream& str, const course& c);
//Implement the following functions.
//When adding a student, if the student is already in DB, then ignore the operation.
//When adding a course, if the course is already in DB, then ignore the operation.
//When dropping a course, if the course does not exist, then ignore the operation.
//When removing a student, if the student does not exist, then ignore the operation.
//All courses in a semester need to be sorted.
//When dropping or adding a course, overall GPA, semester GPA, overall credits and semester credits all need to be updated.

//Semeser numbers:  Spring 2019: 20191; Fall 2019: 20192, etc. 

void add_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id);
void remove_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id);
void add_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id, course c); //20171 Spring semester of 2017; 20172: Fall semester of 2017
																//All courses in the list should be sorted according to name (increasing order)
void drop_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id, course c);
void print_student_semester_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id);
void print_student_all_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id);
ostream& operator<<(ostream& str, const list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& db);

//Implement additional functions such that you can do
//cout << DB << endl;
ostream& operator<<(ostream& str, const list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& db) {

	for (auto i : db) {

		str << "Student ID: " << i->first << endl;
		str << fixed << setprecision(2) << "Overall GPA: " << get<1>(i->second) << endl << "Overall Credits: " << get<0>(i->second) << endl;

		for (auto j : *get<2>(i->second)) {

			str << "Semester : " << j.first << endl;
			str << fixed << setprecision(2) << "GPA : " << get<1>(j.second) << endl;
			str << "Credits : " << get<0>(j.second) << endl;

			for (auto k : *get<2>(j.second)) {

				str << *k << " ";

			}
			cout << endl;
		}
	}
	cout << endl;

	return str;
}

//You might need to implement some overloaded operators in the course class.
ostream& operator<<(ostream& str, const course& c) {

	str << "(" << c.name << " " << c.section << " " << c.credits << " " << c.grade << ")";
	return str;
}

int main() {

	list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>  DB;



	add_student(DB, 11111);
	course C1("CIS554", 1, 3, "A-"), C2("CSE674", 1, 3, "B+"), C3("MAT296", 8, 4, "A"), C4("WRT205", 5, 3, "A");

	add_course(DB, 20171, 11111, C1);
	add_course(DB, 20171, 11111, C4);
	add_course(DB, 20171, 11111, C3);
	add_course(DB, 20171, 11111, C2);
	print_student_semester_courses(DB, 20171, 11111);

	drop_course(DB, 20171, 11111, C1);
	print_student_semester_courses(DB, 20171, 11111); //sorted according to course name

	course C5("CIS351", 2, 3, "A-"), C6("PSY205", 5, 3, "B+"), C7("MAT331", 2, 3, "A"), C8("ECN203", 4, 3, "A");
	add_course(DB, 20172, 11111, C5);
	add_course(DB, 20172, 11111, C6);
	add_course(DB, 20172, 11111, C7);
	add_course(DB, 20172, 11111, C8);
	add_course(DB, 20172, 11111, C3);
	print_student_all_courses(DB, 11111);//ID GPA

	add_student(DB, 11112);
	add_course(DB, 20171, 11112, C2);
	add_course(DB, 20171, 11112, C5);
	add_course(DB, 20171, 11112, C7);
	add_course(DB, 20171, 11112, C4);
	print_student_semester_courses(DB, 20171, 11112);

	add_course(DB, 20172, 11112, C8);
	add_course(DB, 20172, 11112, C3);
	add_course(DB, 20172, 11112, C5);
	add_course(DB, 20172, 11112, C1);
	print_student_semester_courses(DB, 20172, 11112);

	print_student_all_courses(DB, 11112);

	cout << DB << endl;
	remove_student(DB, 11111);
	cout << DB << endl;
	getchar();
	getchar();
	return 0;
}

void add_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id) {
	//Your code
	//Check if a studnet is already in the system
	auto it1{ DB.begin() };;
	bool found{ false };
	while (it1 != DB.end()) {
		if ((*it1)->first == id) {
			found = true;
		}
		it1++;
	}
	if (found) return;

	auto p = new pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >
	{ id, { 0,0.00, new map<int, tuple<int, float, vector<course* >*> > } };

	DB.push_back(p);

}

void remove_student(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id) {
	//Your code
	auto it1{ DB.begin() }, it2{ DB.begin() };
	bool found{ false };
	while (it1 != DB.end()) {
		if ((*it1)->first == id) {
			found = true;
			it2 = it1;
		}
		it1++;
	}
	if (!found) return;

	auto it3 = (*get<2>((*it2)->second)).begin();
	while (it3 != (*get<2>((*it2)->second)).end()) {

		auto it4 = (*get<2>(it3->second)).begin();
		while (it4 != (*get<2>(it3->second)).end()) {

			delete (*it4);
			it4 = (*get<2>(it3->second)).erase(it4);
		}
		it3 = (*get<2>((*it2)->second)).erase(it3);
	}

	DB.erase(it2);
}


void add_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id, course c) {

	//Your code

	//Find if this student is in the database
	auto it1 = DB.begin(), it2 = DB.begin();
	bool found{ false };
	while (it1 != DB.end()) {

		if ((*it1)->first == id) {
			found = true;
			it2 = it1;
		}
		it1++;
	}
	if (found == false) return;

	//Find if the course exists in the database
	bool find_course = false;
	auto it_map = (*get<2>((*it2)->second)).begin();
	//check if a course is already in the database
	while (it_map != (*get<2>((*it2)->second)).end()) {

		for (auto i : *get<2>(it_map->second)) {

			if (*i == c) find_course = true;
		}
		it_map++;
	}

	if (find_course) return;

	//add a new semester to the map if I can't find the semester in the database
	bool find_semester = false;
	for (auto i : *get<2>((*it2)->second)) {
		if (i.first == semester) find_semester = true;
	}
	// Add a new semester if not found
	if (!find_semester) {
		(*get<2>((*it2)->second)).insert({ semester, {0, 0, new vector<course*>} });
	}

	it_map = (*get<2>((*it2)->second)).begin();
	while (it_map != (*get<2>((*it2)->second)).end()) {

		if ((*it_map).first == semester) {

			if (find_course) {
				return;
			}

			if (get<2>((*it_map).second)->empty()) {
				get<2>((*it_map).second)->push_back(new course{ c });
				get<0>((*it_map).second) = c.credits;
				get<1>((*it_map).second) = c.num_grade();
			}
			else {
				get<2>((*it_map).second)->push_back(new course{ c });
				get<1>((*it_map).second) =
					((get<1>((*it_map).second) * get<0>((*it_map).second)) + (c.credits * c.num_grade()))
					/ (get<0>((*it_map).second) + c.credits);
				get<0>((*it_map).second) += c.credits;
				// Sort the vector of pointers to course
				auto v = *(get<2>((*it_map).second));
				get<2>((*it_map).second) = new vector<course*>;
				while (v.size() != 0) {
					auto it_v = v.begin();
					auto it_min = v.begin();
					// Find current smallest course pointer's iterator
					while (it_v != v.end()) {
						if (*(*(it_v)) < *(*(it_min))) {
							it_min = it_v;
						}
						it_v++;
					}
					get<2>((*it_map).second)->push_back(new course((*it_min)->name, (*it_min)->section,
						(*it_min)->credits, (*it_min)->grade));
					//delete that smallest course pointer from vector
					v.erase(it_min);
				}
			}
			break; //If we find the corresponding semester for the course to be added, then just break
		}
		it_map++;

	}

	if (!find_course) {
		get<1>((*it2)->second) =
			((get<1>((*it2)->second) * get<0>((*it2)->second)) + (c.credits * c.num_grade()))
			/ (get<0>((*it2)->second) + c.credits);
		get<0>((*it2)->second) += c.credits;
	}

}

void drop_course(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id, course c) {
	//Your code
	//Find if the student id is in the database
	auto it_db = DB.begin();
	auto it1 = DB.begin();
	bool found_id = false;
	while (it_db != DB.end()) {

		if (id == (*it_db)->first) {

			found_id = true;
			it1 = it_db;
		}
		it_db++;
	}

	if (!found_id) return;

	//Find if the semester is in the database
	auto it_semester_map = (*get<2>((*it1)->second)).begin();
	auto it2 = (*get<2>((*it1)->second)).begin();
	bool found_semester = false;
	while (it_semester_map != (*get<2>((*it1)->second)).end()) {

		if (semester == it_semester_map->first) {

			found_semester = true;
			it2 = it_semester_map;
		}
		it_semester_map++;
	}

	if (!found_semester) return;

	//Find if the course is in the database
	auto it_course_v = (*get<2>(it2->second)).begin();
	auto it3 = (*get<2>(it2->second)).begin();
	bool found_course = false;
	while (it_course_v != (*get<2>(it2->second)).end()) {

		if (*(*(it_course_v)) == c) {

			found_course = true;
			it3 = it_course_v;
		}
		it_course_v++;
	}

	if (!found_course) return;

	//delete the course
	delete (*it3);
	(*get<2>(it2->second)).erase(it3);

	//update semester credits and GPA

	//if this course is the only course for the semester
	if (get<0>(it2->second) == c.credits) {

		get<0>(it2->second) = 0;
		get<1>(it2->second) = 0.00;
	}
	else { // It the course is not the only one in the semester

		get<1>(it2->second) = (get<0>(it2->second) * get<1>(it2->second) - c.credits * c.num_grade()) /
			(get<0>(it2->second) - c.credits);
		get<0>(it2->second) = get<0>(it2->second) - c.credits;
	}


	//update overall credits and GPA

	//if this couse is the only course for the student
	if (get<0>((*it1)->second) == c.credits) {

		get<0>((*it1)->second) = 0;
		get<1>((*it1)->second) = 0.00;
	}
	else { // if this course is not the only course for the student

		get<1>((*it1)->second) = (get<0>((*it1)->second) * get<1>((*it1)->second) - c.credits * c.num_grade()) /
			(get<0>((*it1)->second) - c.credits);
		get<0>((*it1)->second) = get<0>((*it1)->second) - c.credits;
	}

}

void print_student_semester_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int semester, int id) {
	//Your code
	for (auto i : DB) {

		if (i->first == id) {

			for (auto j : *get<2>(i->second)) {

				if (j.first == semester) {

					cout << "Student ID: " << id << endl;
					cout << "Semester: " << semester << endl;
					cout << fixed << setprecision(2) << "GPA : " << get<1>(j.second) << endl;
					cout << "Credits : " << get<0>(j.second) << endl;
					for (auto k : *get<2>(j.second)) {

						cout << *k << " ";
					}
					cout << endl;
				}
			}
		}
	}
	cout << endl;
}
void print_student_all_courses(list<pair<int, tuple<int, float, map<int, tuple<int, float, vector<course* >*> >*> >*>& DB, int id) {
	//Your code
	for (auto i : DB) {

		if (i->first == id) {
			cout << "Student ID: " << i->first << endl;
			cout << fixed << setprecision(2) << "Overall GPA : " << get<1>(i->second) << endl << "Overall Credits : " << get<0>(i->second) << endl;

			for (auto j : *get<2>(i->second)) {

				cout << "semester: " << j.first << endl;
				cout << fixed << setprecision(2) << "GPA : " << get<1>(j.second) << endl;
				cout << "Credits : " << get<0>(j.second) << endl;

				for (auto k : *get<2>(j.second)) {

					cout << *k << " ";

				}
				cout << endl;
			}
		}
	}
	cout << endl << endl;
}



