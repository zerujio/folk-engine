//
// Created by sergio on 15-02-22.
//

#ifndef SRC_RENDER__UNIFORM_TYPE_INFO_HPP
#define SRC_RENDER__UNIFORM_TYPE_INFO_HPP

#include "folk/render/uniform_type.hpp"

#include <functional>
#include <map>

namespace Folk {

/// A surrogate for a glUniform function. Necessary to modify uniforms without knowing their types statically.
struct glUniformFunctor {

    virtual ~glUniformFunctor() = default;

    /**
     * @brief Call the appropriate glUniform function
     * @param location uniform location
     * @param count >1 if array
     * @param value An opaque pointer to the value to set.
     * @param transposed Whether to transpose uniforms or not. Ignored by non matrix types.
     */
    virtual void operator() (unsigned int location, unsigned int count, const void* value, bool transposed) const = 0;
};

/// Information about uniform types.
class UniformTypeInfo final {

    static const std::map<UniformType, UniformTypeInfo> s_info_map;

    std::shared_ptr<const glUniformFunctor> p_glUniform;
    std::size_t m_size;

public:
    UniformTypeInfo(std::size_t size, std::shared_ptr<glUniformFunctor> ptr) : m_size(size), p_glUniform(std::move(ptr)) {}

    /// Size in bytes of the type.
    [[nodiscard]] std::size_t size() const { return m_size; }

    /// The glUniform* function needed to modify uniform of this type.
    [[nodiscard]] const auto& glUniform() const { return *p_glUniform; }

    /// Get type info from enum value.
    static const UniformTypeInfo& get(UniformType type);

    static constexpr bool isMatrix(UniformType type) {
        return (type >= UniformType::fMat2 && type <= UniformType::fMat4x3)
        || (type >= UniformType::dMat2 && type <= UniformType::dMat4x3);
    }
};

} // namespace Folk

#endif //SRC_RENDER__UNIFORM_TYPE_INFO_HPP
