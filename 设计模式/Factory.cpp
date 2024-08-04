#include<iostream>
#include<string>

using namespace std;

/*
        简单工厂 simple Factory        :
                        把对象的创建封装在一个接口函数里面，通过传入不同的标识，返回创建的对象
                        客户不用自己负责new对象，不用了解对象创建的详细过程
                        提供创建对象实例的接口函数不闭合，不能对修改关闭

        工厂方法：Factory Method
                          Factory基类，提供了一个纯虚函数（创建产品），定义派生类（具体产品的工厂）负责创建对应的产品
                          可以做到不同的产品在不同的工厂里面创建，能够对现有工厂，以及产品的修改关闭
                          实际上很多产品是有关联关系的，属于一个产品簇，不应该放在不同的工厂里面创建，这样一是不符合实际的
                          产品对象创建的逻辑，二是工厂类太多了！不好维护

        抽象工厂：Abstract Factory
                        把有关联关系的，属于一个产品簇的所有产品创建的接口函数，放在一个抽象工厂里面AbstractFactory
                        派生类（具体产品的工厂）应该负责创建该产品簇里面所有的产品

        工厂模式：主要是封装了对象的创建
*/


class Car {
public:
        Car(string name) :name_(name) {

        }
        virtual void show() = 0;
protected:
        string name_;
private:

};

class Bmw :public Car {
public:
        Bmw(string name) :Car(name) {

        }
        void show() {
                cout << "汽车：" << name_ << endl;
        }
};

class Audi :public Car {
public:
        Audi(string name) :Car(name) {

        }
        void show() {
                cout << "汽车：" << name_ << endl;
        }
};

class Light {
public:
        Light() {

        }
        virtual void show() = 0;
};

class BmwLight :public Light {
public:
        BmwLight() :Light() {

        }
        void show() {
                cout << "宝马车灯 " << endl;
        }
};

class AudiLight :public Light {
public:
        AudiLight() :Light() {

        }
        void show() {
                cout << "奥迪车灯 "  << endl;
        }
};

//工厂方法  ==>抽象工厂(对有一组关联关系的产品簇提供产品对象的统一创建)
//当某个工厂有自己特有的项目时，抽象工厂就不适用了（子类都成抽象类了）
class AbstractFactory {
public:
        virtual Car* createCar(string name) = 0;
        virtual Light* createCarLight() = 0;
};

class BMWFactory : public AbstractFactory {
public:
        Car* createCar(string name) {
                return new Bmw(name);
        }
        Light* createCarLight() {
                return new BmwLight();
        }
};

class AudiFactory :public AbstractFactory {
public:
        Car* createCar(string name) {
                return new Audi(name);
        }
        Light* createCarLight() {
                return new AudiLight();
        }
};

int main() {
        AbstractFactory* bmwfty = new BMWFactory();
        AbstractFactory* audifty = new AudiFactory();
        Car* p1 = bmwfty->createCar("宝马");
        Car* p2 = audifty->createCar("奥迪");
        Light* l1 = bmwfty->createCarLight();
        Light* l2 = audifty->createCarLight();

        p1->show();
        l1->show();

        p2->show();
        l2->show();
        return 0;
}


#if 0        
//工厂方法
class Car {
public:
        Car(string name) :name_(name) {

        }
        virtual void show() = 0;
protected:
        string name_;
private:

};

class Bmw:public Car {
public:
        Bmw(string name) :Car(name) {

        }
        void show() {
                cout << "汽车：" << name_ << endl;
        }
};

class Audi:public Car {
public:
        Audi(string name) :Car(name) {

        }
        void show() {
                cout << "汽车：" << name_ << endl;
        }
};

//工厂方法    （一个产品一个工厂  导致类太多了）
class Factory {
public:
        virtual Car* createCar(string name) = 0;
};

class BMWFactory : public Factory{
public:
        Car* createCar(string name) {
                return new Bmw(name);
        }
};

class AudiFactory :public Factory {
public:
        Car* createCar(string name) {
                return new Audi(name);
        }
};

int main() {
        BMWFactory* fc = new BMWFactory();
        fc->createCar("宝马");
        AudiFactory* fc1 = new AudiFactory();
        fc1->createCar("奥迪");
}

#endif

#if 0
// 简单工厂
enum CarType {
        BMW, AUDI
};
class SimpleFactory {
public:
        Car* createCar(CarType ct) {
                switch (ct)
                {
                case BMW:
                        return new Bmw("宝马");
                        break;
                case AUDI:
                        return new Bmw("奥迪");
                        break;
                default:
                        break;
                }
        }
};


int main() {
        //Car* p1 = new Bmw("宝马");
        //Car* p2 = new Audi("奥迪");
        //p1->show();
        //p2->show();

        SimpleFactory* sf = new SimpleFactory();
        Car* p3 = sf->createCar(BMW);
        Car* p4 = sf->createCar(AUDI);
        p3->show();
        p4->show();
        delete p3, p4, sf;

        return 0;
}
#endif
