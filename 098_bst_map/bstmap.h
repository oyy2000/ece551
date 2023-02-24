#include "map.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <exception>
#include <utility>
using namespace std;
template <typename K, typename V>
class BstMap : public Map<K, V>
{
private:
    class Node
    {
    public:
        pair<K, V> data;
        Node *left;
        Node *right;

    public:
        Node() : data(0, 0), left(NULL), right(NULL){};
        Node(K k, V v) : data(k, v), left(NULL), right(NULL){};
    };
    Node *root;

public:
    BstMap() : root(NULL){};
    BstMap(const BstMap &rhs) : root(NULL)
    {
        copyTree(&root, rhs.root);
    }
    void copyTree(Node **newTree, const Node *oldTree)
    {
        if (oldTree != NULL)
        {
            *newTree = new Node(oldTree->data.first, oldTree->data.second);
            copyTree(&(*newTree)->left, oldTree->left);
            copyTree(&(*newTree)->right, oldTree->right);
        }
    }
    const BstMap &operator=(const BstMap &rhs)
    {
        if (&rhs != this)
        {
            BstMap temp = rhs;
            Node *t = root;
            root = temp.root;
            temp.root = t;
        }
        return *this;
    }
    virtual void add(const K &key, const V &value)
    {
        Node **current = &root;
        while (*current != NULL)
        {
            if ((*current)->data.first == key)
            {
                (*current)->data.second = value;
                return;
            }
            else if ((*current)->data.first > key)
            {
                current = &(*current)->left;
            }
            else
                current = &(*current)->right;
        }
        *current = new Node(key, value);
        return;
    }

    virtual const V &lookup(const K &key) const throw(std::invalid_argument)
    {
        Node *current = root;
        while (current != NULL)
        {
            if (current->data.first == key)
            {
                return current->data.second;
            }
            else if (current->data.first > key)
            {
                current = current->left;
            }
            else
            {
                current = current->right;
            }
        }
        throw std::invalid_argument("No such key");
        return current->data.second;
    }

    Node **find(const K &key)
    {
        Node **current = &root;
        while (*current != NULL)
        {
            if ((*current)->data.first == key)
            {
                return current;
            }
            else if ((*current)->data.first > key)
            {
                current = &(*current)->left;
            }
            else
            {
                current = &(*current)->right;
            }
        }
        return NULL;
    }
    virtual void remove(const K &key)
    {
        Node **current = find(key);
        Node *N2 = *current;

        if (*current == NULL)
        {
            return;
        }
        if ((*current)->left == NULL)
        {
            *current = (*current)->right;
        }
        else
        {
            Node **vic = &N2->left;
            while ((*vic)->right != NULL)
            {
                vic = &(*vic)->right;
            }
            *current = *vic;
            *vic = (*vic)->left;
            (*current)->left = N2->left;
            (*current)->right = N2->right;
        }
        delete N2;
    }

    Node *getRoot()
    {
        return root;
    }
    void print(Node *r)
    {
        if (r == NULL)
            return;
        print(r->left);
        cout << r->data.first << " " << r->data.second << endl;
        print(r->right);
    }

    void freeBst(Node *r)
    {
        if (r == NULL)
        {
            return;
        }
        freeBst(r->left);
        freeBst(r->right);
        delete r;
    }
    virtual ~BstMap()
    {
        freeBst(root);
    }
};