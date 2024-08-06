#include<iostream>
#include<vector>
using namespace std;

/*
	类模板：=》实现一个C++  STL里面的一个顺序容器  vector  向量容器
	容器：
	allocator空间配置器
*/

// 定义容器的空间配置器，和C++标准库的allocator实现一样
template<typename T>
class Allocator {
public:
	T* allocate(size_t size) {		//负责内存开辟
		return (T*)malloc(sizeof(T)*size);
	}
	void deallocate(void* p) {		// 负责内存释放
		free(p);
	}
	void construct(T* p, const T& val) {	// 负责对象构造
		new(p) T(val);		// 在指定内存上构造   定位new
	}
	void destory(T* p) {	// 负责对象析构
		p->~T();
	}
};


// 容器底层内存开辟，内存释放，对象的构造和析构，都通过allocator空间配置器来实现
template<typename T, typename Alloc = Allocator<T>>
class Seqvector {
public:
	// 需要把内存开辟和对象的构造分开处理
	Seqvector(int size = 10, const Alloc& alloc = Allocator<T>()):allocator_(alloc){
		//first_ = new T[size];   // 需要把内存的开辟和对象的构造分开处理
		first_ = allocator_.allocate(size);
		last_ = first_;
		end_ = first_ + size;
	}

	~Seqvector()
	{
		// 析构容器有效的元素，然后释放first_指针指向的堆内存
		// delete[] first_;
		for (T* p = first_; p != last_; ++p) {
			allocator_.destory(p);	// 把first_指针指向的数组的有效元素进行析构操作
		}
		allocator_.deallocate(first_);	// 释放堆上的数组内存
		first_ = last_ = end_ = nullptr;
	}

	Seqvector(const Seqvector<T>& other) {
		int size = other.end_ - other.first_;
		// first_ = new T[size];
		first_ = allocator_.allocate(size);
		int len = other.last_ - other.first_;
		for (int i = 0; i < len; i++) {
			//first_[i] = other.first_[i];
			allocator_.construct(first_+i,other.first_[i]);
		}
		last_ = first_+len;
		end_ = first_ + size;
	}

	Seqvector<T> operator=(const Seqvector<T>& other) {
		if (this == &other) {
			return *this;
		}
		//delete[] first_;
		for (T* p = first_; p != last_; ++p) {
			allocator_.destory(p);
		}
		allocator_.deallocate(first_);

		/*int size = other.end_ - other.first_;
		first_ = new T[size];
		int len = other.last_ - other.first_;
		for (int i = 0; i < len; i++) {
			first_[i] = other.first_[i];
		}
		last_ = first_ + len;
		end_ = first_ + size;*/

		int size = other.end_ - other.first_;
		first_ = allocator_.allocate(size);
		int len = other.last_ - other.first_;
		for (int i = 0; i < len; i++) {
			allocator_.construct(first_ + i, other.first_[i]);
		}
		last_ = first_ + len;
		end_ = first_ + size;
		return *this;
	}

	void push_back(const T& val) {	// 向容器末尾添加元素
		if (full()) {
			expand();
		}
		//*last_++ = val;
		allocator_.construct(last_, val);
		last_++;
	}

	void pop_back() {		// 从容器末尾删除元素
		if (empty()) {
			return;
		}
		//--last_;
		--last_;
		allocator_.destory(last_);
	}

	T back() const { return *(last_-1); }   // 返回元素末尾的值

	bool full() const { return last_ == end_; }

	bool empty() const { return first_ == last_; }

	int sizenum() const { return last_ - first_; }
private:
	T* first_;   // 指向第一个元素的位置
	T* last_;	 // 指向有效元素最后一个元素的后继位置
	T* end_;	 // 指向最后一个元素的后继位置
	Alloc allocator_;	// 定义容器的空间配置器对象

	void expand() {		// 容器的二倍扩容
		int size1 = end_ - first_;
		//T* temp = new T[2*size1];
		T* temp = allocator_.allocate(2 * size1);

		for (int i = 0; i < size1; i++) {
			//temp[i] = first_[i];
			allocator_.construct(temp+i,first_[i]);
		}

		//delete[] first_;
		for (T* p = first_; p != last_; ++p) {
			allocator_.destory(p);
		}
		allocator_.deallocate(first_);
		first_ = temp;
		last_ = first_ + size1;
		end_ = first_ + 2 * size1;
	}
};

class Test {
public:
	Test() {
		cout << " Test() " << endl;
	}
	~Test() {
		cout << " ~Test() " << endl;
	}
	Test(const Test& other) {
		cout << "Test(const Test&)" << endl;
	}
};

int main() {
	//Seqvector<int> vec;
	//for (int i = 0; i < 20; i++) {
	//	vec.push_back(i);
	//}
	//vec.pop_back();
	//while (!vec.empty()) {
	//	cout << vec.back() << "  ";
	//	vec.pop_back();
	//}

	//Test t1, t2, t3;
	//cout << "----------------------------" << endl;
	//Seqvector<Test> nums;		// 这时调用了十次构造与析构
	//nums.push_back(t1);
	//nums.push_back(t2);
	//nums.push_back(t3);
	//cout << "----------------------------" << endl;
	//nums.pop_back();
	//cout << "----------------------------" << endl;

	Test t1, t2, t3;
	cout << "----------------------------" << endl;
	Seqvector<Test> nums;
	nums.push_back(t1);
	nums.push_back(t2);
	nums.push_back(t3);
	cout << "----------------------------" << endl;
	nums.pop_back();
	cout << "----------------------------" << endl;

	return 0;
}

