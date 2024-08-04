#include<iostream>
#include<mutex>
using namespace std;

/*
        单例模式：一个类不管创建多少次对象，永远只能得到该类型一个对象的实例
        常用到的，比如日志模块，比如有很多模块都用到日志模块，但是只有一个对象就够了（占用内存）
        数据库模块

        单例模式：
        饿汉式单例模式：还没有获取实例对象，实例对象就已经产生了
        懒汉式单例模式：唯一的实例对象，直到第一次获取的时候才产生

        饿汉式不好的地方：构造函数里可能有很多逻辑，业务中可能没有获取唯一的实例
*/

// 懒汉式单例模式
class Singleton {
public:
        static Singleton* getInstance() {        // #3 获取类的唯一实例对象的接口方法
                // linux ：g++ -o run 单例模式.cpp -g  gdb run
                // 函数静态局部变量的初始化，在汇编指令上已经自动添加线程互拆指令了
                static Singleton instance;        //#2 定义一个唯一的类的实例对象
                return &instance;
        }
private:
        Singleton() {        // #1 构造函数私有化

        }
        Singleton(const Singleton& other) = delete;
        Singleton& operator=(const Singleton& other) = delete;
};


int main() {
        Singleton* p1 = Singleton::getInstance();
        Singleton* p2 = Singleton::getInstance();
        Singleton* p3 = Singleton::getInstance();
        cout << p1 << endl;

}


#if 0
// 线程安全的懒汉式单例模式
mutex mtx;

// 懒汉式单例模式 ==》  是不是线程安全的呢？（是）
class Singleton {
public:
        // 是不是可重入函数呢？（函数还没执行完就又被调用一次）        锁加双层判断
        static Singleton* getInstance() {        // #3 获取类的唯一实例对象的接口方法
                //lock_guard<mutex> guard(mtx);        // 锁的粒度太大
                if (instance == nullptr) {
                        lock_guard<mutex> guard(mtx);
                        /*
                                开辟内存                开辟内存
                                构造对象                返回对象
                                返回对象                构造对象
                        */
                        if (instance == nullptr) {
                                instance = new Singleton();
                        }
                }
                return instance;
        }
// volatile的作用是为了加快指令，把共享的数据拷贝到线程的缓冲区中
// 加这个关键字不缓存这个变量一旦instance改变
private:
        static Singleton *volatile instance;        //#2 定义一个唯一的类的实例对象
        Singleton() {        // #1 构造函数私有化

        }
        Singleton(const Singleton& other) = delete;
        Singleton& operator=(const Singleton& other) = delete;
};

Singleton*volatile Singleton::instance = nullptr;        //静态区的数据段，在主函数开始之前就已经创建

int main() {
        Singleton* p1 = Singleton::getInstance();
        Singleton* p2 = Singleton::getInstance();
        Singleton* p3 = Singleton::getInstance();
        cout << p1 << endl;

}
#endif

#if 0
// 饿汉式的单例                一定是线程安全的
class Singleton {
public:
        static Singleton* getInstance() {        // #3 获取类的唯一实例对象的接口方法
                return &instance;
        }
private:
        static Singleton instance;        //#2 定义一个唯一的类的实例对象
        Singleton() {        // #1 构造函数私有化

        }
        Singleton(const Singleton& other) = delete;
        Singleton& operator=(const Singleton& other) = delete;
};

Singleton Singleton::instance;        //静态区的数据段，在主函数开始之前就已经创建

int main(){
        Singleton* p1 = Singleton::getInstance();
        Singleton* p2 = Singleton::getInstance();
        Singleton* p3 = Singleton::getInstance();
        cout << p1 << endl;

}
#endif
