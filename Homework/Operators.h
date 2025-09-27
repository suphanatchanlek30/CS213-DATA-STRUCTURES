// Operators.h
#ifndef OPERATORS_H
#define OPERATORS_H

#include <string>
using std::string;

class ModifiedLinkedList; // forward declaration

class Operators
{
public:
    void cutList(int);
    void undo();
    void cloneList();
    void printCurrentList();
    void printHistory();
    void makeList(double[], int);
    Operators(int sSize = 20)
    {
        ops = new Op *[sSize]();
        lists = new ModifiedLinkedList *[sSize]();
        topOp = -1;
        topList = -1;
        maxTopLists = sSize;
        maxTopOps = sSize;
    }
     ~Operators();

protected:
    struct Op
    {
        string op;
        int pos;
        Op(int position)
        {
            if (position == -1)
            {
                op = "CLONE";
                pos = -1;
            }
            else
            {
                op = "CUT";
                pos = position;
            }
        }
    };
    ModifiedLinkedList **lists;
    Op **ops;
    int topOp;
    int topList;
    int maxTopOps;
    int maxTopLists;

    // helpers
    void pushList(ModifiedLinkedList *L);
    ModifiedLinkedList *popList();
    void pushOp(Op *O);
    Op *popOp();
};

#endif // OPERATORS_H