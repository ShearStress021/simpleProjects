#pragma once
#include <iostream>
#include <memory>

template<typename T>
struct RNode {
	T data{};
	std::shared_ptr<RNode<T>> next{};

};

template<typename T>
class RAIILinkList {

public:
	void insertNodeAtBegin(const T& val) {
		head = std::make_shared<RNode<T>>(val, head);
	}

	void insertNodeAtEnd(const T& val) {
		auto newNode = std::make_shared<RNode<T>>(val, nullptr);

		if (!head) {
			head = std::move(newNode);
			return;
		}
		auto current = head;

		while (current->next) {
			current = current->next;
		}
		current->next = std::move(newNode);

	}
	bool removeAtBegin() {
		if (!head) {
			return false;
		}
		head = head->next;
		return true;
	}

	bool removeAtEnd() {
		if (!head) {
			return false;
		}

		if (!head->next) return removeAtBegin();

		auto current = head;

		while (current->next->next) {
			current = current->next;
		}

		current->next = nullptr;
		return true;
	}

	bool removeByValue(const T val) {
		if (!head) return false;

		if (head->data == val) return removeAtBegin();

		auto current = head;

		while (current->next && current->next->data != val) {
			current = current->next;
		}

		if (!current->next) return false;

		current->next = current->next->next;
		return true;
	}


	void reverseLList() {
		auto current = head;
		std::shared_ptr<RNode<T>> prev = nullptr;

		while (current) {
			auto temp = current->next;
			current->next = prev;
			prev = current;
			current = temp;
		}
		head = prev;
	

	}


	void print() const {
		auto current = head;

		while (current) {
			std::cout << current->data << " -> ";
			current = current->next;
		}
		std::cout << "nullptr\n";
	}
private:
	std::shared_ptr<RNode<T>> head{};
};