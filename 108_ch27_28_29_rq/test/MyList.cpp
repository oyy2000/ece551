#include <iostream>
#include <vector>

using namespace std;

// For this coding exercise,
// you can only use C++ 98 features.Write an overloaded sum operator+ for the class MyList shown below, which takes as parameter a MyList object and appends a copy of it to the calling object.
class MyList {
private:
    class Node {
    public:
        int data;
        Node *next;
    };
    Node *head;

public:
    MyList &operator+(const MyList &rhs) {
        assert(this->head != nullptr);
        Node *thisHead = this->head;
        assert(rhs.head != nullptr);
        Node *rhsHead = rhs.head;
        Node *newList = rhs.head;
        // move the thisHead pointer to the end of calling List
        while (thisHead != nullptr && thisHead->next != nullptr) {
            thisHead = thisHead->next;
        }
        // copy the whole rhs List
        while (rhsHead != nullptr) {
            Node *node = new Node();
            try {
                node->data = rhsHead->data;
                node->next = rhsHead->next;
                newList->next = node;
            } catch (...) {
                // If exception happends while copying node,
                //  delete it and rethrow the exception.
                delete node;
                throw;
            }
        }
        newList->next = nullptr;
        // append the new List to the tail of calling List
        thisHead->next = newList;
    }
};

MyList &MyList::operator+(const MyList &other) {
    // Create a new Node to append to the calling object.
    Node *new_node = new Node();
    try {
        // Copy the data from the other MyList.
        new_node->data = other.data;
        new_node->next = other.next;

        // Append the new Node to the end of the calling MyList.
        // Find the last Node of the calling object.
        Node *last = &head;
        while (last->next != nullptr) {
            last = last->next;
        }
        // Append the new Node.
        last->next = new_node;
    } catch (...) {
        // If an exception is thrown while copying the other MyList,
        // delete the new Node and rethrow the exception.
        delete new_node;
        throw;
    }
    // Return the calling object.
    return *this;
}

// The overloaded operator should provide a strong exception guarantee.
