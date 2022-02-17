#ifndef INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
#define INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP

#include "gl_object.hpp"
#include "gl_shader.hpp"

namespace Folk::gl {

GLboolean _isProgram(GLuint id);

class ShaderProgram : public BaseHandle<_isProgram> {
public:
    /// Link the GLSL program shaders. A shader must have been attached previously.
    void link() const;

    /// Attach a shader.
    void attach(ShaderHandle shader) const;

    /// Detach a shader.
    void detach(ShaderHandle shader) const;

    /// Make this shader program current.
    void bind() const;

    /// Unbind the currently bound shader program.
    static void unbind();

    /// Bind a variable name to a vertex attribute location. Must be called before linking for it to take effect.
    void bindAttribLocation(GLuint index, const char* name) const;

    /// Program introspection interfaces
    enum class Interface : GLenum {
        Uniform = GL_UNIFORM,
        UniformBlock = GL_UNIFORM_BLOCK,
        AtomicCounterBuffer = GL_ATOMIC_COUNTER_BUFFER,
        ProgramInput = GL_PROGRAM_INPUT,
        ProgramOutput = GL_PROGRAM_OUTPUT,
        TransformFeedbackVarying = GL_TRANSFORM_FEEDBACK_VARYING,
        TransformFeedbackBuffer = GL_TRANSFORM_FEEDBACK_BUFFER,
        BufferVariable = GL_BUFFER_VARIABLE,
        ShaderStorageBlock = GL_SHADER_STORAGE_BLOCK,
        VertexSubroutine = GL_VERTEX_SUBROUTINE,
        GeometrySubroutine = GL_GEOMETRY_SUBROUTINE,
        FragmentSubroutine = GL_FRAGMENT_SUBROUTINE,
        TessControlSubroutine = GL_TESS_CONTROL_SUBROUTINE,
        TessEvaluationSubroutine = GL_TESS_EVALUATION_SUBROUTINE,
        ComputeSubroutine = GL_COMPUTE_SUBROUTINE
    };

    /// Interface parameters
    enum class InterfaceParam : GLenum {
        /// Number of active resources
        ActiveResources = GL_ACTIVE_RESOURCES,

        /// Length of the longest resource name in the interface.
        MaxNameLength = GL_MAX_NAME_LENGTH,

        /// The maximum number of active variables among all the resources in the interface.
        MaxNumActiveVariables = GL_MAX_NUM_ACTIVE_VARIABLES,

        /**
         * @brief The largest number of compatible subroutines among all subroutine variables for that shader stage.
         * This can only be used with the *Subroutine interfaces.
         */
        MaxNumCompatibleSubroutines = GL_MAX_NUM_COMPATIBLE_SUBROUTINES
    };

    /// Query interface info
    [[nodiscard]] GLint getInterface(Interface interface, InterfaceParam param) const;

    /// Query a resource's name.
    [[nodiscard]] std::string getResourceName(Interface interface, GLuint resource_index) const;

    /// Resource properties
    enum class ResourceProp : GLenum {
        NameLength = GL_NAME_LENGTH,
        Type = GL_TYPE,
        ArraySize = GL_ARRAY_SIZE,
        Offset = GL_OFFSET,
        BlockIndex = GL_BLOCK_INDEX,
        ArrayStride = GL_ARRAY_STRIDE,
        MatrixStride = GL_MATRIX_STRIDE,
        IsRowMajor = GL_IS_ROW_MAJOR,
        AtomicCounterBufferIndex = GL_ATOMIC_COUNTER_BUFFER_INDEX,
        BufferBinding = GL_BUFFER_BINDING,
        BufferDataSize = GL_BUFFER_DATA_SIZE,
        NumActiveVariables = GL_NUM_ACTIVE_VARIABLES,
        ActiveVariables = GL_ACTIVE_VARIABLES,
        ReferencedByVertexShader = GL_REFERENCED_BY_VERTEX_SHADER,
        ReferencedByTessControlShader = GL_REFERENCED_BY_TESS_CONTROL_SHADER,
        ReferencedByTessEvaluationShader = GL_REFERENCED_BY_TESS_EVALUATION_SHADER,
        ReferencedByGeometryShader = GL_REFERENCED_BY_GEOMETRY_SHADER,
        ReferencedByFragmentShader = GL_REFERENCED_BY_FRAGMENT_SHADER,
        ReferencedByComputeShader = GL_REFERENCED_BY_COMPUTE_SHADER,
        TopLevelArraySize = GL_TOP_LEVEL_ARRAY_SIZE,
        TopLevelArrayStride = GL_TOP_LEVEL_ARRAY_STRIDE,
        Location = GL_LOCATION,
        LocationIndex = GL_LOCATION_INDEX,
        IsPerPatch = GL_IS_PER_PATCH,
    };

    /**
     * @brief Query multiple properties for a single active resource within an interface.
     * @param interface The program interface containing the resource.
     * @param resource_index The location of the active resource.
     * @param property_count The amount of properties to retrieve.
     * @param properties The list of properties to retrieve.
     * @param value_buffer_size The size of the buffer in which to write the values of the properties.
     * @param value_lengths A buffer in which to write the length of the value retrieved for each property.
     * @param value_buffer A buffer in which to write the values of the properties.
     */
    void getResource(Interface interface, GLuint resource_index,
                     GLsizei property_count, const ResourceProp* properties,
                     GLsizei value_buffer_size, GLsizei* value_lengths, GLint* value_buffer) const;

    /**
     * @brief Retrieve multiple properties of a single active resource within an interface.
     * @param interface The interface that contains the resource.
     * @param properties The list of properties to retrieve.
     * @param value_lengths A vector to store the lengths of the retrieved properties. If its length is different from
     * that of @p properties, it will be resized to match.
     * @param values A vector to store the values of the retrieved properties.
     */
    void getResource(Interface interface, GLuint resource_index,
                     const std::vector<ResourceProp>& properties,
                     std::vector<GLsizei>& value_lengths, std::vector<GLint>& values) const;

    /// Retrieve multiple properties of a single active resource within an interface.
    void getResource(Interface interface, GLuint resource_index, const std::vector<ResourceProp>& properties,
                     std::vector<GLint>& values) const;

    /**
     * @brief Retrieve multiple properties of a single active resource within an interface.
     * @tparam PropNumber Number of properties to retrieve
     * @tparam ArrayLength Length of the array to write property values into.
     * @param interface The interface that contains the resource.
     * @param properties A list of properties to retrieve.
     * @param value_lengths A vector to store the lengths of the retrieved properties.
     * @param values
     */
    template<std::size_t PropNumber, std::size_t ArrayLength>
    void getResource(Interface interface, GLuint resource_index,
                     const std::array<ResourceProp, PropNumber>& properties,
                     std::array<GLsizei, PropNumber>& value_lengths, std::array<GLint, ArrayLength>& values) const
    {
        getResource(interface, resource_index, PropNumber, properties.data(), ArrayLength, value_lengths.data(), values.data());
    }

    /// Retrieve multiple properties of a single active resource within an interface.
    template<std::size_t PropNumber, std::size_t ArrayLength>
    void getResource(Interface interface, GLuint resource_index, const std::array<ResourceProp, PropNumber>& properties,
                     std::array<GLint, ArrayLength>& values) const {
        getResource(interface, resource_index, PropNumber, properties.data(), ArrayLength, nullptr, values.data());
    }
};

GLuint _createProgram();
void _deleteProgram(GLuint id);

using ShaderProgramManager = ObjectManager<ShaderProgram, _createProgram, _deleteProgram>;

} // namespace Folk

#endif //INCLUDE_FOLK_RENDER__GL_SHADER_PROGRAM_HPP
