#include "delta_clock.hpp"
#include "folk/core/error.hpp"

namespace Folk {

DeltaClock::DeltaClock(std::chrono::nanoseconds max_delta) 
    : _max_delta(max_delta) {}


void DeltaClock::click() {
    auto now = clock::now();
    _last_delta = now - _initial_time;
    _clamped_last_delta = _last_delta > _max_delta ? _max_delta : _last_delta;
    _initial_time = now;
}

void DeltaClock::setMaxDelta(std::chrono::nanoseconds dt) {
    if (dt <= std::chrono::nanoseconds::zero()) {
        throw FOLK_RUNTIME_ERROR(
            "DeltaClock::setMaxDelta: maxDelta must be greater than zero.");
    
    _max_delta = dt;
    }
}
}//namespace folk
