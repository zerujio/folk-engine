//
// Created by sergio on 11-01-22.
//

#ifndef INCLUDE_FOLK_INPUT__CONNECTION_HPP
#define INCLUDE_FOLK_INPUT__CONNECTION_HPP

#include "entt/entt.hpp"

namespace Folk {

/**
 * @brief Type returned by functions that establish callbacks.
 *
 * A connection object manages a "connected" callback function. The release() member function may be used to disconnect
 * the callback.
 */
using Connection = entt::connection;

/**
 * @brief A Connection object that will automatically disconnect the callback when its lifetime ends.
 */
using ScopedConnection = entt::scoped_connection;

}

#endif //INCLUDE_FOLK_INPUT__CONNECTION_HPP
