//
// Created by sergio on 25-01-22.
//

#ifndef SRC_WINDOW__WINDOWING_SYSTEM_HPP
#define SRC_WINDOW__WINDOWING_SYSTEM_HPP


namespace Folk {

struct WindowingSystem final {

    /// Initialize the windowing library.
    static void initialize();

    /// De-initialize the windowing library.
    static void terminate();

    /// Update input, invoke callbacks, etc...
    static void pollEvents();

};

} // namespace Folk


#endif //SRC_WINDOW__WINDOWING_SYSTEM_HPP
