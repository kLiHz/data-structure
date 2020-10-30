#include <iostream>
#include "string.hpp"

int main()
{
    String a ("The dog looks like a dog.");
    a.print();
    std::cout << std::endl;
    String sub = "dog";
    std::cout << "String \'" << "dog" << "\' found in positon: ";
    int pos = 0;
    while ((pos = a.find(sub, pos)) != -1) {
        std::cout << pos << ' ';
        pos += sub.size();
    }
    std::cout << std::endl;
    a.replace_all("dog", "kangaroo");
    a.print();
    std::cout << std::endl;
    return 0;
}

