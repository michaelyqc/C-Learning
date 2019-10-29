/*
 * lambda statement
 * capture parameter : null is allowed
 * input parameters : null is allowed
 * return type : null is allowed, compiler will infer according to return statement
 * code statement :
 * [ capture parameter ] ( input parameters ) mutable -> return type { code statement  }
 *
 * [] : 默认不捕获任何变量
 * [=] : 默认以值捕获所有变量
 * [&] : 默认以引用捕获所有变量
 * [x] : 仅以值捕获x, 其它变量不捕获
 * [&x] : 仅以引用捕获x, 其它变量不捕获
 * [=, &x] : 默认以值捕获所有变量, 但是x是例外, 通过引用捕获
 * [&, x] : 默认以引用捕获所有变量, 但是x是例外, 通过值捕获
 * [this] : 通过引用捕获当前对象（其实是复制指针）
 * [*this] : 通过传值方式捕获当前对象
 *
 */


#include <iostream>
#include <functional>


// using reference capture maybe point to suspend pointer
std::function<int(int)> add_x(int x)
{
  return [&](int a) { return x + a; };
  // return [=](int a) { return x + a; };
}

class Filter
{
  public:
    Filter(int divisorVal): divisor{divisorVal} {}

    std::function<bool(int)> getFilter() 
    {
      // return [this](int value) {return value % this->divisor == 0; };
      return [=](int value) {return value % divisor == 0; };
    }

    /* just this pointer is available to getFilter function
    std::function<bool(int)> getFilter() 
    {
      return [divisor](int value) {return value % divisor == 0; };
    }
     */

  private:
    int divisor;
};

int main(int argc, char* argv[]) {
  // most simple lambda statement
  auto most_simple_lambda = [] { std::cout << "most simple lambda statement" << std::endl; };
  most_simple_lambda();

  // most full lambda statement
  auto add_func = [] (int left, int right) -> int { return left + right; };
  std::cout << "add_func(1, 10) = " << add_func(1, 10) << std::endl;

  // no return type lambda statement
  auto multi_func = [] (int left, int right) { return left * right; };
  std::cout << "multi_func(1, 10) = " << multi_func(1, 10) << std::endl;

  // variable be used to capture
  int x = 10;
  
  /* 
   * default 
    class ClosureType
    {
      public:
        // ...
        ReturnType operator() (params) const { body };
    }
  * add mutable keyword
    class ClosureType
    {
    public:
    // ...
    ReturnType operator() (params) { body };
    }

    ClosureType& operator=(const ClosureType&) = delete;
  */

  // assignment capture
  // auto add_to = [x] (int y) -> int { return x + y; };
  auto add_to = [x] (int y) mutable -> int { return x += y; };
  std::cout << "add_to = " << add_to(10) << std::endl;
  std::cout << "after add_to x = " << x << std::endl;

  x = 10;
  // reference capture
  auto multi_to = [&x] (int y) -> int { return x *= y; };
  std::cout << "multi_to = " << multi_to(10) << std::endl;
  std::cout << "after multi_to x = " << x << std::endl;

  auto a = [] { std::cout << "A" << std::endl; };
  auto b = [] { std::cout << "B" << std::endl; };

  // a = b;   // 非法，lambda无法赋值
  auto c = a;   // 合法，生成一个副本

  auto pfunc = add_x(10);
  std::cout << "pfunc(10) = " << pfunc(10) << std::endl;

  return 0;
}
