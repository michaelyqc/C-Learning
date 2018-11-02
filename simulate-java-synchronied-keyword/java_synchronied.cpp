#include <iostream>
#include <boost/thread.hpp>

using namespace std;

#define synchronized(M)  for(Lock M##_lock = M; M##_lock; M##_lock.setUnlock())

boost::mutex global_mutex; 

// synchronization controller object
class Lock
{
  public:
    // the default constructor
    Lock(boost::mutex & mutex) : m_mutex(mutex), m_locked(true)
    {
      mutex.lock();
    }

    // the destructor
    ~Lock()
    {
      m_mutex.unlock();
    }

    // report the state of locking when used as a boolean
    operator bool () const
    {
      return m_locked;
    }

    // unlock
    void setUnlock()
    {
      m_locked = false;        
    }

  private:
    boost::mutex & m_mutex;
    bool m_locked;
};

void hello_world()
{
    synchronized(global_mutex)
    {
        std::cout<<"hello";
        boost::this_thread::sleep(boost::posix_time::seconds(2));
        std::cout<<" world"<<std::endl;
    }

    return;
}

void hello_michael()
{
    synchronized(global_mutex)
    {
        std::cout<<"hello";
        std::cout<<" michael"<<std::endl;
    }

    return;
}

int main(int argc, char* argv[])
{
    boost::thread world_thread(&hello_world);
    boost::thread michael_thread(&hello_michael);

    world_thread.join();
    michael_thread.join();

    return 0;
}
