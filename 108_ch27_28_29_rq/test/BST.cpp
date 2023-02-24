// For this coding exercise, you can only use C++98 features, and cannot use the STL data types.
#include <iostream>
#include <vector>

using namespace std;

// Write the enList function (outside of the BST class), which takes as parameter an instance of the following templated BST class, and returns a doubly linked list that contains all the leaf elements in the argument tree.

template <typename T>
class BST {
private:
    class Node {
    public:
        T data;
        Node *left;
        Node *right;
        Node(int data_) :
            data(data_), left(NULL), right(NULL){};
        Node *root;
    };
};

class DoublyLinkedList {
private:
    class Node {
    public:
        int data;
        Node *next;
    };
    Node *head;

public:
    void insertNode(){};
    void removeNode(){};
};

template <typename T>
DoublyLinkedList enList(const BST<T> &tree) {
    DoublyLinkedList list;
    list.insertNode();
}
