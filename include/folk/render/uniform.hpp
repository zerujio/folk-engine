#ifndef SRC_RENDER__UNIFORM_HPP
#define SRC_RENDER__UNIFORM_HPP

#include "uniform_type.hpp"
#include "texture.hpp"
#include "gl_uniform.hpp"

#include <array>
#include <memory>

namespace Folk {

/**
 * @brief Interface for Uniform classes that store the value for a shader uniform.
 */
class IUniform {

    friend class Renderer;

protected:
    /// [Internal usage] Set the uniform to the stored value (on the currently bound program).
    virtual void bind() const = 0;

};

/// Base class for plain data uniforms.
template<typename ValueT>
class BaseUniform : public IUniform {
public:
    explicit BaseUniform(uint loc) : m_location(loc) {}

    /// The value of the uniform.
    ValueT value{};

protected:
    [[nodiscard]] uint loc() const {
        return m_location;
    }

private:
    uint m_location;
};


/// Base class for plain data uniform arrays
template<typename ValueT>
class BaseArrayUniform : public IUniform {
public:

    /// Construct an array uniform with @p count elements.
    explicit BaseArrayUniform(uint loc, std::size_t count)
            : m_location(loc), m_size(count), m_values(std::make_unique<ValueT[]>(count)) {}

    /// Element access with bounds checking.
    [[nodiscard]] const ValueT &value(std::size_t i) const {
        if (i >= m_size)
            throw Error("Array uniform index out of range");

        return m_values[i];
    }

    [[nodiscard]] ValueT &value(std::size_t i) {
        const BaseArrayUniform* const_this = this;
        return const_cast<ValueT &>(const_this->value(i));
    }

    /// Pointer to first element (i.e. array access with no bounds checking).
    [[nodiscard]] const ValueT *values() const {
        return m_values.get();
    }

    [[nodiscard]] ValueT *values() {
        return m_values.get();
    }

    /// Number of elements in the array.
    [[nodiscard]] std::size_t size() const {
        return m_size;
    }

protected:
    [[nodiscard]] uint loc() const { return m_location; }

private:
    uint m_location;
    std::size_t m_size;
    std::unique_ptr<ValueT[]> m_values;
};


/**
 * @brief Stores the value of a uniform.
 * @tparam T A scalar type.
 */
template<typename T>
class Uniform final : public BaseUniform<T> {
public:
    using BaseUniform<T>::BaseUniform;

protected:
    void bind() const override {
        gl::setUniform<T>(this->loc(), 1, 1, &this->value);
    }
};

/**
 * @brief Stores the values of an uniform array.
 * @tparam T A scalar type.
 */
template<typename T>
class Uniform<T[]> final : public BaseArrayUniform<T> {
public:
    using BaseArrayUniform<T>::BaseArrayUniform;

protected:
    void bind() const override {
        gl::setUniform<T>(this->loc(), 1, this->size(), this->values());
    }
};

/**
 * @brief Uniform specialization for vector types.
 */
template<auto N, class T, auto P>
class Uniform<glm::vec<N, T, P>> final : public BaseUniform<glm::vec<N, T, P>> {
public:
    using BaseUniform<glm::vec<N, T, P>>::BaseUniform;

protected:
    void bind() const override {
        gl::setUniform<T>(this->loc(), N, 1, &this->value.x);
    }
};

/**
 * @brief Uniform array specialization for vector types.
 */
template<auto N, class T, auto P>
class Uniform<glm::vec<N, T, P>[]> final : public BaseArrayUniform<glm::vec<N, T, P>> {
public:
    using BaseArrayUniform<glm::vec<N, T, P>>::BaseArrayUniform;

protected:
    void bind() const override {
        gl::setUniform<T>(this->loc(), N, this->size(), &this->value(0).x);
    }

};

/**
 * @brief Uniform specialization for matrix types.
 */
template<auto N, auto M, class T, auto P>
class Uniform<glm::mat<N, M, T, P>> final : public BaseUniform<glm::mat<N, M, T, P>> {
public:
    using BaseUniform<glm::mat<N, M, T, P>>::BaseUniform;

    bool transpose{false};

protected:
    void bind() const override {
        gl::setUniformMatrix<T>(this->loc(), N, M, 1, transpose, &(this->value[0][0]));
    }
};

/**
 * @brief Uniform array specialization for matrix types.
 */
template<auto N, auto M, class T, auto P>
class Uniform<glm::mat<N, M, T, P>[]> final : public BaseArrayUniform<glm::mat<N, M, T, P>> {
public:
    using BaseArrayUniform<glm::mat<N, M, T, P>>::BaseArrayUniform;

    bool transpose{false};

protected:
    void bind() const override {
        gl::setUniformMatrix<T>(this->loc(), N, M, this->size(), transpose, &(this->value(0)[0][0]));
    }
};

/**
 * @brief Uniform array specialization for texture sampler types.
 * @tparam TextureType A texture type, such as Texture2D.
 */
template<TextureType T>
class Uniform<Texture<T>> final : public IUniform {
public:
    explicit Uniform(uint texture_unit) : m_texture_unit(texture_unit) {}

    std::shared_ptr<Texture<T>> p_texture{};

protected:

    void bind() const override {
        gl::Texture::setActive(m_texture_unit);
        p_texture->bind();
    }

private:
    uint m_texture_unit;
};

} // namespace Folk


#endif //SRC_RENDER__UNIFORM_HPP
