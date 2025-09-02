#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Student
{
	string m_first = "First";
	string m_last  = "Last";
	int 	m_id   = 	0;
	float m_avg    = 0.0;

	public:
		Student(){}
		Student(string m_f, string m_l, int m_i, float m_a)
			:m_first(m_f),
			m_last(m_l),
			m_id(m_i),
			m_avg(m_a) {}
			

		int  getId() const{
			return m_id;
		}
		float getAvg() const{
			return m_avg;
		}
		string getFirst() const{
			return m_first;
		}
		string getLast() const{
			return m_last;
		}

		void print() const{
			cout << m_first << " " << m_last << " " << m_id << " " << m_avg << "\n";
		}

};


class Course{
	string m_name = "Course";
	vector<Student> m_students;

	public:
		Course(){}
		Course(const string& name)
		:m_name(name){}

		void addStudent(const Student& s){
			m_students.push_back(s);
		}

		const vector<Student>& getStudents() const{
			return m_students;
		}

		void loadFromFile(const string& filename){
			ifstream fin(filename);
			string first, last ;
			int id;
			float avg;
			while (fin >> first){
				fin  >> last ;
				fin >> id ;
				fin >> avg;
				cout << first << " " << last << "\n";
				addStudent(Student(first, last, id, avg));
			}

		}
		void print() const{

			for(const auto& s: m_students){
				s.print();
			}
		}
		

};
int main(){
	Course comp4("CSIS 3560");
	comp4.loadFromFile("students.txt");
	comp4.print();

	return 0;
	
}
