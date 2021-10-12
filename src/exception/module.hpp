#ifndef FOLK_EXCEPTION__MODULE_HPP
#define FOLK_EXCEPTION__MODULE_HPP

#include "../utils/singleton.hpp"

#include <thread>
#include <mutex>

namespace folk {

FOLK_SINGLETON_CLASS_FINAL(ExceptionModule) {

public:
    
    /// Handle the current exception.
    /**
     * This function is meant to be called inside the catch part of a 
     * try-catch.
    */
    void handle();

};

} // namespace folk

#endif // FOLK_EXCEPTION__MODULE_HPP