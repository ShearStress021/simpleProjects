#include <iostream>
#include "types.h"
using namespace std;


Contact::Contact()
		: id(23), fname("Jay"), lname("Grace"), phoneNumber("465-473-8873"), incomingCalls(4), outgoingCalls(23) {}

Contact::Contact(int iD, string fn, string ln, string pNum, int iC, int oC)
		:id(iD),
		fname(fn),
		lname(ln),
		phoneNumber(pNum),
		incomingCalls(iC),
		outgoingCalls(oC) {}

// Getter
int Contact::getId() const {return id;}
string Contact::getFname() const {return fname;}
string Contact::getLname() const {return lname;}
string Contact::getPnum() const {return phoneNumber;}
int Contact::getIc() const {return incomingCalls;}
int Contact::getOc() const {return outgoingCalls;}


int main(){
	cout << "\n\t--------------------------------- " << "\n";
	cout << "\t Phone Book Register " << "\n";
	cout << "\t--------------------------------- " << "\n";

	cout << "\t[1] -> List All Contacts" << "\n";
	cout << "\t[2] -> Add New Contact" << "\n";
	cout << "\t[3] -> Edit Contact" << "\n";
	cout << "\t[4] -> Remove Contact" << "\n";
	cout << "\t[5] -> Search Contact" << "\n";
	cout << "\t[6] -> Call Contact " << "\n";
	cout << "\t[0] -> Quit" << "\n";
	cout << "\t--------------------------------- " << "\n";
	cout << "\tEnter your choice : " << "\n";

	
	return 0;
}


void addContact(vector<Contact> contactList){

}
