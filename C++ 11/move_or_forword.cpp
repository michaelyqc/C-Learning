/*
 * author : yangqichao
 * date : 2019/08/14
 * brief : test C++ 11 std::move, std::forword
 */


#include <iostream>
#include <typeinfo>
#include <typeinfo>
#include <memory>
#include <string>


struct A
{
    A(int&& n)
    {
        std::cout << "rvalue overload, n=" << n << std::endl;
    }
    A(int& n)
    {
        std::cout << "lvalue overload, n=" << n << std::endl;
    }
};


class B
{
public:
    template<class T1, class T2, class T3>
    B(T1 && t1, T2 && t2, T3 && t3) :
        a1_(std::forward<T1>(t1)),
        a2_(std::forward<T2>(t2)),
        a3_(std::forward<T3>(t3))
    {

    }
private:
    A a1_, a2_, a3_;
};


template <class T, class U>
std::unique_ptr<T> make_unique1(U&& u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)));
    // return std::unique_ptr<T>(new T(std::move(u)));
}


template <class T, class... U>
std::unique_ptr<T> make_unique(U&&... u)
{
    return std::unique_ptr<T>(new T(std::forward<U>(u)...));
    // return std::unique_ptr<T>(new T(std::move(u)...));
}


int main (int argc, char* argv[]) {
    int i = 1;
    // std::cout << "decltype(i) = " << decltype(i).name() << std::endl;
    auto p1 = make_unique1<A>(1);
    
    int j = 10;
    auto p2 = make_unique1<A>(j);
    
    int k = 100;
    auto p3 = make_unique<B>(1, j, k);
    
    return 0;
}




