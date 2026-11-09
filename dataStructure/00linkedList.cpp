#include <iostream>
#include <print>

template<typename T>
class LinkedList {
	private:
		struct Node{
			T data{};
			Node* next{};
			explicit Node(const T& val): data(val){}
		};

		Node* head{nullptr};
	public:
		void insertNode(const T& val){
			Node * newNode = new Node(val);
			newNode->next = head;
			head = newNode;
			delete newNode;
		}

		void insertNodeAtLast(const T& val){
			Node * newNode = new Node(val);

			if(!head){
				head = newNode;
				return ;
			}

			while(head->next){
				head = head->next;
			}
			head->next = newNode;
			delete newNode;
		}

		void printLL(){
			while(head != nullptr){
				std::print("{}->",head->data);
				head = head->next;
			}
		}
};



int main(){

	LinkedList<int> ll{};
	ll.insertNode(10);
	ll.insertNodeAtLast(30);
	ll.insertNode(20);

	ll.printLL();

}

