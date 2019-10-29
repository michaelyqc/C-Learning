#include <iostream>
#include <future>


// int () function prototype
int f() {
  string hello_world = "hello world!";
  std::cout << hello_world << std::endl;
  
  return hello_world.size();
}


int main() {
  // int () function prototype
  std::packaged_task<int ()> task(f);
  auto result = task.get_future();

  task();

  cout << result.get() << endl;

  return 0;
}
