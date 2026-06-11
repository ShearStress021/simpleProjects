
#include <iostream>
#include <memory>

template<typename T>
struct Node {


    std::shared_ptr<Node<T>> next{ };

    //Node* next{};
    T data{};

    explicit Node(T value) : data(value) {}
};

template<typename T>
class LinkedList {

public:

    void insertNode(T data) {

        auto num = std::make_shared<Node<T>>(data);
        num->next = head;
        head = num;
    }

    void printList() {
        auto current = head;
        while (current) {
            std::cout << current->data << " --> ";
            current = current->next;
        }

        std::cout << "nullptr\n";
    }

    void insertNodeAtEnd(T data) {
        auto current = head;
        auto num = std::make_shared<Node<T>>(data);

        while (current->next != nullptr)
            current = current->next;

        current->next = num;
    }

    void deleteAttheEnd() {
        auto current = head;
        while (current->next->next != nullptr)
            current = current->next;

        current->next = nullptr;
    }

    void removeByValue(T data) {
        auto current = head;

        if (!current) std::cout << "List is empty\n";

        while (current->next) {
            if (current->next->data == data)
                break;
            current = current->next;

        }

        if (current->next == nullptr) std::cout << "Node not present\n";
        current->next = current->next->next;
            
    }

private:
    std::shared_ptr<Node<T>> head{};
  //  Node<T>* head{ nullptr };

};




int main()
{

    LinkedList<int> ll{};
    ll.insertNode(1);
    ll.insertNode(2);
    ll.insertNode(4);
    ll.insertNodeAtEnd(10);
    ll.insertNodeAtEnd(40);
    ll.printList();

    ll.deleteAttheEnd();

    ll.printList();

    ll.removeByValue(1);
    ll.printList();
}

