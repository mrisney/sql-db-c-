#ifndef LINKED_LIST_FUNCTIONS_TEMPLATED_H
#define LINKED_LIST_FUNCTIONS_TEMPLATED_H
#include "../../includes/node/node.h"
#include <iostream>

using namespace std;


/*
    loop through the linked list - print out each node.
*/

template <typename T>
void _print_list(node<T>* head) {
    node<T>* current = head;
    while (current != nullptr) {
        cout << *current;
        current = current->_next;
    }
    cout << "nullptr" << endl;
}

/*
    recursively traverses the linked list in reverse order
    to print out each node, as it unwinds the recursion.
*/

template <typename T>
void _print_list_backwards(node<T>* head) {
    if (head == nullptr) {
        return;
    }
    _print_list_backwards(head->_next);
    cout << *head;
}

/*
    simple search through nodes, if key matches, return node else return nullptr
*/

template <typename T>
node<T>* _search_list(node<T>* head, T key) {
    for (node<T>* _node = head; _node != nullptr; _node = _node->_next) {
        if (_node->_item == key) {
            return _node;
        }
    }
    return nullptr;
}

/*
    create a new node, 
    update new node's next pointer search through nodes, 
    if key matches, return node else return nullptr,
    update previous head's previous pointer.
    if the current head is not nullptr (i.e., the list is not empty), 
    the _prev pointer of the current head is updated to point to the new node. 
    this maintains the doubly linked list property.
    update list's head pointer. 
    finally, the head pointer of the linked list is updated to point to the new node, 
    making the new node the new head of the list.
*/

template <typename T>
node<T>* _insert_head(node<T>*& head, T insert_this) {
    node<T>* new_node = new node<T>(insert_this);
    new_node->_next = head;
    if (head != nullptr) {
        head->_prev = new_node;
    }
    head = new_node;
    return head;
}

/*
    inserts a new node with the provided value after a specified node in the linked list. 
    if the given node is nullptr, the function behaves as _insert_head to insert at the beginning. 
    the function establishes the necessary links to maintain the list's integrity, 
    and returns a pointer to the newly inserted node.
*/
template <typename T>
node<T>* _insert_after(node<T>*& head, node<T>* after_this, T insert_this) {
    if (after_this == nullptr) {
        return _insert_head(head, insert_this);
    }
    node<T>* new_node = new node<T>(insert_this);
    new_node->_prev = after_this;
    new_node->_next = after_this->_next;
    if (after_this->_next != nullptr) {
        after_this->_next->_prev = new_node;
    }
    after_this->_next = new_node;
    return new_node;
}

/*
    inserts a new node with the given value before a specified node in the linked list. 
    if the given node is nullptr, the function behaves as _insert_head to insert at the beginning. 
    adjusts the necessary pointers to ensure proper linkage within the list and returns a pointer to the newly inserted node.
*/
template <typename T>
node<T>* _insert_before(node<T>*& head, node<T>* before_this, T insert_this) {
    if (before_this == nullptr) {
        return _insert_head(head, insert_this);
    }
    node<T>* new_node = new node<T>(insert_this);
    new_node->_next = before_this;
    new_node->_prev = before_this->_prev;
    if (before_this->_prev != nullptr) {
        before_this->_prev->_next = new_node;
    }
    before_this->_prev = new_node;
    return new_node;
}

/*
    returns a pointer to the node preceding a given node in the linked list. 
    If the input node is nullptr, the function returns nullptr as well. 
*/

template <typename T>
node<T>* _previous_node(node<T>* prev_to_this) {
    if (prev_to_this == nullptr) {
        return nullptr;
    }
    return prev_to_this->_prev;
}

/* 
    removes a specified node from the linked list and returns the value stored in that node. 
    if it is at the list's head, the list's head pointer is updated accordingly
*/

template <typename T>
T _delete_node(node<T>*& head, node<T>* delete_this) {
    if (delete_this == nullptr) {
        return T(); 
    }
    if (delete_this->_prev != nullptr) {
        delete_this->_prev->_next = delete_this->_next;
    } else {
        head = delete_this->_next;
    }
    if (delete_this->_next != nullptr) {
        delete_this->_next->_prev = delete_this->_prev;
    }
    T deleted_item = delete_this->_item;
    delete delete_this;
    return deleted_item;
}

/* 
    duplicates a linked list, clear out dest list, 
    create a new list with nodes containing the same values as the source list. 
    returns a pointer to the last node in the newly created list, 
*/
template <typename T>
node<T>* _copy_list(node<T>*& dest, node<T>* src) {
    _clear_list(dest);
    node<T>* _node = src;
    node<T>* prev_dest = nullptr;
    while (_node != nullptr) {
        node<T>* new_node = new node<T>(_node->_item);
        if (prev_dest != nullptr) {
            prev_dest->_next = new_node;
            new_node->_prev = prev_dest;
        } else {
            dest = new_node;
        }
        prev_dest = new_node;
        _node = _node->_next;
    }
    return prev_dest;
}

/*
    deallocates memory by deleting all nodes in the linked list. 
    updates the list's head pointer to nullptr, effectively emptying the list.
*/

template <typename T>
void _clear_list(node<T>*& head) {
    while (head != nullptr) {
        node<T>* temp = head;
        head = head->_next;
        delete temp;
    }
}
/*
    returns the value stored in a node at a specific position in the linked list.
    takes an index as input and returns a reference to the value.
*/
template <typename T>
T& _at(node<T>* head, int pos) {
    node<T>* node = head;
    for (int i = 0; i < pos; ++i) {
        if (node == nullptr) {
            throw out_of_range("Index out of bounds");
        }
        node = node->_next;
    }
    return node->_item;
}

#endif // LINKED_LIST_FUNCTIONS_TEMPLATED_H