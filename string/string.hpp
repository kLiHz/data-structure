#ifndef STRING_HPP
#define STRING_HPP

#include <iostream>
#include <cstring>
#include <algorithm>

class String
{
private:
    char * ptr;
    int length;
    int arraySize;
    void get_next(int next[]) const;
    int KMP(const String & p, int pos = 0) const;
public:
    String(); 
    String(int _size);
    String(const char * str);
    String(const char * str, int _length);
    //String(const int * _begin, const int * _end);
    String(const String & l);
    ~String();
    int size() const;
    void enlarge();
    void enlarge(int _inc);
    String & operator= (const String & str);
    String substring(int idx, int _length);
    void push_back(const int & element);
    void append(const String& str);
    void append(const String& str, int subpos, int sublen);
    void print();
    char & operator[] (int idx);
    int find(const String & s, int pos = 0) const;
    void replace_all(const String & str1, const String & str2);
    String replace_all_copy(const String & str1, const String & str2);
};

#endif

/*#include <iostream>
#include <string>
#include <boost/algorithm/string/replace.hpp>

int main()
{
    std::string str = "This dog looks like a dog.";
    std::cout << str << std::endl;
    boost::replace_all(str, "dog", "elephant");
    std::cout << str << std::endl;
    return 0;
}*/

