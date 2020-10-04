#include "sqlist.hpp"

SqTable::SqTable() {
	order = 0;
	length = arraySize = 0;
	ptr = nullptr;
}

SqTable::SqTable(const std::initializer_list<int> & l) {
	order = 0;
	length = arraySize = 0;
	ptr = nullptr;
	for (auto a : l) {
		push_back(a);
	}
}

SqTable::SqTable(int _size) : arraySize(_size) {
	order = 0;
	if (arraySize > 0) {
		length = 0;
		ptr = new int[arraySize];
	}
	else {
		ptr = nullptr;
		length = arraySize = 0;
	}
}

SqTable::SqTable(const int * a, int _length) {
	order = 0;
	if (_length > 0) {
		length = arraySize = _length;
		ptr = new int[_length];
		memcpy(ptr, a, _length * sizeof(int));
	}
	else {
		length = arraySize = 0;
		ptr = nullptr;
	}
}

//SqTable::SqTable(const int * _begin, const int * _end) {}

SqTable::SqTable(const SqTable & l){
	order = l.order;
	if (l.length > 0) {
		length = l.length;
		arraySize = l.arraySize;
		ptr = new int[arraySize];
		memcpy(ptr, l.ptr, sizeof(int)*length);
	}
	else {
		ptr = nullptr;
		arraySize = length = 0;
	}
}

SqTable::~SqTable(){
	if (ptr != nullptr) delete[] ptr;
}

SqTable & SqTable::operator= (const SqTable & l) {
	if (ptr == l.ptr) return *this;
	order = l.order;
	if (l.length > 0) {
		length = l.length;
		if (l.length > arraySize) {
			if (ptr != nullptr) delete[] ptr;
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

SqTable SqTable::subtable(int idx, int _length){
	return SqTable(&ptr[idx], _length);
}

void SqTable::enlarge(int enlargeNum = 32){
	int * newPtr = new int[arraySize + enlargeNum];
	arraySize = arraySize + enlargeNum;
	memcpy(newPtr, ptr, sizeof(int) * length);
	if (ptr != nullptr) delete[] ptr;
	ptr = newPtr;
}

//在顺序表末尾插入元素
void SqTable::push_back(const int & element){
	if (length >= arraySize) enlarge();
	ptr[length++] = element;
	order = 0; //在末尾插入元素可能会导致有序变为无序, 而push()内部将会做维护
}

void SqTable::sort(){
	std::sort(ptr, ptr+length);
	order = 1;
}

int SqTable::size() { return length; }

void SqTable::deduplication() {
	int k, i;
	if (length == 0) return;
	if (order == 1) { //对于顺序(递增)有序表
		//这里是一种O(n)的做法; 思想: 和删除所有值为e的元素思想类似 -- 挑选需要的元素进入"篮子"
		k = 1, i = 1; //用两个变量，k指向当前位置，i用来指向要移动的数据
		//i初始值设为1省去while循环里面if语句的一个防止越界访问的判断条件
		while (i < length) { //length - 1防止越界访问
			if (ptr[i] != ptr[i-1]) {
				//如果元素和后一位置不等，说明是(重复)元素的最后一个，则执行"搬运"
				if (i != k) ptr[k] = ptr[i];
				++k;
			}
			++i;
		}
		length = k; //记得更新表的长度！(还要考虑k没有变更过的情况……)
		//还可以优化，当重复数据比较繁多时，可以用二分查找找连续相同元素的边界
	}
	else if (order == 0) { //对于无序顺序表的做法
		k = 1, i = k; //k指向要写入的位置，i用来遍历顺序表
		while (i < length) { 
			bool isExist = false;
			for (int j = 0; j < k; j++) { //在idx: k之前找是否存在相同元素
				if (ptr[j] == ptr[i]) { isExist = true; break; }
			}
			if (!isExist) { //若不存在相同元素
				if (k != i) ptr[k] = ptr[i]; //有时候k, i的值是一样的，这时这样的赋值操作没有意义
				++k;
			}
			++i;
		}
		length = k;
	}
}

void SqTable::print() {
	for (int i = 0; i < length; ++i) std::cout << ptr[i] << ' ';
	std::cout << std::endl;
}
	
int SqTable::get_element(int idx, bool * ifSuccess) {
	if (idx < 0 || idx > length) {
		if (ifSuccess != nullptr) *ifSuccess = false;
		return -1;
	} else {
		if (ifSuccess != nullptr) *ifSuccess = false;
		return ptr[idx];
	}
}

int SqTable::sequential_search(int target){
	int t = 0;
	while (t < length) {
		if (ptr[t] == target) return t;
		++t;
	}
	return -1;
}

int SqTable::binary_search(int target, int * tgt_idx){
	int x = 0, y = length - 1; //注意右端点y的初始值
	while (x <= y)
	{
		int mid = (x+y)/2;
		//int mid = x + (y - x) >> 1; //防止溢出的写法
		if (ptr[mid] == target) {
			if (tgt_idx != nullptr) *tgt_idx = mid;
			return mid;
		}
		else if (ptr[mid] < target) x = mid + 1;
		else y = mid - 1;
	}
	//若没有找到target，则target应在ptr[y]和ptr[x]之间
	if (tgt_idx != nullptr) *tgt_idx = x; //返回元素应该在的位置的idx
	return -1;
}

//查找target第一次出现的位置
int SqTable::binary_find_first_of(int target, int * tgt_idx) {
	int x = 0, y = length - 1, mid; //注意右端点y的初始值
	while (x <= y)
	{
		mid = (x + y) / 2;
		if (ptr[mid] < target) x = mid + 1;
		else y = mid - 1; //ptr[mid] == target时不return, 继续缩小右边界
		//直到 y == x-1 时终止
	} 
	//如果没有找到target, 则target应在x-1和x之间的位置
	if (tgt_idx != nullptr) *tgt_idx = x; //返回元素应该在的位置的idx
	if (ptr[x] == target) return x; //这里也有点讲究，要考虑到会不会导致越界访问
	else return -1;
}

//查找target最后一次出现的位置
int SqTable::binary_find_last_of(int target, int * tgt_idx) {
	int x = 0, y = length - 1, mid; //注意右端点y的初始值
	while (x <= y) {
		mid = (x + y) / 2;
		if (ptr[mid] <= target) x = mid + 1;
		else y = mid - 1;
	}
	//如果没有找到target, 则target应在y和y+1(或者说x)之间的位置
	//返回元素应该在的位置的idx
	if (ptr[y] == target) {
		if (tgt_idx != nullptr) *tgt_idx = y;
		return y; //这里也有点讲究，要考虑到会不会导致越界访问
	}
	else {
		if (tgt_idx != nullptr) *tgt_idx = y + 1;
		return -1;
	}
}

//返回查找目标的下标, -1表示未查找到
int SqTable::find(int target) {
	if (order == 1) {
		if (target < ptr[0] || target > ptr[length - 1]) return -1; 
		else return binary_find_first_of(target);
		//return binary_search(target);
	}
	else return sequential_search(target);
}

//修改值为 target 的元素为 new_value
bool SqTable::edit_element(int target, int new_value) {
	if (new_value == target) return true;
	//基本思想很简单；
	//对于无序顺序表：找到target，修改它
	//对于有序顺序表：找到target，删除它，再插入新的数值
	//考虑到可能有重复出现的数据，可用循环重复上述过程
	int idx = -1;
	if (order == 0) {
		bool if_found = false;
		for (int i = 0; i < length; ++i) { //时间复杂度O(n); 思想: 遍历
			if (ptr[i] == target) { ptr[i] = new_value; if_found = true;}
		}
		return if_found;
	}
	//对于无序的顺序表，可以，或者说只能这样做，
	else if (order == 1) {
		/*while ((idx = find(target)) != -1) {
			remove(idx);
			insert(target);
		}*/
	//但对于有序顺序表这样的方法可能会造成很多不必要的数据移动，造成效率下降
	//一个解决方法是，判断是否是可以直接修改的情况，即新数据放在原位置上是否仍然有序
		/*while ((idx = find(target)) != -1) { //找到了值相等的元素
			//位于端点的下标需要特殊判断，即：
			if (idx == 0 && new_value <= ptr[idx+1]) ptr[idx] = new_value; 
			else if (idx > 0 && new_value >= ptr[idx-1] && idx < length - 1 && new_value <= ptr[idx +1]) ptr[idx] = new_value; 
			else if (idx == length && new_value >= ptr[idx-1]) ptr[idx] = new_value; 
			else { remove(idx); insert(new_value) };
		}*/
	//但这样的方法还是不够优秀：感觉如果这样还不如先统一修改、再统一排序：
		/*while ((idx = find(target)) != -1) ptr[idx] = new_value;
		sort(); */
	//感觉如果选用了合适的排序算法，"统一修改再排序"的效率还是很高的
	//所以在想，能不能先找到要排序的元素，判断它将要插入的空间，
	//然后只移动两个位置之间的元素，提高效率
	//而对于重复元素的情况，可以确定出元素的区间，以及待插入的位置，并计算要移动的数据的区间
	//为了用上二分查找，憨憨的我花了很多功夫整明白了二分查找找第一个或最后一个出现的元素的写法
	//整出来 binary_find_first_of() 和 binary_find_last_of() 两个函数. 然后就终于可以开始了
		int t_left, t_right; //目标元素的左右区间下标
		if ((t_left = find(target)) == -1) return false; //不存在这样的元素直接返回; find()里面集成了特判
		else t_right = binary_find_last_of(target); 
		//因为涉及到查找不到元素的情况
		int aim_idx = -1;
		if (new_value < target) { //需要讨论新值和target的大小关系
			//修改要移动元素的闭区间的端点
			if (binary_find_last_of(new_value, &aim_idx) != -1) { ++aim_idx;}
			//将 [aim_idx, t_left - 1] 的元素移动到 [, t_right]去
			int j = t_right;
			for (int k = t_left - 1; k >= aim_idx; --j, --k) {
				ptr[j] = ptr[k];
			}
			//完成操作后j的位置在移动好的区间的左边的位置
			for (int i = aim_idx; i <= j; ++i) ptr[i] = new_value;
		}
		else { //target < new_value
			//和上一个情况不一样，这里无论如何都要前移一位
			binary_find_first_of(new_value, &aim_idx);
			--aim_idx;
			//将 [t_right + 1, aim_idx] 的元素移动到 [t_left, ]去
			int j = t_left;
			for (int k = t_right + 1; k <= aim_idx; ++j, ++k) {
				ptr[j] = ptr[k];
			}
			//完成操作后j的位置在移动好的区间的右边的位置
			for (int i = j; i <= aim_idx; ++i) ptr[i] = new_value;
		}
		return true;
	}
	return false;
}
	
int & SqTable::operator[] (int idx) {
	order = 0;
	if (idx > length - 1) {
		if (idx < arraySize - 1) {length = idx; return ptr[idx];}
		else return ptr[0];
	}
	else if (idx < 0) return ptr[0];
	else return ptr[idx];
}

//在下标为idx的位置插入新的元素
void SqTable::insert(int idx, int target){
	if (idx > length || idx < 0) return; 
	//处理越界访问，注意idx > length 而不是 length-1 是为了能够插入在最后一个元素的后边；
	if (length >= arraySize) enlarge(); //如果大小不够，扩增数组大小
	for (int i = length; i > idx; --i) ptr[i] = ptr[i-1]; //注意i的起点和终点
	ptr[idx] = target;
	++length;
}

//将一个元素加入到顺序表中
void SqTable::push(int target)
{
	if (order == 0) push_back(target); //对于无序表直接push_back
	else if (order == 1) {
		//还是先进行两个特判：
		if (target < ptr[0]) insert(0,target);
		if (target > ptr[length - 1]) push_back(target);
		//使用二分查找找到元素位置
		//考虑到有重复元素，尽可能在连续区间的后面插入，以减少元素挪动，提高效率
		//因为涉及到查找不到元素的情况
		int aim_idx = -1;
		if (binary_find_last_of(target, &aim_idx) == -1) {
			//std::cout << aim_idx << std::endl; 
			insert(aim_idx,target);
		} else { //如果找到了target的最后出现位置
			//std::cout << aim_idx << std::endl; 
			insert(aim_idx + 1, target);
		}
	}
	//不能再++length了
}

void SqTable::erase(int idx) {
	if (idx < 0 || idx > length - 1) return;
	for (int i = idx; i < length - 1; ++i) ptr[i] = ptr[i + 1];
	--length;
}

//删除顺序表L中所有值为e的元素
bool SqTable::erase_element(int target) {
	if (order == 1) {
		int t_left, t_right;
		//使用二分法快速查找到顺序表中元素的左右边界
		//相比于顺序表采用的复杂度为O(n)的算法仅优化掉查找元素边界的过程
		if ((t_left = find(target)) == -1) return false; //找不到元素直接返回; find()集成了特判
		t_right = binary_find_last_of(target);
		if (t_right == length - 1) length = t_left; //如果元素在顺序表末尾了，直接截断
		else {
			while (t_right < length) ptr[t_left++] = ptr[++t_right];
			length -= (t_right - t_left + 1); 
		}
		return true;
	}
	else {
		int aim_idx;
		bool if_found = false;
		/*while ((aim_idx = find(target)) != -1) { //时间复杂度O(n^2)
			if_found = true;
			erase(aim_idx); //erase()方法会--length，因此这里不需要再--length了
		}*/
		int i = 0, k = 0;
		while(i < length) { //复杂度为O(n)的算法; 思想: 挑选需要的东西进"篮子"里
			if (ptr[i] == target) { if_found = true; ++i; continue;}
			else { 
				if (k != i) ptr[k] = ptr[i];
				++k; ++i;
			}
		}
		length = k;
		return if_found;
	}
}