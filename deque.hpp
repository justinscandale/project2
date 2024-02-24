//DEQUE CLASS FOR PROJECT 2
//JUSIN SCANDALE & TSEGA AMANUEL

#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    size_t size;

public:
    Deque() : head(nullptr), tail(nullptr), size(0) {}

    ~Deque() {
        clear();
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void pushFront(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }

    void pushBack(const T& value) {
        Node* newNode = new Node(value);
        if (empty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void popFront() {
        if (empty()) {
            std::cerr << "Deque is empty. Cannot pop from front.\n";
            return;
        }
        Node* temp = head;
        head = head->next;
        if (head)
            head->prev = nullptr;
        else
            tail = nullptr;
        delete temp;
        size--;
    }

    void popBack() {
        if (empty()) {
            std::cerr << "Deque is empty. Cannot pop from back.\n";
            return;
        }
        Node* temp = tail;
        tail = tail->prev;
        if (tail)
            tail->next = nullptr;
        else
            head = nullptr;
        delete temp;
        size--;
    }

    T& front() const {
        if (empty()) {
            throw std::out_of_range("Deque is empty. Cannot access front element.");
        }
        return head->data;
    }

    T& back() const {
        if (empty()) {
            throw std::out_of_range("Deque is empty. Cannot access back element.");
        }
        return tail->data;
    }

    void clear() {
        while (!empty()) {
            popFront();
        }
    }
};

#endif