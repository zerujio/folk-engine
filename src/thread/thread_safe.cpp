#include "thread_safe.hpp"

namespace folk::thread
{

void ThreadSafeObject::lock() 
{
    m.lock();
}

void ThreadSafeObject::unlock() 
{
    m.unlock();
}

}//namespace folk::thread