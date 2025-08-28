#include <iostream>
#include <thread>
#include <chrono>
#include "types.h"
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;


#define TEXTFILE "contacts.txt" 

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


ContactList::ContactList(){}
ContactList::ContactList(vector<Contact> cl)

			:contactList(cl){}

const vector<Contact>& ContactList::getContactList() const { return contactList; }



int main(){
	int num;
	ContactList contactList;
	bool quit = false;

	while(!quit){

		clearScreen();

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
		cout << "\tEnter your choice : " ;

		cin >> num ;
		
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
		

		
		switch(num){
			case 1:
				cout << "\n\t------------------------" << "\n";
				cout << "\tContact List"<< "\n";
				cout << "\t------------------------" << "\n";
				listContacts(contactList, TEXTFILE);
				break;
			case 2:
				cout << "\n\t------------------------" << "\n";
				cout << "\tAdd Contact"<< "\n";
				cout << "\t------------------------" << "\n";
				addContact(contactList, TEXTFILE);
				break;
			case 3:
				cout << "\n\t------------------------" << "\n";
				cout << "\tEdit Contact"<< "\n";
				cout << "\t------------------------" << "\n";
			case 4:
				cout << "\n\t------------------------" << "\n";
				cout << "\tRemove Contact"<< "\n";
				cout << "\t------------------------" << "\n";
			case 5:
				cout << "\n\t------------------------" << "\n";
				cout << "\tSearch Contact"<< "\n";
				cout << "\t------------------------" << "\n";
				break;
			case 6:
				cout << "\n\t------------------------" << "\n";
				cout << "\tCall Contact"<< "\n";
				cout << "\t------------------------" << "\n";
				break;
			case 0:
				cout << "\tQuit the Phonebook"<< "\n";
				quit = true;
				break;
			default:
				cout << "\n\t[!]Wrong Option, try again" << "\n";
				cout << "\t------------------------" << "\n";
				break;
		}

		if(!quit){
			pause();
		}
	}
		
	
	
	
	return 0;
}


void addContact(ContactList* contactList,const string& filename){
	int id, ic, oc;
	string fn, ln, pNum;
	




	std::random_device rd;  
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 100);
    std::uniform_int_distribution<> newnum(1, 15);


	id = distr(gen);
	ic = newnum(gen);
	oc = newnum(gen);

	cout << "\tEnter First Name: ";
	getline(cin, fn);

	cout << "\tEnter Last Name: ";
	getline(cin, ln);


	cout << "\tEnter Phone Number: ";
	getline(cin, pNum);

	Contact newContact(id, fn,ln,pNum,ic,oc);
	contactList.push_back(newContact);
	string fullname = fn + " " + ln;
	string contactLine = to_string(id) + "|" + fullname + "|" + pNum + "|" +
                     to_string(ic) + "|" + to_string(oc); 

	saveToFile(contactLine, filename);


}

void listContacts(vector<Contact>& contactList, const string& filename){
	ifstream fin(filename);
	string name, pNum;
	int id, ic, oc;
	
	while(fin >> id){
		cout << "\n\t--------------------------------------------\n";

		cout << "\t| "
              << left << setw(4) << "ID"<< " | "
              << left << setw(20) << "NAME" << " | "
              << left << setw(15) << "PHONE" << " | "
              << left << setw(10) << "INCOMING" << " | "
              << left << setw(10) << "OUTGOING" << " |\n";	

		cout << "\t--------------------------------------------\n";

		
		fin  >> "\t| "
              >> left >> setw(4) >> id >> " | "
              >> left >> setw(20) >> name >>" | "
              >> left >> setw(15) >> pNum >> " | "
              >> left << setw(10) >> ic >> " | "
              >> left << setw(10) >> oc >> " |\n";	
		
		

	}
}


void addInternalContact(ContactList* list, Contact contact){

}
void saveToFile(string& input , const string& filename){
	ofstream myFile(filename);

	if (myFile.is_open()){
		myFile << input;
		myFile.close();
	}else {
		cout << "Error in file Opening";
	}
}

void pause(){
	  this_thread::sleep_for(chrono::milliseconds(200)); // optional
	  cout << "\n\tPress Enter to continue...";
	  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n' );
}
void clearScreen(void) {

	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}
