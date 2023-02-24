// Returns a doubly linked list containing all the leaf elements in the given BST.
#include <iostream>
#include <vector>

// For this coding exercise, you can only use C++98 features, and cannot use the STL data types.

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

template <typename T>
class DLL {
private:
    template <typename T>
    class DLLNode {
    public:
        T data;
        DLLNode *prev;
        DLLNode *next;
        DLLNode(T data_, DLLNode *prev_, DLLNode *next_) :
            data(data_), prev(prev_), next(next_) {
        }
    };
    DLL() :
        head(nullptr) {
    }
    DLLNode<T> *head;

public:
    void insertNode(){};
    void removeNode(){};
};

template <typename T>
DLL<T> &enList(const BST<T> &tree) {
    // Create an empty doubly linked list.
    DLL<T> list;
    enListHelper(tree.root, list);
    return list;
}

template <typename T>
// using a helper to preorder traverse the tree
void enListHelper(const typename BST<T>::Node *current, DLL<T> &list) {
    if (current == nullptr) {
        return;
    }
    if (current->left == nullptr && current->right == nullptr) {
        // If the node is a leaf, add it to the doubly linked list.
        list.insertNode(current->data);
    } else {
        // else recursively visit its children.
        enListHelper(current->left, list);
        enListHelper(current->right, list);
    }
}
