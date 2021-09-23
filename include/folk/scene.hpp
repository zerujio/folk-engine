#ifndef SCENE__SCENE_HPP
#define SCENE__SCENE_HPP

namespace folk
{

class Scene final {
public:
    using UpdateCallback = void (*)(Scene&, double);

    /* The function to be called whenever a new frame is drawn for this scene. 
    
    The frameDraw function takes two arguments: a reference to the scene being
    drawn, and a double representing the amount of time (in seconds) passed since
    the last time the function was called.
    
    If some form of V-Sync is active, the function will be called at the refresh
    rate of the monitor. If not, it will be called as fast as possible. */
    UpdateCallback frameDrawCallback {nullptr};

    /* Set the function to be called whenever the state of the scene is updated.

    The gameUpdate function takes two arguments: a reference to the scene being
    updated, and a double representing the amount of time in seconds that has
    passed since the las time the function was called.

    The engine will attempt to call this function at a stable frequency (60Hz by
    default), but may be lowered if processing takes too long. Input is polled
    at this same rate. */
    UpdateCallback gameUpdateCallback {nullptr};

private:
};

}// namespace folk::scene

#endif//SCENE__SCENE_HPP
