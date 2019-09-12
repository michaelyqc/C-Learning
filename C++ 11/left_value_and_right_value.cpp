/*
 * author : yangqichao
 * date : 2019/08/08
 * brief : test C++ 11 left value, right value, reference and reference
 */


#include <iostream>
#include <typeinfo>
#include <string>


int main (int argc, char* argv[]) {
    int tmp = 110;
    // int && dest = std::move(tmp);
    // int dest = std::move(tmp);
    int dest(std::move(tmp));
    int* ptr1 = &tmp;
    // int* && ptr2 = std::move(ptr1);
    int* ptr2 = std::move(ptr1);
    
    std::cout<< "ptr1 = " << ptr1 << std::endl;
    std::cout<< "ptr2 = " << ptr2 << std::endl;
    
    
    // check value
    std::cout<< "tmp = " << tmp << std::endl;
    std::cout<< "dest = " << dest << std::endl;
    
    // check value address
    std::cout<< "&tmp = " << &tmp << std::endl;
    std::cout<< "&dest = " << &dest << std::endl;
    
    // check value address
    std::cout<< "type(tmp) = " << typeid(tmp).name() << std::endl;
    std::cout<< "type(dest) = " << typeid(dest).name() << std::endl;
    
    std::string str1 = "hello world!";
    std::string && str2 = std::move(str1);
    std::string && str3 = static_cast<std::string &&>(str1);
    // std::string str4(std::move(str1));
    std::string str4 = std::move(str1);
    
    std::cout<< "&str1 = " << &str1 << std::endl;
    std::cout<< "&str2 = " << &str2 << std::endl;
    std::cout<< "&str3 = " << &str3 << std::endl;
    std::cout<< "&str4 = " << &str4 << std::endl;
    
    std::cout<< "str1 = " << str1 << std::endl;
    std::cout<< "str2 = " << str2 << std::endl;
    std::cout<< "str3 = " << str3 << std::endl;
    std::cout<< "str4 = " << str4 << std::endl;
    
    return 0;
}
