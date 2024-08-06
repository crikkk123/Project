#include <iostream>
#include <vector>

using namespace std;

/*
        函数模板
        模板的意义：对类型进行参数化了

        函数模板：不进行编译（类型不知道），没实例化之前是函数模板，实例化后是模板函数
        模板的实例化：编译器根据传入的参数类型进行生成模板函数（函数调用点进行实例化）
        模板函数：        被编译器所编译

        模板的类型参数：typename/class
        模板的非类型参数： 都是常量，只能使用，不能修改（必须是整数类型，整数或者地址）

        模板的实参推演：  =》可以根据用户传入的实参的类型，推导出模板参数的具体类型
        模板的特例化（专用化）：特殊（不是编译器提供的，而是开发者提供的）的实例化
        函数模板、模板的特例化、非模板函数的重载关系

        模板代码是不能再一个文件中定义，在另一个文件中使用
        模板代码调用之前，一定要看到模板定义的地方，这样的话模板才能够进行正常的实例化，产生能够被编译器编译的代码

        所以，模板代码都是放在头文件中，然后在源文件中直接#include包含
*/

// 函数模板
template<typename T>        //定义一个模板的参数列表
bool compare(T a, T b) {
        cout << "template compare" << endl;
        return a > b;
}

/*
在函数调用点，编译器用用户指定的类型，从原模板实例化一份函数代码出来
模板函数：
bool compare<int>(int a,int b){
        return a>b;
}

bool compare<double>(double a,double b){
        return a>b;
}

bool compare<const char*>(const char* a,const char* b){
        return a>b;
        // return strcmp(a,b)>0;
}
*/

// 针对compare函数模板，提供const char*类型的特例化版本
template<>
bool compare<const char*>(const char*a,const char* b) {
        cout << "compare(const char*)" << endl;
        return strcmp(a, b) > 0;
}

bool compare(const char* a, const char* b) {
        cout << "normal compare(const char*)" << endl;
        return strcmp(a, b) > 0;
}

template<typename T,int SIZE>
void BubbleSort(T* arr) {
        for (int i = 1; i < SIZE; i++) {
                for (int j = 0; j < SIZE - i; j++) {
                        if (arr[j] > arr[j + 1]) {
                                swap(arr[i], arr[j + 1]);
                        }
                }
        }
}

int main() {
        // 函数的调用点（实例化）
        compare<int>(10, 20);        // 模板名加参数列表才是函数，否则只是函数的模板（函数模板）
        compare<double>(10.0, 20.0);

        // 函数模板实参推演
        compare(10, 20);

        // 函数模板实参推演  T const char*
        // 对于某些类型来说，依赖编译器默认实例化的模板代码，代码的处理逻辑是不对的
        // 编译器优先把compare处理成函数名字，没有的话才去找compare模板 
        compare("aaa", "bbb");
        compare<const char*>("aaa", "bbb");

        int arr[] = { 8,34,14,6,2,76 };
        const int size = sizeof(arr) / sizeof(arr[0]);
        BubbleSort<int, size>(arr);           //模板的非类型参数
        for (auto it : arr) {
                cout << it << "  ";
        }
        cout << endl;
        return 0;
}
