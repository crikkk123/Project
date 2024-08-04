#include<iostream>
#include<memory>

using namespace std;

/*
        适配器模式：让不兼容的接口可以在一起工作
        电脑  ==》投影到   ==》投影仪上  VGA   HDMI   TypeC

        VGA接口的电脑，（TV）投影仪也是VGA接口
*/

class VGA {
public:
        virtual void play() = 0;
};

// 进了一批新的投影仪，但是新的投影仪都只支持HDMI接口
class HDMI {
public:
        virtual void play() = 0;
};

// TV01表示支持VGA接口的投影仪
class TV01:public VGA {
public:
        void play() {
                cout << "通过VGA接口投影" << endl;
        }
};

class TV02 :public HDMI {
public:
        void play() {
                cout << "通过HDMI接口投影" << endl;
        }
};

//实现一个电脑类(只支持VGA接口)
class computer {
public:
        // 由于电脑只支持VGA接口，所以该方法的参数也只能支持VGA接口的指针/引用
        void playvideo(VGA* pvga) {
                pvga->play();
        }
};

/*
        方法1：换一个支持HDMI接口的电脑，这个叫代码重构
        方法2:买一个转接头（适配器），能够把VGA信号转成HDMI信号，这个叫添加适配器类
*/

// 由于电脑(VGA接口)和投影仪(HDMI接口)无法直接相连，所以需要添加适配器类
class VGATOHDMIAdapter :public VGA{
public:
        VGATOHDMIAdapter(HDMI* p) :pHdmi(p) {

        }
        void play() {        // 该方法相当于就是转换头，做不同接口的信号转换的
                pHdmi->play();
        }
private:
        HDMI *pHdmi;
};

int main() {
        computer a;
        a.playvideo(new TV01());
        a.playvideo(new VGATOHDMIAdapter(new TV02()));
        return 0;
}
