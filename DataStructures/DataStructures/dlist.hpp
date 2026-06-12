#include <iostream>
#include <memory>


template<typename T>
struct DNode {
	T data{};
	std::unique_ptr<DNode> next{};
	std::unique_ptr<DNode> prev{};
};


template<typename T>
class DoubleLinkList {

public:
	void print() {

	}



private:
	std::unique_ptr<DNode> head{};

};