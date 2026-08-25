#include <iostream>




template<typename T>
class LinkedList {
	private:
		struct Node {
			T data{};
			Node *next{nullptr};
			explicit Node(const T& val) : data(val) {}

		};

	public:
		Node *head{nullptr};

		~LinkedList(){
			clearNodes();

		}
		void printLL(){
			while(head != nullptr){
				std::cout << head->data << "-> " ;
				head = head->next;
			}
		}

		// insert at the begin
		void insertNode(T value){
			Node *newNode = new Node(value);
			newNode->next = head;
			head = newNode;
		}
		// insert at end;
		void insertNodeAtEnd(T value){
			Node *newNode = new Node(value) ;

			if(!head ){
				head = newNode;
				return;
			}

			Node * curr = head;
			while(curr->next){
			curr = curr->next;

			}
			curr->next = newNode;
		}

		void clearNodes(){
			while(head != nullptr){
				Node * n = head->next;
				delete head;
				head = n;

			}
			head = nullptr;

		}
		// 





};


int main(){
	LinkedList<int> ll {};
//	ll.insertNode(12);

	ll.insertNodeAtEnd(50);
//	ll.insertNode(20);
	ll.printLL();
	return 0;
}
