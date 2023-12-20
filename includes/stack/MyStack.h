#ifndef MY_STACK_H
#define MY_STACK_H
#include <iostream>
#include "../../includes/node/node.h"
#include "../../includes/linked_list_functions/linkedlistfunctionsTemplated.h"

using namespace std;

template <typename ITEM_TYPE>
class Stack {
private:

    node<ITEM_TYPE>* _top; 
    int _size; 

public:

    // default constructor
    Stack() : _top(nullptr), _size(0) {}

    // copy constructor
    Stack(const Stack<ITEM_TYPE>& copyMe) : _top(nullptr), _size(0) {
        // use the _copy_list function to copy the linked list
        _copy_list(_top, copyMe._top);
        _size = copyMe._size;
    }

    // copy assignment operator
    Stack<ITEM_TYPE>& operator=(const Stack<ITEM_TYPE>& RHS) {
        if (this == &RHS) {
            return *this; // handle self-assignment
        }
        _clear_list(_top);
        _copy_list(_top, RHS._top);
        _size = RHS._size;
        return *this;
    }

    // returns an item, from the top of the stack
    ITEM_TYPE top() const {
        if (_top == nullptr) {
            throw runtime_error("Stack is empty");
        }
        return _top->_item;
    }

    // check if the stack is empty
    bool empty() const {
        return (_top == nullptr);
    }

    // push an item onto the stack
    void push(const ITEM_TYPE& item) {
        _insert_head(_top, item);
        ++_size;
    }

    // pop an item from the stack
    ITEM_TYPE pop() {
        if (_top == nullptr) {
            throw runtime_error("Stack is empty");
        }
        ITEM_TYPE popped_item = _top->_item;
        _delete_node(_top, _top);
        --_size;
        return popped_item;
    }

    // iterator class
    class Iterator {
    private:
        node<ITEM_TYPE>* _ptr; // pointer to a node

    public:
        Iterator() : _ptr(nullptr) {} // default constructor

        explicit Iterator(node<ITEM_TYPE>* ptr) : _ptr(ptr) {} // constructor, with node pointer

        ITEM_TYPE& operator*() const {
            return _ptr->_item;
        }

        Iterator& operator++() {
            if (_ptr != nullptr) {
                _ptr = _ptr->_next;
            }
            return *this;
        }

        Iterator operator++(int) {
            Iterator iter = *this;
            ++(*this);
            return iter;
        }

        bool operator!=(const Iterator& other) const {
            return _ptr != other._ptr;
        }

        bool is_null() const {
            return _ptr == nullptr;
        }
    };

    Iterator begin() const {
        return Iterator(_top); // start at the top of the stack
    }

    Iterator end() const {
        return Iterator(nullptr); // end iterator is nullptr
    }

    // friend function to print the stack
/*
    template<typename T>
    friend ostream& operator<<(std::ostream& outs, const Stack<T>& printMe) {
        _print_list(printMe._top);
        return outs;
    }
*/
    // get the size of the stack
    int size() const {
        return _size;
    }
};

#endif // MY_STACK_H