#pragma once
#include <memory>


template<typename T>
struct Node {

	T data{};
    Node* next{};
};

template<typename T>
class LinkedList {

public:

	~LinkedList() {

	}

	void insertNodeAtBegin(const T& val) {
		head = new Node{ val, head };
	}
	void insertNodeAtEnd(const T& val) {

		Node<T>* newNode = new Node<T>{ val, nullptr };

		if (!head) {
			head = newNode;
			return;
		}


		Node<T>* current = head;
		while (current->next) {
			current = current->next;

		}
		current->next = newNode;

	}

	bool removeAtBegin() {

		if (!head) {
			return false;
		}
		Node<T>* delNode = head;
		head = head->next;
		delete delNode;
	}

	bool removeAtEnd() {
		if (!head) {
			return false;
		}

		if (!head->next) {
			return removeAtBegin();
		}


		Node<T>* current = head;
		while (current->next->next)
			current = current->next;

		delete current->next;
		current->next = nullptr;
		return true;
	}


	bool removeByValue(const T& val) {
		if (!head) {
			return false;
		}
		if (head->data == val) {
			return removeAtBegin();

		}
		Node<T>* current = head;
		while (current->next && current->next->data != val) {
			current = current->next;
		}

		if (!current->next) {
			return false;
		}
		Node<T>* delNode = current->next;
		current->next = delNode->next;
		delete delNode;

		return true;
	}

	void reversedList() {
		
	}
	void print() {
		Node<T>* current = head;
		while (current) {
			std::cout << current->data << " --> ";
			current = current->next;
		}
		std::cout << "nullptr\n";
	}

private:
	Node<T>* head{};

};