#include<iostream>

using namespace std;

/*
        类模板：
*/

template<typename T>
class SeqStack {        // 模板名称  + 类型参数列表 =》类名称
public:
        // 构造和析构函数名不用加<T>，其他出现模板的地方都加上类型参数列表
        SeqStack<T>(int size = 10) : _pstack(new T[size]), _top(0), _size(size) {}
        ~SeqStack<T>() {
                delete[]_pstack;
                _pstack = nullptr;
        }
        SeqStack<T>(const SeqStack<T>& stack):_top(stack._top),_size(stack._size) {
                _pstack = new T[_size];
                for (int i = 0; i < _top; i++) {
                        _pstack[i] = stack._pstack[i];
                }
        }
        SeqStack<T>& operator=(const SeqStack<T>&stack) {
                if (this == &stack) {
                        return *this;
                }
                delete[] _pstack;

                _top = stack._top;
                _size = stack._size;
                _pstack = new T[_size];
                for (int i = 0; i < _top; i++) {
                        _pstack[i] = stack._pstack[i];
                }
                return *this;
        }

        void push(const T&val) {
                if (full()) {
                        expand();
                }
                _pstack[_top++] = val;
        }
        void pop() {
                if (empty()) {
                        return;
                }
                --_top;
        }
        T top()const {
                return _pstack[_top - 1];
        }
        bool full()const {
                return _top == _size;
        }
        bool empty()const {
                return _top == 0;
        }
private:
        T *_pstack;
        int _top;
        int _size;

        // 顺序栈底层数组按2倍的方式扩容
        void expand() {
                T* ptmp = new T[2*_size];
                for (int i = 0; i < _top; i++) {
                        ptmp[i] = _pstack[i];
                }
                delete[]_pstack;
                _pstack = ptmp;
                _size *= 2;
        }
};

int main() {
        SeqStack<int> s1;
        s1.push(1);
        s1.push(3);
        s1.push(7);
        s1.pop();
        cout << s1.top() << endl;
        return 0;
}
