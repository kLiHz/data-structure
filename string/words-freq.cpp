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
        size_t l = 0, r = t.size() - 1;
        while (useless.find(t[l]) != -1) ++l;
        while (useless.find(t[r]) != -1) --r;
        t = t.substr(l, r - l + 1);
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
