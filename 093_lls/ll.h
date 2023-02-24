#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>

// YOUR CODE GOES HERE
class Tester;

template <typename T>
class LinkedList
{
private:
    class Node
    {
    public:
        T data;
        Node *next;
        Node *prev;
        Node(T d) : data(d), next(NULL), prev(NULL){};
        Node(T d, Node *n, Node *p) : data(d), next(n), prev(p){};
    };
    Node *head;
    Node *tail;
    int size;

public:
    LinkedList() : head(NULL), tail(NULL), size(0){};
    ~LinkedList()
    {
        while (head != NULL)
        {
            Node *current = head->next;
            delete head;
            head = current;
        }
        size--;
    };
    LinkedList(const LinkedList &rhs) : head(NULL), tail(NULL), size(0)
    {
        for (Node *cur = rhs.head; cur != NULL; cur = cur->next)
        {
            addBack(cur->data);
        }
    }
    LinkedList &operator=(const LinkedList &rhs)
    {
        if (this != &rhs)
        {
            Node *temp = head;
            while (temp != NULL)
            {
                temp = temp->next;
                delete head;
                head = temp;
            }
            size = 0;
            Node *curr = rhs.head;
            while (curr != NULL)
            {
                addBack(curr->data);
                curr = curr->next;
            }
        }
        return *this;
    }
    void addFront(const T &item)
    {
        head = new Node(item, head, NULL);
        if (tail == NULL)
        {
            tail = head;
        }
        else
        {
            head->next->prev = head;
        }
        size++;
    };
    void addBack(const T &item)
    {
        tail = new Node(item, NULL, tail);
        if (head == NULL)
        {
            head = tail;
        }
        else
        {
            tail->prev->next = tail;
        }
        size++;
    }
    bool remove(const T &item)
    {
        for (Node *cur = head; cur != NULL; cur = cur->next)
        {
            if (item == cur->data)
            {
                if (cur == head)
                {
                    head = cur->next;
                }
                if (cur == tail)
                {
                    tail = cur->prev;
                }
                if (cur->next != NULL)
                {
                    cur->next->prev = cur->prev;
                }
                if (cur->prev != NULL)
                {
                    cur->prev->next = cur->next;
                }
                delete cur;
                size--;
                return true;
            }
        }
        return false;
    };
    T &operator[](int index)
    {
        int i = 0;
        Node *current = head;
        while (current != NULL)
        {
            if (i == index)
            {
                return current->data;
            }
            current = current->next;
            i++;
        }
        return current->data;
    }
    const T &operator[](int index) const
    {
        int i = 0;
        Node *current = head;
        while (current != NULL)
        {
            if (i == index)
            {
                return current->data;
            }
            current = current->next;
            i++;
        }
        return current->data;
    }
    int find(const T &item)
    {
        int i = 0;
        Node *current = head;
        while (current != NULL)
        {
            if (current->data == item)
            {
                return i;
            }
            current = current->next;
            i++;
        }
        return -1;
    }
    int getSize() const
    {
        return size;
    };
    friend class Tester;
};

#endif
