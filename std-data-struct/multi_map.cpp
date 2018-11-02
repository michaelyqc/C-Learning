#include <iostream>
#include <string>
#include <map>
#include <functional>
 
template<class M>
void print(const M& mmap)
{
    for (auto & e : mmap)
        std::cout << "{" << e.first << "," << e.second << "} ";
    std::cout << '\n';
}
 
int main()
{
    // 列表初始化
    std::multimap<int, std::string, std::greater<int>> mmap 
    {{2, "foo"}, {2, "bar"}, {3, "baz"}, {1, "abc"}, {5, "def"}};
 
    // 用 value_type 插入
    mmap.insert(decltype(mmap)::value_type(5, "pqr"));
    print(mmap);
   
    // 用 make_pair 插入
    mmap.insert(std::make_pair(6, "uvw"));
    print(mmap);
   
    mmap.insert({7, "xyz"});
    print(mmap);
   
    // 用 initialization_list 插入
    mmap.insert({{5, "one"}, {5, "two"}});
    print(mmap);

    for (auto iter = mmap.begin(); iter != mmap.end(); ++iter)
        std::cout << "{" << iter->first << "," << iter->second << "}" << std::endl;
   
    // 擦除所有关键为 5 的条目
    mmap.erase(5);
    print(mmap);
   
    // 寻找并擦除特定条目
    auto pos = mmap.begin();
    while (pos->second != "bar" && pos != mmap.end()) ++pos;
    mmap.erase(pos);
    print(mmap);
}
