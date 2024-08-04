#include<iostream>
#include<unordered_map>
#include<list>

using namespace std;

/*
    行为型模式：主要关注的是对象之间的通信
        观察者-监听者（发布-订阅模式）设计模式：主要关注的是对象的一对多的关系，也就是多个对象都依赖一个对象
        当该对象的状态发生改变时，其他对象都能够接收到相应的通知

        一组数据（数据对象）  ==》通过这一组数据  ==》曲线图（对象1）/柱状图（对象2）/元饼图（对象3）
        当数据对象改变时，对象1、2、3应该计时的收到相应的通知

        Observer1     Observer2      Observer3
                        subject(主题) 主题有更改，应该及时通知相应的观察者，去处理相应的事件
*/

// 观察者抽象类
class Observer {
public:
        // 处理消息的接口
        virtual void handle(int msg) = 0;
};

class Observer1 :public Observer {
public:
        void handle(int msg) {
                switch (msg)
                {
                case 1:
                        cout << "Observer1 receive 1 msg!" << endl;
                        break;
                case 2:
                        cout << "Observer1 receive 2 msg!" << endl;
                        break;
                case 3:
                        cout << "Observer1 receive 3 msg!" << endl;
                        break;
                default:
                        break;
                }
        }
};

class Observer2 :public Observer {
public:
        void handle(int msg) {
                switch (msg)
                {
                case 1:
                        cout << "Observer2 receive 1 msg!" << endl;
                        break;
                case 3:
                        cout << "Observer2 receive 3 msg!" << endl;
                        break;
                default:
                        break;
                }
        }
};

class Observer3 :public Observer {
public:
        void handle(int msg) {
                switch (msg)
                {
                case 2:
                        cout << "Observer3 receive 2 msg!" << endl;
                        break;
                default:
                        break;
                }
        }
};

// 主题类
class Subject {
public:
        // 给主题增加观察者对象
        void addObservermsg(int msg,Observer* p) {
                _submap[msg].push_back(p);
        }
        // 主题检测发生改变，通知相应的观察者对象处理事件
        void dispatch(int msg) {
                auto it = _submap.find(msg);
                if (it != _submap.end()) {
                        for (Observer* pobser : it->second) {
                                pobser->handle(msg);
                        }
                }
        }
private:
        unordered_map<int, list<Observer*>> _submap;
};

int main() {
        Subject sub;
        Observer1* p1 = new Observer1();
        Observer2* p2 = new Observer2();
        Observer3* p3 = new Observer3();
        sub.addObservermsg(1, p1);
        sub.addObservermsg(2, p1);
        sub.addObservermsg(3, p1);
        sub.addObservermsg(1, p2);
        sub.addObservermsg(3, p2);
        sub.addObservermsg(2, p3);
        for (;;) {
                int n;
                cin >> n;
                if (n == -1) {
                        return 0;
                }
                sub.dispatch(n);
        }
        return 0;
}
