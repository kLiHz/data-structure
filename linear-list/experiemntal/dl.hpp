#ifndef _DLINKLIST_HPP_
#define _DLINKLIST_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>

#include <list>
int a(){
    std::list<int> b;
    b.sort();
    b.insert(b.end(),1);
    std::list<int>::iterator i;
    i.operator++();
}

class dlinklist
{

public:
    struct node {
        int value;
        node * prev;
        node * next;
        int located_times; //被访问(locate)次数
        node() : prev(nullptr), next(nullptr), located_times(0) {}
    };

    struct iterator {
        dlinklist::node * my_node;
        iterator();
        iterator(dlinklist::node * x) : my_node(x) {}

        int & operator*() {
            return my_node->value; 
        } 
        iterator operator++(int) { //后自增
            iterator tmp = *this;
            my_node = my_node->next;
            return tmp;
        } 
        iterator& operator++() { //前自增
            my_node = my_node->next; 
            return *this; 
        } 
        iterator operator--(int) {
            iterator tmp = *this;
            my_node = my_node->prev;
            return tmp;
        } 
        iterator& operator--() {
            my_node = my_node->prev; 
            return *this; 
        } 
        friend bool operator==(const iterator & x, const iterator & y) {
            return x.my_node == y.my_node;
        }
        friend bool operator!=(const iterator & x, const iterator & y) {
            return x.my_node != y.my_node;
        }
    };

    dlinklist(); 
	dlinklist(const std::initializer_list<int> & l);
	dlinklist(const int * a, int _length);
	//dlinklist(const int * _begin, const int * _end);
	//dlinklist(const dlinklist & l);
	~dlinklist();
    void empty();
    dlinklist::node* locate(int elem); //返回链表中值为elem的元素的位置, 访问频度元素高的元素会被前移
    void push_back(int elem);
    void insert(node * _where, int elem);
    bool erase(node * _where);
    void print();
private:
    dlinklist::node end_node;
    int length;
};

dlinklist::dlinklist() {

}

#endif
