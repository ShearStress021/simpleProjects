#include <iostream>
#include <ranges>
#include <vector>








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
		void insertNode(const T& value){
			Node *newNode = new Node(value);
			newNode->next = head;
			head = newNode;
		}
		// insert at end;
		void insertNodeAtEnd(const T& value){
			Node *newNode = new Node(value) ;

			if(head == nullptr){
				head = newNode;
				return;
			}

			Node * curr = head;
			while(curr->next){
			curr = curr->next;
			}
			curr->next = newNode;
		}

		// free list
		void clearNodes(){
			while(head != nullptr){
				Node * n = head->next;
				delete head;
				head = n;
			}
			head = nullptr;
		}
};


int main(){

	std::vector<int> nums {1,2,3,4,5};
	auto nr = std::ranges::views::reverse(nums);

	auto n =   nums | std::views::filter([](int n){ return n % 2==0; });
	
	LinkedList<int> ll {};
//	ll.insertNode(12);

	ll.insertNodeAtEnd(50);
	ll.insertNode(20);
	ll.printLL();
	return 0;
}
