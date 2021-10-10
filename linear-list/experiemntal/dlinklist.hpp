#ifndef _DLINKLIST_HPP_
#define _DLINKLIST_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>

template<class elemType>
class DoubleLinkList 
{
private:
    class node {
    public:
        elemType data;
        node * previous;
        node * next;
        node() : next(NULL), previous(NULL) {}
        node(const elemType & x, node * p = NULL, node * n = NULL) {
            data = x; previous = p; next = n;
        } 
        ~node(); 
    }
    template<class elemType> 
    class iterator {
    public:
        DoubleLinkList<elemType>::node * item;
        iterator() : item(NULL) {};
        elemType & operator* () {return item->data; };
        DoubleLinkList<elemType>::iterator & operator++() {item = item->next; return *this; };
        DoubleLinkList<elemType>::iterator & operator--() {item = item->previous; return *this; };
    };
    node * head;
    node * tail;
    int length;
public:
    DoubleLinkList();
    DoubleLinkList(const DoubleLinkList &);
    ~DoubleLinkList() {clear(); };
    void clear();
    void insert(const iterator & _where, const elemType & _elem);
    
};

#endif