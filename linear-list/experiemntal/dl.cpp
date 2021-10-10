#include "dl.hpp"

dlinklist::dlinklist() {
    head = nullptr;
    tail = nullptr;
    length = 0;
}

dlinklist::dlinklist(const std::initializer_list<int> & l)
{
    length = 0;
    for (auto a : l) { push_back(a); }
}

dlinklist::dlinklist(const int * a, int _length)
{
    for (int i = 0; i < _length; ++i) push_back(a[i]);
}

dlinklist::~dlinklist()
{
    while (head != nullptr)
    {
        node * t = head; 
        head = head->next;
        delete t;
    }
}

void dlinklist::push_back(int elem) {
    node * new_node = new node;
    new_node->data = elem;
    new_node->data = elem;
    if (length > 0) {
        tail->next = new_node;
        new_node->prior = tail;
        tail = tail->next;
        ++length;
    }
    else {
        head = tail = new_node;
        ++length;
    }
}

void dlinklist::print()
{
    if (length > 0) {
        node * p = head;
        while (p != nullptr) {
            std::cout << p << ' ';
            p = p->next;
        }
        std::cout << std::endl;
    }
    else return;
}

bool dlinklist::erase(int idx) 
{
    node * p = head;
    int cnt = 0;
    while (p != nullptr) {
        if (cnt == idx){
            if (p->prior != nullptr) {p->prior = p->next;}
            if (p->next != nullptr) {p->next = p->prior;}
            --length;
            if (head == p) head = nullptr;
            if (tail == p) head = nullptr;
            delete p;
            return true;
        };
        ++cnt;
    }
    return false;
}

int & dlinklist::locate(int idx) {
    int cnt = 0;
}