#include <iostream>
#include <vector>

using namespace std;
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
    friend void enListHelper(DLL<T> &dll, Node &current);
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
    // initialization
    DLL() :
        head(nullptr) {
    }

    DLLNode<T> *head;

public:
    void insertNode(){};
    void removeNode(){};
};

template <typename T>
void enListHelper(DLL<T> &dll, typename BST<T>::Node &current) {
    if (current == nullptr) return;
    // dfs
    if (current->left == nullptr && current->right == nullptr) {
        // current is a leaf node, add it to the list
        DLL::DLLNode<T> *newNode = new DLL::DLLNode<T>(current->data, nullptr, nullptr);
        if (head == nullptr) {
            head = newNode;
        } else {
            tail->next = newNode;
        }
        tail = newNode;
    }

    // continue traversing the tree
    if (current->left != nullptr) {
        enListHelper(current->left);
    }
    if (current->right != nullptr) {
        enListHelper(current->right);
    }
}

// function with depth-first traversal
template <typename T>
DLL<T> *enList(BST<T> &tree) {
    DLL<T> *dll = new DLL<T>();
    enListHelper(dll, tree.root);
    return dll;
};
