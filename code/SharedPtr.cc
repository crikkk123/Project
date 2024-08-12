#include<iostream>

using namespace std;

template<typename T>
class Ref {
	int r_count = 0;
	T* object = nullptr;
public:
	Ref(T* target):object(target){
		r_count++;
	}

	// 引用计数加1
	void increase() {
		r_count++;
	}

	// 引用计数减1
	void reduce() {
		r_count--;
		if (r_count == 0)
		{
			delete object;
			delete this;
		}
	}

	T* get() {
		return object;
	}

	int get_Count() {
		return r_count;
	}
};

template<typename T>
class Share_ptr {
	Ref<T>* ref = nullptr;
public:
	Share_ptr(){}
	Share_ptr(T* other) {
		ref = new Ref<T>(other);
	}

	Share_ptr(const Share_ptr& other) {
		this->ref = other.ref;
		if (ref) {
			ref->increase();
		}
	}
};

int main() {

	return 0;
}
