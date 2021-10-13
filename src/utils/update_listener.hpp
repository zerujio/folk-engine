#ifndef FOLK_UTILS__UPDATE_LISTENER_HPP
#define FOLK_UTILS__UPDATE_LISTENER_HPP

#include <chrono>

namespace Folk {

class UpdateListener {
public:
    using Delta = std::chrono::duration<double, std::milli>;
    
    virtual void update(Delta delta) = 0;
};

}// namespace folk

#endif//FOLK_UTILS__UPDATE_LISTENER_HPP
