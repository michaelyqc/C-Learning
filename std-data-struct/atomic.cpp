#include <iostream>   // std::cout
#include <atomic>     // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT 
#include <thread>     // std::thread, std::this_thread::yield
#include <vector>     // std::vector

using namespace std;

// global variable
std::atomic<bool> ready(false);    // can be checked without being set
std::atomic_flag winner = ATOMIC_FLAG_INIT;    // always set when checked

void count(int id)
{ 
    // 等待主线程中设置 ready 为 true.
    while (!ready) {
        // 主动让出 cpu 给系统中等待 cpu 运行的线程
        std::this_thread::yield();
    }

    // 计数
    for (int i = 0; i < 1000000; ++i) {
        // no operation
    } 

    // 如果某个线程率先执行完上面的计数过程，则输出自己的 ID.
    // 此后其他线程执行 test_and_set 是 if 语句判断为 false，
    // 因此不会输出自身 ID.
    if (!winner.test_and_set()) {
        std::cout << "thread #" << id << " won!\n";
    }
};

int main()
{
    std::vector<std::thread> threads;
    std::cout << "spawning 10 threads that count to 1 million...\n";
    for (int i = 1; i <= 10; ++i)
        threads.push_back(std::thread(count, i));

    ready = true;
    for (auto& th : threads)
        th.join();

    return 0;
}
















