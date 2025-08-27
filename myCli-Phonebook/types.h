#ifndef TYPE_H
#define TYPE_H
#include <iostream>
#include <vector>
using namespace std;




class Contact{
	private:
		int id;
		string fname;
		string lname;
		string phoneNumber;
		int incomingCalls;
		int outgoingCalls;

	public:
		Contact();
		Contact(int iD, string fn, string ln, string pNum, int iC, int oC); 

		// Getters
		int getId() const;
		string getFname() const;
		string getLname() const;
		string getPnum() const;
		int getIc() const;
		int getOc() const;


		// Setters
		void setId(int iD);
		void setFname(const string& fn);
		void setLname(const string& ln);
		void setPnum(const string& pNum);
		void setIc(int ic);
		void setOc(int oc);


};

void addContact( vector<Contact> contactList ) ;


#endif
