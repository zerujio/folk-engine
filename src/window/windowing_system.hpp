//
// Created by sergio on 25-01-22.
//

#ifndef SRC_WINDOW__WINDOWING_SYSTEM_HPP
#define SRC_WINDOW__WINDOWING_SYSTEM_HPP


namespace Folk {

class WindowingSystem final {

    friend class EngineSingleton;

    /// Initialize the windowing library.
    static void startUp();

    /// De-initialize the windowing library.
    static void shutDown();

    /**
     * @brief Initializes/de-initializes the windowing library in RAII style.
     */
    struct ScopedInitializer final {
        /// Calls startUp();
        ScopedInitializer() {
            startUp();
        }

        /// Calls shutDown();
        ~ScopedInitializer() {
            shutDown();
        }

        ScopedInitializer(const ScopedInitializer &) = delete;
        ScopedInitializer& operator=(const ScopedInitializer &) = delete;
    };

public:
    WindowingSystem() = delete;
};

} // namespace Folk


#endif //SRC_WINDOW__WINDOWING_SYSTEM_HPP
