/*
 * brief introduction of the function : try to use functor object
 * author : YangQiChao
 * date : 2019/09/09
 */


#include <iostream>
#include <thread>

class Hello {
  
public:
    void operator()(const char* what) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << what << std::endl;
    }

    Hello() {
        std::cout << "Class Hello construct function" << std::endl;
    }

    Hello(const Hello& hello) {
        std::cout << "Class Hello copy construct function" << std::endl;
    }
};


int main() {
    Hello hello;

    // 方式一：拷贝函数对象。
    // 发生两次拷贝构造，需要了解 std::thread 的定义
    std::thread t1(hello, "Hello World!");
    t1.join();

    // 方式二：不拷贝函数对象，通过 boost::ref 传入引用。
    // 用户必须保证被线程引用的函数对象，拥有超出线程的生命期。
    // 比如这里通过 join 线程保证了这一点。 
    std::thread t2(std::ref(hello), "Hello World!");
    t2.join();

    return 0;
}
