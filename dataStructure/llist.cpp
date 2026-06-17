#include <iostream>

template<typename T>
struct Node {
	
	T data;
	Node *next{nullptr};
	explicit Node(const T& val) : data(val) {}



};

template<typename T>
class LList{

	private:
		Node<T>* head{nullptr};

	
	public:

		void printLL(){

			while(head != nullptr){
				std::cout << head->data << " --> ";
				head = head->next;
			}

		}

		void insertNode(T value){

			Node<T>* num = new Node(value);

			num->next = head;
			head = num;
		}

};



int main(){
	std::cout << "Hello, World" << '\n';

	LList<int> ll{};
	ll.insertNode(1);
	ll.insertNode(2);
	ll.printLL();
	std::cout << '\n';

	return 0;
}
