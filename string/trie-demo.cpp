#include <iostream>
#include "trie.hpp"

int main() //TestProgram
{
    void help();
    trie::Trie<char> words;
    bool flag = true;
    help();
    while (flag)
    {
        std::string str;
        std::cout << "> ";
        char ch = getch();
        std::cout << ch << "\n";
        switch (ch)
        {
        case 'a':
            std::cout << "Push a string > ";
            std::getline(std::cin, str);
            std::cout << "This string has appeared for " << words.insert(str)->cnt << " times." << std::endl;
            break;
        case 'f':
            std::cout << "Find a string > ";
            std::getline(std::cin, str);
            trie::node<char> * find;
            find = words.find(str);
            if (find == nullptr)
                std::cout << "Not found." << std::endl;
            else
                std::cout << "This string has appeared for " << find->cnt << " times." << std::endl;
            break;
        case 'r':
            std::cout << "Delete a string > ";
            std::getline(std::cin, str);
            std::cout << "Deletion " << (words.erase(str) ? "succeed." : "failed.") << std::endl;
            break;
        case 'v':
            std::cout << "All words: " << std::endl;
            words.output();
            break;
        case 'q':
            flag = false;
            std::cout << "Exiting demo..." << std::endl;
            break;
        case 'h':
            help();
            break;
        default:
            std::cout << "Illegal command!" << std::endl;
            break;
        }
    }
    return 0;
}

void help()
{
    std::cout << "---------------------------------\n";
    std::cout << "| * Input a to push a string;   |\n";
    std::cout << "| * Input f to find a string;   |\n";
    std::cout << "| * Input r to delete a string; |\n";
    std::cout << "| * Input v to view all words;  |\n";
    std::cout << "| * Input h for help;           |\n";
    std::cout << "| * Input q to exit.            |\n";
    std::cout << "---------------------------------\n";
}
