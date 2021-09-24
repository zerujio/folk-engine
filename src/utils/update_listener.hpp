#ifndef FOLK_UTILS__UPDATE_LISTENER_HPP
#define FOLK_UTILS__UPDATE_LISTENER_HPP

#include <chrono>

class UpdateListener {
public:
    virtual void update(double delta) = 0;
};

#endif//FOLK_UTILS__UPDATE_LISTENER_HPP
