// Operators.cpp
#include "Operators.h"
#include "ModifiedLinkedList.h"
#include <iostream>
using namespace std;

// ===== helpers =====
void Operators::pushList(ModifiedLinkedList *L)
{
    if (topList + 1 >= maxTopLists)
    {
        cout << "[X] List stack overflow!\n";
        return;
    }
    lists[++topList] = L;
}
ModifiedLinkedList *Operators::popList()
{
    if (topList < 0)
        return NULL;
    ModifiedLinkedList *t = lists[topList];
    lists[topList] = NULL;
    --topList;
    return t;
}
void Operators::pushOp(Op *O)
{
    if (topOp + 1 >= maxTopOps)
    {
        cout << "[X] Operator stack overflow!\n";
        return;
    }
    ops[++topOp] = O;
}
Operators::Op *Operators::popOp()
{
    if (topOp < 0)
        return NULL;
    Op *t = ops[topOp];
    ops[topOp] = NULL;
    --topOp;
    return t;
}

// ===== public =====
void Operators::makeList(double arr[], int size)
{
    if (topList != -1)
    {
        cout << "[X] Cannot make a new list: list stack is not empty.\n";
        return;
    }
    ModifiedLinkedList *list = new ModifiedLinkedList();
    // ใส่ย้อนจากท้าย -> add-to-head แล้วจะออกมา 1..n
    for (int i = size - 1; i >= 0; --i)
        list->add(arr[i]);
    pushList(list);
}

void Operators::cutList(int pos)
{
    if (topList < 0)
    {
        cout << "[X] No list to cut!\n";
        return;
    }
    ModifiedLinkedList *first = NULL, *second = NULL;
    int res = lists[topList]->cut(pos, first, second);
    if (res != 0)
    {
        cout << "[X] Invalid cut position!\n";
        return;
    }
    // ลบต้นฉบับ แล้ว push ซ้ายก่อนขวา
    delete popList();
    pushList(first);
    pushList(second);
    pushOp(new Op(pos));
    cout << "CUT Operation has been done.\n";
}

void Operators::cloneList()
{
    if (topList < 0)
    {
        cout << "[X] No list to clone!\n";
        return;
    }
    ModifiedLinkedList *cloned = lists[topList]->clone();
    pushList(cloned);
    pushOp(new Op(-1));
    cout << "CLONE Operation has been done.\n";
}

void Operators::printCurrentList()
{
    cout << "================ CURRENT LIST ================\n";
    if (topList < 0)
        cout << "[X] Nothing to print.\n";
    else
        lists[topList]->print();
    cout << "=============================================\n";
}

void Operators::printHistory()
{
    cout << "================= LIST STACK =================\n";
    if (topList < 0)
    {
        cout << "[X] Nothing in this stack ...\n";
    }
    else
    {
        for (int i = 0; i <= topList; ++i)
        {
            cout << "Index in the stack: " << i << "\n";
            lists[i]->print();
        }
    }
    cout << "================ OPERATORS ===================\n";
    if (topOp < 0)
    {
        cout << "[X] Nothing in this stack ...\n";
    }
    else
    {
        for (int i = 0; i <= topOp; ++i)
        {
            cout << i << ": " << ops[i]->op;
            if (ops[i]->op == "CUT")
                cout << " @pos=" << ops[i]->pos;
            cout << "\n";
        }
    }
    cout << "=============================================\n";
}

void Operators::undo()
{
    if (topOp < 0)
    {
        cout << "[X] No operation to undo!\n";
        return;
    }
    Op *lastOp = popOp();
    if (lastOp->op == "CUT")
    {
        // เอา right แล้ว left ออกมา แล้วคืนสภาพเป็น left + right
        if (topList < 1)
        {
            cout << "[X] Not enough lists to undo CUT!\n";
            delete lastOp;
            return;
        }
        ModifiedLinkedList *right = popList();
        ModifiedLinkedList *left = popList();
        // mergeWith: prefix 'other' -> this  ดังนั้น right->mergeWith(left) = left+right
        right->mergeWith(left);
        pushList(right);
        delete left;
        cout << "Undone [CUT] Operator ....\n";
    }
    else
    {
        if (topList < 0)
        {
            cout << "[X] No list to undo CLONE!\n";
            delete lastOp;
            return;
        }
        delete popList();
        cout << "Undone [CLONE] Operator ....\n";
    }
    delete lastOp;
}

Operators::~Operators()
{
    while (topList >= 0)
        delete popList();
    while (topOp >= 0)
        delete popOp();
}
