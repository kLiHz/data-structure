#include <iostream>
#include <fstream>
#include "trie.hpp"

int main(int argc, char* argv[]) {
    std::string filename;
    if (argc == 2) {
        filename = argv[1];
    } else {
        std::cout << "Input Filename: ";
        std::cin >> filename;
    }
    std::fstream inFile;
    inFile.open(filename);
    std::string t;
    std::string useless = "(),.;?!\"-";
    trie::Trie<char> words;
    while (inFile >> t) { 
        while (useless.find(*(t.begin())) != -1) t.erase(t.begin());
        while (useless.find(*(t.rbegin())) != -1) t.pop_back();
        auto i = t.begin();
        while (i != t.end()) {
            if (*i >= 'A' && *i <= 'Z') *i = *i + ('a' - 'A');
            ++i;
        }
        words.insert(t); 
    }
    inFile.close();
    words.output();
    return 0;
}
