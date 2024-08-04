#include<iostream>
#include<memory>

using namespace std;

/*
        代理proxy模式：通过代理类，来控制实际对象的访问权限
        客户     助理proxy                老板 委托类
        代理类和委托类都继承一个基类（利用多态）
*/

class VideoSite {
public:
        virtual void freeMovie() = 0;
        virtual void vipMovie() = 0;
        virtual void ticketMovie() = 0;
};

class FixBugVideoSite:public VideoSite {        //委托类
public:
        virtual void freeMovie() {
                cout << "免费电影" << endl;
        }
        virtual void vipMovie() {
                cout << "VIP电影" << endl;
        }
        virtual void ticketMovie() {
                cout << "券电影" << endl;
        }
};

// 代理类   代理FixBugVideoSite
class FreeVideoSiteProxy :public VideoSite {
public:
        FreeVideoSiteProxy() {
                pvideo = new FixBugVideoSite();
        }
        ~FreeVideoSiteProxy()
        {
                delete pvideo;
        }
        virtual void freeMovie() {
                pvideo->freeMovie();        // 通过代理对象的freeMovie，来访问真正的委托类对象的freeMovie
                //pvideo.freeMovie();
        }
        virtual void vipMovie() {
                cout << "需要购买VIP" << endl;
        }
        virtual void ticketMovie() {
                cout << "需要购买券" << endl;
        }
private:
        VideoSite* pvideo;
        // FixBugVideoSite* pvideo = new FixBugVideoSite();
        ///FixBugVideoSite pvideo;
};

// 代理类   代理FixBugVideoSite
class VIPVideoSiteProxy :public VideoSite {
public:
        VIPVideoSiteProxy() {
                pvideo = new FixBugVideoSite();
        }
        ~VIPVideoSiteProxy()
        {
                delete pvideo;
        }
        virtual void freeMovie() {
                pvideo->freeMovie();        // 通过代理对象的freeMovie，来访问真正的委托类对象的freeMovie
        }
        virtual void vipMovie() {
                pvideo->vipMovie();
        }
        virtual void ticketMovie() {
                cout << "需要购买券" << endl;
        }
private:
        VideoSite* pvideo;
};

int main() {
        VideoSite* v1 = new FreeVideoSiteProxy();
        v1->freeMovie();
        v1->vipMovie();
        v1->ticketMovie();

        cout << endl;

        unique_ptr<VideoSite> v2(new VIPVideoSiteProxy());
        v2->freeMovie();
        v2->vipMovie();
        v2->ticketMovie();

        return 0;
}
