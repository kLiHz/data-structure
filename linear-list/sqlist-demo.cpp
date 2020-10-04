#include <iostream>
#include "sqlist.hpp"

/*int main()
{
	//SqTable a = {1,4,4,3,3,3,5,6};
	SqTable a = {1,5,3,3,3,5,1,7,9,9,7,7,5};
	//for (auto i: {2,4,5,5,5,4,2,7,9,9,7,7,6,6}) a.push_back(i);
	a.print();
	//a.deduplication();
	a.sort();
	a.print();

	int k;
	std::cin >> k;
	std::cout << a.binary_find_first_of(k) << std::endl;
	std::cout << a.binary_find_last_of(k) << std::endl;

	SqTable b = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
	std::cout << b.binary_find_last_of(5) << std::endl;
	std::cout << b.binary_find_last_of(6) << std::endl;
	return 0;
}*/

/*int main() {
	SqTable b = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
	b.erase_element(5);
	b.print();
	return 0;
}*/

int main()
{
	SqTable a = {8,1,5,3,3,5,3,1,7,9,7,9,7,5};
	SqTable b = a;
	std::cout << "a: "; a.print();
	a.sort(); // a is a ascending-ordered sequential list
	std::cout << "b: "; b.print();

	std::cout << "push 4 into the lists\n";
	a.push(4); std::cout << "a: "; a.print();
	b.push(4); std::cout << "b: "; b.print();

	std::cout << "a.size(): " << a.size() << '\n';
	std::cout << "b.size(): " << b.size() << '\n';

	std::cout << "change all 9s to 0\n";
	a.edit_element(9,0); std::cout << "a: "; a.print();
	b.edit_element(9,0); std::cout << "b: "; b.print();

	std::cout << "change all 0s to 4\n";
	a.edit_element(0,4); std::cout << "a: "; a.print();
	b.edit_element(0,4); std::cout << "b: "; b.print();	

	std::cout << "delete all 5s in the lists\n";
	a.erase_element(5); std::cout << "a: "; a.print();
	b.erase_element(5); std::cout << "b: "; b.print();

	int low, high, idx1, idx2;
	std::cout << "put elements of [2,7] in a to c\n";
	low = 2; high = 7;
	a.binary_find_first_of(low, &idx1);
	if (a.binary_find_last_of(high, &idx2) == -1) idx2 -= 1;
	SqTable c = a.subtable(idx1, idx2 - idx1 + 1);
	std::cout << "c: "; c.print();

	std::cout << "put elements of [3,6] in a to c\n";
	low = 3; high = 6;
	a.binary_find_first_of(low, &idx1);
	if (a.binary_find_last_of(high, &idx2) == -1) idx2 -= 1;
	SqTable d = a.subtable(idx1, idx2 - idx1 + 1);
	std::cout << "d: "; d.print();

	std::cout << "deduplication for a and b\n";
	a.deduplication(); std::cout << "a: "; a.print();
	b.deduplication(); std::cout << "b: "; b.print();

	std::cout << "a.size(): " << a.size() << '\n';
	std::cout << "b.size(): " << b.size() << '\n';
	std::cout << "c.size(): " << c.size() << '\n';

	return 0;
}
