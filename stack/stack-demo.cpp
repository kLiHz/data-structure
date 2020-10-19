#include <iostream>
#include "linkstack.hpp"

//已知表达式存储在字符串中，其中可以有大括号、中括号和小括号，试编写算法判断表达式中括号是否匹配。
bool is_matched(const char * str) 
{
    LinkStack<char> l;
    char * i = (char *) str;
    while (*i != '\0') {
        if (*i == '(' || *i == '[' || *i == '{') l.push(*i);
        else if (*i == ')') {
            if (l.top() != '(') { std::cout << *i << " dosen't match!\n"; return false;}
            else l.pop();
        }
        else if (*i == ']') {
            if (l.top() != '[') { std::cout << *i << " dosen't match!\n"; return false;}
            else l.pop();
        }
        else if (*i == '}') {
            if (l.top() != '{') { std::cout << *i << " dosen't match!\n"; return false;}
            else l.pop();
        }
        ++i;
    }
    if (!l.empty()) { std:: cout << l.top() << " doesn't match!\n"; return false; }
    else { return true; }
}

int main() 
{
    char str[] = "(!!((/{^${.{}}}/[==.[[*]&]#])))";
    if (is_matched(str)) std::cout << "All matched!\n"; 
    return 0;
}
