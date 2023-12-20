#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <iostream>
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename T>
class Queue {
public:
    class Iterator {
    public:
        friend class Queue;

        Iterator() : _ptr(nullptr) {}
        Iterator(node<T>* p) : _ptr(p) {}

        T operator*() {
            return _ptr->_item;
        }

        bool is_null() {
            return _ptr == nullptr;
        }

        friend bool operator!=(const Iterator& left, const Iterator& right) {
            return left._ptr != right._ptr;
        }

        friend bool operator==(const Iterator& left, const Iterator& right) {
            return left._ptr == right._ptr;
        }

        Iterator& operator++() {
            if (_ptr != nullptr) {
                _ptr = _ptr->_next;
            }
            return *this;
        }

        Iterator operator++(int unused) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

    private:
        node<T>* _ptr;
    };

    Queue() : _front(nullptr), _rear(nullptr), _size(0) {}
    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue<T>& operator=(const Queue<T>& RHS);

    bool empty() const;
    T front() const;
    T back() const;

    void push(const T& item);
    T pop();

    Iterator begin() const;
    Iterator end() const;

    void print_pointers();
    int size() const;

    template<typename TT>
    friend ostream& operator<<(ostream& outs, const Queue<TT>& printMe);

private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

// constructor
template<typename T>
Queue<T>::Queue(const Queue<T>& copyMe) : _front(nullptr), _rear(nullptr), _size(0) {
    _rear = _copy_list(_front, copyMe._front);
    _size = copyMe._size;
}

// destructor
template<typename T>
Queue<T>::~Queue() {
    while (!empty()) {
        pop();
    }
}

// copy assignment operator
template<typename T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS) {
    if (this == &RHS) {
        return *this;
    }
    while (!empty()) {
        pop();
    }
    _rear = _copy_list(_front, RHS._front);
    _size = RHS._size;
    return *this;
}

// check if the queue is empty
template<typename T>
bool Queue<T>::empty() const {
    return _size == 0;
}

// return the item at the front of the queue
template<typename T>
T Queue<T>::front() const {
    if (empty()) {
        throw runtime_error("Queue is empty");
    }
    return _front->_item;
}

// return the item at the back of the queue
template<typename T>
T Queue<T>::back() const {
    if (empty()) {
        throw runtime_error("Queue is empty");
    }
    return _rear->_item;
}

// push an item onto the back of the queue
template<typename T>
void Queue<T>::push(const T& item) {
    if (empty()) {
        // If the queue is empty, set both front and rear to the new node
        _front = new node<T>(item);
        _rear = _front;
    } else {
        // Otherwise, insert after the current rear and update rear to the new node
        _insert_after(_front, _rear, item);
        _rear = _rear->_next;
    }
    ++_size;
}

// pop an item from the front of the queue
template<typename T>
T Queue<T>::pop() {
    if (empty()) {
        throw runtime_error("Queue is empty");
    }

    T popped_item = _front->_item;
    _delete_node(_front, _front); // use _delete_node to remove the front node

    if (empty()) {
        _rear = nullptr; // if queue is empty, also update rear to nullptr
    }

    --_size;
    return popped_item;
}

// return an iterator to the front of the queue
template<typename T>
typename Queue<T>::Iterator Queue<T>::begin() const {
    return Iterator(_front);
}

// return an iterator to the end of the queue (nullptr)
template<typename T>
typename Queue<T>::Iterator Queue<T>::end() const {
    return Iterator(nullptr);
}

// print pointers
template<typename T>
void Queue<T>::print_pointers() {
    cout << "Front: " << _front << ", Rear: " << _rear << endl;
}

// return the size of the queue
template<typename T>
int Queue<T>::size() const {
    return _size;
}

// friend function to print the queue
template<typename T>
ostream& operator<<(ostream& outs, const Queue<T>& printMe) {
    _print_list(printMe._front);
    return outs;
}

#endif // MY_QUEUE_H