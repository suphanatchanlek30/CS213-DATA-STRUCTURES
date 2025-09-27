// ModifiedLinkedList.cpp
#include "ModifiedLinkedList.h"
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

void ModifiedLinkedList::add(double n)
{
    // add to head
    Node *newNode = new Node(n);
    newNode->next = head;
    head = newNode;
    ++counter;

    // อัปเดต mid ให้ชี้ตำแหน่ง floor((counter+1)/2) (เริ่มนับ 1 จากหัว)
    if (counter == 0)
    {
        mid = NULL;
    }
    else
    {
        int target = (counter + 1) / 2;
        Node *cur = head;
        for (int i = 1; i < target && cur; ++i)
            cur = cur->next;
        mid = cur;
    }
}

void ModifiedLinkedList::getData(double *&arr, int &size)
{
    size = counter;
    if (size <= 0)
    {
        arr = NULL;
        return;
    }
    arr = new double[size];
    Node *curr = head;
    for (int i = 0; i < size && curr; ++i)
    {
        arr[i] = curr->data;
        curr = curr->next;
    }
}

ModifiedLinkedList *ModifiedLinkedList::clone()
{
    ModifiedLinkedList *newList = new ModifiedLinkedList();
    if (!head)
        return newList;
    // เก็บค่าแล้ว add ย้อนท้าย -> คงลำดับเดิม head->tail
    double *arr = NULL;
    int size = 0;
    getData(arr, size);
    for (int i = size - 1; i >= 0; --i)
        newList->add(arr[i]);
    delete[] arr;
    return newList;
}

// รวมลิสต์ other มาต่อ "ด้านหัว" ของลิสต์ปัจจุบัน => ผล = other + this
ModifiedLinkedList *ModifiedLinkedList::mergeWith(ModifiedLinkedList *other)
{
    if (!other || !other->head)
        return this;
    // เชื่อมปลาย other -> head ปัจจุบัน แล้วเลื่อน head มาที่ต้น other
    Node *lastOther = other->head;
    while (lastOther->next)
        lastOther = lastOther->next;
    lastOther->next = head;
    head = other->head;
    counter += other->counter;

    // อัปเดต mid ใหม่
    int target = (counter + 1) / 2;
    Node *cur = head;
    for (int i = 1; i < target && cur; ++i)
        cur = cur->next;
    mid = cur;
    return this;
}

int ModifiedLinkedList::cut(int pos, ModifiedLinkedList *&first, ModifiedLinkedList *&second)
{
    if (pos < 1 || pos > counter)
        return -1;
    first = new ModifiedLinkedList();
    second = new ModifiedLinkedList();

    // สร้างแบบ add-to-head แล้ว clone เพื่อคืนลำดับให้ถูก (head->tail)
    Node *curr = head;
    int idx = 1;
    while (curr)
    {
        if (idx <= pos)
            first->add(curr->data);
        else
            second->add(curr->data);
        curr = curr->next;
        ++idx;
    }
    // restore order via clone
    ModifiedLinkedList *tmp;
    tmp = first->clone();
    delete first;
    first = tmp;
    tmp = second->clone();
    delete second;
    second = tmp;
    return 0; // success
}

void ModifiedLinkedList::removeAllNodes()
{
    Node *curr = head;
    while (curr)
    {
        Node *temp = curr;
        curr = curr->next;
        delete temp;
    }
    head = NULL;
    mid = NULL;
    counter = 0;
}

void ModifiedLinkedList::print()
{
    // พิมพ์ค่าโดยคร่อม mid ด้วย [] และลงท้าย ", Mid = :<val>"
    Node *curr = head;
    while (curr)
    {
        if (curr == mid)
            std::cout << "[" << curr->data << "] ";
        else
            std::cout << curr->data << " ";
        curr = curr->next;
    }
    std::cout << ", Mid = :";
    if (mid)
        std::cout << mid->data;
    else
        std::cout << "-";
    std::cout << std::endl;
}
