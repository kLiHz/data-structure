#ifndef _DLINKLIST_HPP_
#define _DLINKLIST_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>

//Circular-linked List
//循环单链表

template<class elemType>
struct linklist_node {
    elemType data;
    linklist_node * next;
    linklist_node() : next(nullptr) {};
    linklist_node(const elemType & _elem, linklist_node * _next = nullptr) : data(_elem), next(_next) {};
};

template<class elemType>
class linklist_iterator {
    linklist_node * the_node;
    linklist_iterator & operator++() {
        the_node = the_node->next;
        return *this;
    }
    linklist_iterator operator++(int) { //尾自增
        linklist_iterator _tmp(*this);
        the_node = the_node->next;
        return _tmp;
    }
    elemType operator->(){
        return this->the_node->data;
    }
};

class ClinkList
{
private:
    int * 
    class node {
        int data;
        int * next;
    }
public:
};

#endif