#include "glist.hpp"
#include <iostream>

template <typename T>
void print_glist(const GList<T> & list, int depth = 0) {
    std::cout << "(";
    for (auto i : list) {
        if (i->type() == GListElement<T>::LIST) {
            auto sublist_ptr = dynamic_cast<GList<T>*>(i);
            print_glist<T>(*sublist_ptr, depth+1);
        } 
        else { std::cout << i->data(); }
        std::cout << ",";
    }
    std::cout << "\b)";
}

int main() {
    GList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back(list);
    list.push_back('c');
    print_glist(list);
    std::cout << " depth: " << list.depth() << std::endl;
}
