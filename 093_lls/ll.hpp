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
        Node(T d) : data(d){};
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
            Node *current = new Node(1);
            current = head->next;
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
            Node *temp_head = new Node(rhs.head->data);
            Node *copy_node = temp_head;
            Node *prev = NULL;
            Node *temp_tail;
            for (Node *curr_node = rhs.head; curr_node != NULL; curr_node = curr_node->next)
            {
                if (curr_node->next != NULL)
                {                                                      // add to next if we're not at tail
                    copy_node->next = new Node(curr_node->next->data); // create new string of data
                }
                else
                { // set tail if we've reached it
                    temp_tail = copy_node;
                    copy_node->next = NULL;
                }
                copy_node->prev = prev;
                prev = copy_node;
                copy_node = copy_node->next;
            }

            // at this point curr_node should be tail
            //      Node * temp_tail = new Node(rhs.tail->data);

            for (Node *next_node = head->next; next_node != NULL;
                 next_node = next_node->next)
            { // delete old data
                delete next_node->prev;
            }
            delete tail;

            // set new info
            size = rhs.size;
            head = temp_head;
            tail = temp_tail;
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
    int &operator[](int index)
    {
        int i = 0;
        Node *node_of_interest = head;
        for (Node *curr_node = head; curr_node != NULL; curr_node = curr_node->next)
        {
            if (i == index)
            {
                node_of_interest = curr_node;
            }
            i++;
        }
        return node_of_interest->data;
    }
    const int &operator[](int index) const
    {
        int i = 0;
        Node *node_of_interest = head;
        for (Node *curr_node = head; curr_node != NULL; curr_node = curr_node->next)
        {
            if (i == index)
            {
                node_of_interest = curr_node;
            }
            i++;
        }
        return node_of_interest->data;
    }
    int find(const T &item)
    {
        int index = 0;
        for (Node *curr_node = head; curr_node != NULL; curr_node = curr_node->next)
        {
            if (curr_node->data == item)
            {
                return index;
            }
            index++;
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
