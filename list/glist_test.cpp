#include "glist.hpp"
#include <iostream>

/*template <typename T>
void print_glist(const GList<T> & list, int depth = 1){
    std::string tab(2 * depth, ' ');
    std::cout << tab << "[\n";
    auto i = list.begin();
    while (i != list.end()) { 
        auto m = *i;
        if (m->type() == GListElement<T>::ATOM) {
            std::cout << tab;
            std::cout << m->data(); 
        }
        else {
            auto sublist_ptr = dynamic_cast<GList<T>*>(m);
            print_glist<T>(*sublist_ptr, depth+1);
        }
        ++i;
        if (i != list.end()) std::cout << ",";
        std::cout << "\n";
    }
    std::cout << "]\n";
}*/

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
