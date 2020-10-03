// !!!NOT FINISHED!!!
#include <iostream>
#include <cstring>
//#include "carray-template.cpp"
#include <algorithm>

class SqTable
{
private:
	int * ptr;
	
	int order; // 1 for ascending, -1 for descending
	int length;
	int arraySize;
public:
	SqTable() {
		order = 0;
		length = arraySize = 0;
		ptr = nullptr;
	};

	SqTable(const std::initializer_list<int> & l) {
		order = 0;
		length = arraySize = 0;
		ptr = nullptr;
		for (auto a : l) {
			push_back(a);
		}
	};

	SqTable(int _size) : arraySize(_size){
		order = 0;
		if (arraySize > 0) {
			length = 0;
			ptr = new int[arraySize];
		}
		else {
			ptr = nullptr;
			length = arraySize = 0;
		}
	};

	SqTable(const int * a, int _length) {
		order = 0;
		if(_length > 0) {
			length = arraySize = _length;
			ptr = new int[_length];
			memcpy(ptr, a, _length * sizeof(int));
		}
		else {
			length = arraySize = 0;
			ptr = nullptr;
		}
	}

	SqTable(const SqTable & l){
		order = l.order;
		if (l.length > 0) {
			arraySize = l.arraySize;
			ptr = new int[arraySize];
			memcpy(ptr, l.ptr, sizeof(int)*length);
		}
		else {
			ptr = nullptr;
			arraySize = length = 0;
		}
	}
	
	~SqTable(){
		if (ptr != nullptr) delete[] ptr;
	}

	SqTable & operator= (const SqTable & l) {
		if (ptr == l.ptr) return *this;
		if (ptr != nullptr) delete[] ptr;
		order = l.order;
		if (l.length > 0) {
			length = l.length;
			if (l.length > arraySize) {
				delete[] ptr;
				arraySize = l.arraySize;
				ptr = new int[arraySize];
			}
			memcpy(ptr, l.ptr, sizeof(int)*l.length);
		}
		else {
			length = 0;
		}
		return *this;
	}
	
	SqTable subtable(int idx, int _length){
		return SqTable(&ptr[idx], _length);
	}
	
	void enlarge(int enlargeNum = 5){
		int * newPtr = new int[arraySize + enlargeNum];
		arraySize = arraySize + enlargeNum;
		memcpy(newPtr, ptr, sizeof(int) * length);
		if (ptr != nullptr) delete[] ptr;
		ptr = newPtr;
	};

	void push_back(const int & element){
		if (length >= arraySize) enlarge();
		ptr[length++] = element;
		order = 0;
	};

	void sort(){
		std::sort(ptr, ptr+length);
		order = 1;
	}

	void deduplication() {
		int k, i;
		if (order == 1) { //对于顺序有序表，这里是一种O(n)的做法
			k = 1, i = k; //用两个变量，k指向当前位置，i用来指向要移动的数据
			while (i < length){
				if (ptr[i] != ptr[i-1]) {
					//如果元素和前一位置不等，说明不是重复元素，则执行"搬运"
					if (i != k) ptr[k] = ptr[i];
					++k;
				}
				++i;
			}
			length = k; //记得更新新的表的长度！
		}
		else {
			k = 0, i = 0;
			while (i < length) {
				bool isExist = false;
				for (int j = 0; j < k; j--) {
					if (ptr[j] == ptr[i]) {
						isExist = true;
						break;
					}
				}
				if (!isExist) {ptr[k++] = ptr[i++];}
				else ++i;
			}
			length = k;
		}
	};

	void print() {
		for (int i = 0; i < length; ++i) std::cout << ptr[i] << ' ';
		std::cout << std::endl;
	}
	
	int get_element(int idx, bool * ifSuccess = nullptr) {
		if (idx < 0 || idx > length) {
			if (ifSuccess != nullptr) *ifSuccess = false;
			return -1;
		} else {
			if (ifSuccess != nullptr) *ifSuccess = false;
			return ptr[idx];
		}
	};

	void edit_element(int target, int new_value) {
	//修改值为 target 的元素为 new_value
		//简单但效率低的方法是，找到相等的数据，删除它，再插入新的数值
		//对于重复出现的数据，可用循环重复上述过程
		//但这样的方法可能会造成很多不必要的数据移动，造成效率下降
		/*int idx = -1;
		while ((idx = find(target)) != -1) { //找到了值相等的元素
			if (order == 1) { //顺序有序表
				//一个解决方法，判断是否是可以直接修改的情况，即新数据放在原位置上是否仍然有序
				//（位于端点的下标需要特殊判断），即：
				if (idx == 0 && new_value <= ptr[idx+1]) ptr[idx] = new_value; 
				else if (idx > 0 && new_value >= ptr[idx-1] && idx < length - 1 && new_value <= ptr[idx +1]) ptr[idx] = new_value; 
				else if (idx == length && new_value >= ptr[idx-1]) ptr[idx] = new_value; 
				else {remove(idx); insert(new_value)};
				//但这样的方法还是不够优秀
			}
			else ptr[idx] = new_value;
			//另外，其实这样好像还不如先统一修改、再统一排序
			//ptr[idx] = new_value;
		}
		//sort(); */
		//其实如果选用了合适的排序算法，可能"统一修改再排序"的效率和下面这种思路是差不多的
		//思路是这样的，找到要排序的元素，判断它将要插入的空间，
		//然后只移动两个区间之间的元素，提高效率
		//对于重复元素的情况，可以确定出元素的区间，以及待插入的位置，并计算要移动的数据的区间
		//然后判断元素取键和要移动的数据的区间之间的大小关系，之后进行移动
	}
	
	int & operator[] (int idx) {
		order = 0;
		if (idx > length - 1) {
			if (idx < arraySize - 1) {length = idx; return ptr[idx];}
			else return ptr[0];
		}
		else if (idx < 0) return ptr[0];
		else return ptr[idx];
	}

	int sequential_search(int target){
		int t = 0;
		while (t < length) {
			if (ptr[t] == target) return t;
			++t;
		}
		return -1;
	}
	int binary_search(int target){
		int x = 0, y = length - 1;
		while (x <= y)
		{
			int mid = (x+y)/2;
			//int mid = x + (y - x) >> 1; //防止溢出的写法
			if (ptr[mid] == target) return mid;
			else if (ptr[mid] < target) x = mid + 1;
			else y = mid - 1;
		}
		//若没有找到target，则target应在ptr[y]和ptr[x]之间
		return -1;
	}
	int binary_find_first_of(int target) {
		int x = 0, y = length - 1, mid;
		while (x < y) // 这里用 < 查找target第一次出现的位置
		{
			mid = (x + y) / 2;
			if (target <= ptr[mid]) y = mid; //不关心target最后出现的位置，区间右端点改为mid
			else x = mid + 1; 
			//直到 x == mid 终止
		} 
		//如果没有找到target, 则target应在x-1的位置
		if (ptr[x] == target) return x;
		else return -1;
	}
	int binary_find_last_of(int target) {
		int x = 0, y = length - 1, mid;
		while (x < y) {
			mid = (x + y) / 2;
			if (ptr[mid] <= target) x = mid + 1;
			else y = mid;
		}
		if (ptr[x - 1] == target) return x - 1;
		else return -1;
	}
	
	int find(int target) { //返回查找目标的下标, -1表示未查找到
		if (order == 1) return binary_search(target);
		else return sequential_search(target);
	}
	void insert(int target){
		
		if (order == 1) { //如果顺序表有序
			if (length >= arraySize) enlarge();
			//有序则采用二分查找
			int x = 0, y = length, mid;
			int l = -1, r = -1; //l, r用来记录连续元素区间的左右端点
			

			if (x <= y) { //二分查找到了结果
				int i = mid;
				//考虑到有重复元素的情况，我们尽可能在连续区间的后面完成插入，以减少元素挪动
				while (ptr[++i] == ptr[mid]); //循环结束后，i停在连续区间的下一个
				for (int j = length - 1; j > i; ++j) ptr[j] = ptr[j-1];
				ptr[i] = target;
			}
			else { //二分查找没有找到结果，但x, y停在了待插入位置的附近
				// 1 2 3 3 3 5 5 6 6 7 
			}
		}
		else {
			order = 0;
			push_back(target);
		}
		++length;
	}
};

int main()
{
	SqTable a = {1,4,4,3,3,3,5,6};
	//for (auto i: {2,4,5,5,5,4,2,7,9,9,7,7,6,6}) a.push_back(i);
	a.print();
	//a.deduplication();
	a.sort();
	a.print();
	for (int i = 0; i < 5; i++) {
		int k;
		std::cin >> k;
		std::cout << a.binary_find_first_of(k) << std::endl;
	}
	
}
