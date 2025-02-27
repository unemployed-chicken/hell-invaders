#pragma once
#include <memory>
using std::shared_ptr;


template < class T>
struct Node : public std::enable_shared_from_this<Node<T>> {
    shared_ptr<T> Data;
    shared_ptr<Node<T>> Previous = nullptr;
    shared_ptr<Node<T>> Next = nullptr;

    Node(shared_ptr<T> data) : Data(data) {}
    ~Node() {
        Previous = nullptr;
        Next = nullptr;
    }

    void linkPrevious(shared_ptr<Node<T>> node) {
        Previous = node;
    }

    void linkNext(shared_ptr<Node<T>> node) {
        Next = node;
        node->linkPrevious(this->shared_from_this());
    }

    void pop() {
        if (Previous != nullptr && Next != nullptr) {
            Previous->Next = Next;
            Next->Previous = Previous;
        }
        else if (Previous != nullptr) { Previous->Next = nullptr; }
        else if (Next != nullptr) { Next->Previous = nullptr; }
    }
};

template <class T>
class DoubleLinkedList {
    shared_ptr<Node<T>> Head; // Specify the template argument <T> for Node
    shared_ptr<Node<T>> Tail;
    int Count;

public:
    DoubleLinkedList(std::shared_ptr<Node<T>> node) : Head(node), Tail(node), Count(1) {}
    DoubleLinkedList() { 
        Head = nullptr;
        Tail = nullptr;
        Count = 0;
    }
    ~DoubleLinkedList() {}

    shared_ptr<Node<T>> getHead() { return Head; }
    shared_ptr<Node<T>> getTail() { return Tail; }
    int getCount() { return Count; }
    
    void insertAtEnd(std::shared_ptr<Node<T>> node) { // If Head and Tail do not exist, this will make the node the head and the tail
        if (!Tail) {
            Head = Tail = node;
        }
        else {
            node->linkPrevious(Tail);
            Tail->linkNext(node);
            Tail = node;
        }
        ++Count;
    }

    void deleteHead() { // This will delete tail if there is only one node
        if (!Head) {
            return;
        }
        else if (!Head->Next) {
            Head = nullptr;
            Tail = nullptr;
        }
        else {
            Head = Head->Next;
            Head->Previous->pop();
        }
        --Count;
    }

    void deleteTail() { // This will delete head if there is only one node
        if (!Tail) {
            return;
        }
        else if (!Tail->Previous) {
            Head = nullptr;
            Tail = nullptr;
        }
        else {
            Tail = Tail->Previous;
            Tail->Next->pop();
        }
        --Count;
    }

    void popNode(shared_ptr<Node<T>> node) {
        // Checks if Node is Head or Tail and removes appropriately
        if (node == Head) {
            deleteHead();
        }
        else if (node == Tail) {
            deleteTail();
        }
        else {
            node->pop();
            --Count;
        }
    }

    void deleteAllNodes() {
        while (Head) {
            popNode(Head);
        }
    }
};

