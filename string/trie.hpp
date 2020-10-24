#ifndef TRIE_HPP
#define TRIE_HPP

#include <iostream>
#include <cstring>
#include <list>
#include <stack>
#include <conio.h>
namespace trie
{
    template<typename CHAR_TYPE>
    struct node {
        CHAR_TYPE ch;
        size_t cnt;
        std::list<node<CHAR_TYPE>*> children;
        node() { ch = ' '; cnt = 0; }
        ~node() {
            for (auto i : children) { delete i; }
        }
        void traverse(std::string & str) {
            if (cnt > 0) 
                std::cout << str << " cnt: " << cnt << std::endl;
            for (auto i : children) {
                str += i->ch;
                i->traverse(str);
                str.pop_back();
            }
            return;
        };
    };
    template<typename CHAR_TYPE>  
    class Trie {
    private:
        node<CHAR_TYPE>  root;
    public:
        node<CHAR_TYPE>* insert(const std::string & str);
        node<CHAR_TYPE>* find(const std::string & str);
        bool             erase(const std::string & str);
        void             output();
    };
    template<typename CHAR_TYPE> 
    node<CHAR_TYPE>* Trie<CHAR_TYPE>::insert(const std::string & str) {
        node<CHAR_TYPE> * now = &root;
        for (auto i : str) {
            bool found = false;
            for (auto j : now->children) {
                if (j->ch == i) {
                    found = true; now = j; break;
                }
            }
            if (!found) {
                auto t = new node<CHAR_TYPE>;
                t->ch = i;
                now->children.push_back(t);
                now = t;
            }
        }
        ++(now->cnt);
        return now;
    }
    template<typename CHAR_TYPE> 
    node<CHAR_TYPE>* Trie<CHAR_TYPE>::find(const std::string & str) {
        node<CHAR_TYPE> * now = &root;
        for (auto i : str) {
            bool found = true;
            for (auto j : now->children) {
                if (j->ch == i) {
                    found = true; now = j; break;
                }
            }
            if (!found) {
                return nullptr;
            }
        }
        if (now->cnt > 0) return now;
        else return nullptr; // cannot find str
    }
    template<typename CHAR_TYPE> 
    bool Trie<CHAR_TYPE>::erase(const std::string & str) {
        typedef typename std::list<node<CHAR_TYPE>*>::iterator node_ptr_list_it;
        typedef node<CHAR_TYPE>* node_ptr;
        node_ptr now = &root;
        std::stack<node_ptr> history_node_ptr;
        std::stack<node_ptr_list_it> history_node_ptr_it;
        history_node_ptr.push(&root);
        for (auto i : str) {
            bool found = true;
            node_ptr_list_it j = now->children.begin();
            while (j != now->children.end()) {
                if ((*j)->ch == i) {
                    found = true;
                    now = *j;
                    history_node_ptr.push(now);
                    history_node_ptr_it.push(j); 
                    // j is the position of node:now in its father's children list
                    break;
                }
                ++j;
            }
            if (!found) return false; //cannot find str
        }
        if (now->cnt > 0) { // found
            now->cnt = 0; // remove the word from the tree
            while (!history_node_ptr_it.empty()) {
                auto i = history_node_ptr.top(); 
                history_node_ptr.pop();
                if (i->children.empty() && i->cnt == 0) {
                    delete i;
                    auto p = history_node_ptr_it.top();
                    history_node_ptr_it.pop();
                    history_node_ptr.top()->children.erase(p);
                }
                else break;
            }
            return true;
        }
        else return false; //cannot find str
    }
    template<typename CHAR_TYPE> 
    void Trie<CHAR_TYPE>::output()
    {
        std::string s;
        root.traverse(s);
    }
}

#endif
