// ModifiedLinkedList.h
#ifndef MODIFIED_LINKED_LIST_H
#define MODIFIED_LINKED_LIST_H

#include <cstddef>

class ModifiedLinkedList
{
public:
    ModifiedLinkedList()
    {
        head = NULL;
        counter = 0;
    }
    void add(double);
    void getData(double *&, int &);
    ModifiedLinkedList *clone();
    ModifiedLinkedList *mergeWith(ModifiedLinkedList *);
    int cut(int, ModifiedLinkedList *&, ModifiedLinkedList *&);
    void removeAllNodes();
    void print();

protected:
    struct Node
    {
        double data;
        Node *next;
        Node(double d)
        {
            data = d;
            next = NULL;
        }
    };
    int counter;
    Node *head;
    Node *mid;
};

#endif // MODIFIED_LINKED_LIST_H