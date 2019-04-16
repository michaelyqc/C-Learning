/*
 * brief : test standard thread lib's function "sleep_for, detach"
 *
 * result : if main thread exit
 */

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;



// other thread sleep function
void detach_thread() 
{
    std::cout << "detach_thread exit!" << std::endl;
}



int main(int argc, char* argv[])
{
    // main thread sleep function
    std::cout << "main thread sleep 5 seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); 

    std::cout << "create a detach thread" << std::endl;
    std::thread detach(detach_thread);
    detach.detach();
    // detach.join();

    std::cout << "sleep 5 seconds wait detach thread executed" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(5)); 

    return 0;
}
