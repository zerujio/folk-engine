#ifndef FOLK_INPUT__COMMON_HPP
#define FOLK_INPUT__COMMON_HPP

#include <cinttypes>

namespace Folk
{

#define INPUT_CODE_INT_TYPE uint16_t
using InputCodeIntType = INPUT_CODE_INT_TYPE;

/// \brief \~spanish Posibles estados de una tecla/botón.
/// \brief \~english Possible key states.
enum InputState : uint8_t {
    Release = 0,
    Press = 1
};

} // namespace Folk


#endif // FOLK_INPUT__COMMON_HPP