#include<iostream>
#include<memory>

using namespace std;

/*
        装饰器模式：Decorator                增强类的功能
        通过子类实现功能增强的问题：为了增强现有类的功能，通过实现子类的方式，重写接口
        是可以完成扩展的，但是代码中有太多的子类添加进来了
*/

class Car {
public:
        virtual void show() = 0;
};

class Bmw : public Car {
public:
        void show() {
                cout << "宝马汽车: ";
        }
};

class Audi : public Car {
public:
        void show() {
                cout << "奥迪汽车: ";
        }
};

class Benz : public Car {
public:
        void show() {
                cout << "奔驰汽车: ";
        }
};

class conDecorator01 :public Car {
public:
        conDecorator01(Car* car):pcar(car){}
        void show() {
                pcar->show();
                cout << "自动驾驶 ";
        }
private:
        Car* pcar;
};

class conDecorator02 :public Car {
public:
        conDecorator02(Car* car) :pcar(car) {}
        void show() {
                pcar->show();
                cout << "自动刹车 ";
        }
private:
        Car* pcar;
};

class conDecorator03 :public Car {
public:
        conDecorator03(Car* car) :pcar(car) {}
        void show() {
                pcar->show();
                cout << "自动巡航 ";
        }
private:
        Car* pcar;
};


int main() {
        Car* p1 = new conDecorator03(new Bmw());
        p1 = new conDecorator01(p1);
        p1 = new conDecorator02(p1);
        p1->show();
        cout << endl;

        Car* p2 = new conDecorator02(new Audi());
        p2 = new conDecorator01(p2);
        p2->show();
        cout << endl;

        Car* p3 = new conDecorator01(new Benz());
        p3->show();
        cout << endl;

        return 0;
}
