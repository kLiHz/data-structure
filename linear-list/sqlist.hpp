#ifndef _SQLIST_HPP_
#define _SQLIST_HPP_

#include <iostream>
#include <cstring>
#include <algorithm>

class SqTable 
{
private:
	int * ptr;
	int order; // 1 for ascending, -1 for descending
	int length;
	int arraySize;
public:
	SqTable(); 
	SqTable(const std::initializer_list<int> & l);
	SqTable(int _size);
	SqTable(const int * a, int _length);
	//SqTable(const int * _begin, const int * _end);
	SqTable(const SqTable & l);
	~SqTable();
	int size();
	SqTable & operator= (const SqTable & l);
	SqTable subtable(int idx, int _length);
	void enlarge();
	void push_back(const int & element);
	void sort();
	void deduplication();
	void print();
	int get_element(int idx, bool * ifSuccess = nullptr);
	bool edit_element(int target, int new_value);
	bool erase_element(int target);
	int & operator[] (int idx);
	int sequential_search(int target);
	int binary_search(int target, int * tgt_idx = nullptr);
	int binary_find_first_of(int target, int * tgt_idx = nullptr);
	int binary_find_last_of(int target, int * tgt_idx = nullptr);
	int upper_bound(int target);
	int find(int target);
	void push(int target);
	void insert(int idx, int target);
	void erase(int idx);
	//计划新增项目：
	//insert的重载，并集交集，迭代器等
};

#endif