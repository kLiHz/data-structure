#include "CircularQueue.hpp"
#include <iostream>

int main() {
    using ElemType = int;
    Queue<ElemType> q(15);
    std::string in;
    std::cout << std::boolalpha;
    auto usage = "Usage:\n"
                 "  pop: pop an element in 'q';\n"
                 "  push <v>: push element 'v' into 'q'\n"
                 "  exit: quit this demo.\n";

    while (true) {
        std::cin >> in;
        if (in == "exit") break;
        else if (in == "print") {
            std::cout << q << "\n";
            std::cout << "q.empty(): " << q.empty() << "; q.full(): " << q.full() << std::endl;
        }
        else if (in == "pop") {
            std::cout << "q.pop():\n";
            if (q.empty()) {
                std::cout << "The queue is already empty!" << std::endl;
                continue;
            }
            q.pop();
            std::cout << q << "\n";
            std::cout << "q.empty(): " << q.empty() << "; q.full(): " << q.full() << std::endl;
        }
        else if (in == "push") {
            std::cin >> in;
            if (q.full()) {
                std::cout << "The queue is already full!" << std::endl;
                continue;
            }
            ElemType v;
            try {
                v = std::stoi(in);
                std::cout << "q.push(" << v << "):\n";
                q.push(v);
                std::cout << q << "\n";
                std::cout << "q.empty(): " << q.empty() << "; q.full(): " << q.full() << std::endl;
            } catch (...) {
                std::cout << "Illegal input. Not pushing." << std::endl;
            }
        } else {
            std::cout << usage << std::endl;
        }
    }
}
