#include <iostream>




template<typename T>
class LinkedList {
	private:
		struct Node {
			T data{};
			Node *next{nullptr};
			explicit Node(const T& val) : data(val) {}

			~Node(){
				delete next;
			}
		};

	public:
		Node *head{nullptr};

		~LinkedList(){
			delete[] head;

		}
		void printLL(){
			while(head != nullptr){
				std::cout << head->data << "-> " ;
				head = head->next;
			}
		}

		// insert at the begin
		void insertNode(T value){
			Node *element = new Node(value);
			element->next = head;
			head = element;
		}
		// 





};


int main(){
	LinkedList<int> ll {};
	ll.insertNode(12);
	ll.insertNode(20);
	ll.printLL();
	return 0;
}
