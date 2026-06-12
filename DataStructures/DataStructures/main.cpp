#include <iostream>
#include "llist.hpp"
#include "raiiLList.hpp"


int main() {


	RAIILinkList<int> rl{};

	rl.insertNodeAtBegin(1);
	rl.insertNodeAtBegin(3);
	rl.insertNodeAtEnd(10);
	rl.insertNodeAtEnd(40);
	rl.insertNodeAtEnd(80);

	rl.print();
	rl.removeByValue(10);
	rl.print();
	rl.reverseLList();
	rl.print();

	std::cout << "Hello, World" << '\n';
	return 0;
}