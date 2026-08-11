#pragma once
#include <iostream>


void  detectDanglingPointer();


template<typename T>
class LinkedList {

	private:
		struct Node {
			T data{};
			Node * next{};
			explicit Node(const T& value) : data(value) , next(nullptr) {}
		};

	public:
		LinkedList() = default;
		Node * head{nullptr};

		void addNode(const T& value) {
			Node* newNode = new Node(value);
			newNode->next = head;
			head = newNode;
		}

		void printList(){
			auto* curr = head;

			while(curr){
				std::cout << curr->data << ' ';
				curr = curr->next;
			}
		}



};
