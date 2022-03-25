#include "renderer.hpp"

#include "folk/render/visual_component.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/log.hpp"
#include "folk/render/gl.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"

namespace Folk {

RenderingWindowHandle Renderer::s_handle {};
bool Renderer::s_frame_buffer_size_changed {false};
Vec2i Renderer::s_frame_buffer_size {};

void Renderer::drawFrame(SceneManager &scene, std::chrono::duration<double> delta)
{
    if (s_frame_buffer_size_changed) {
        gl::call::fast(glViewport)(0, 0, s_frame_buffer_size.x, s_frame_buffer_size.y);
        s_frame_buffer_size_changed = false;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    auto aspect_ratio = static_cast<float>(s_frame_buffer_size.x) / static_cast<float>(s_frame_buffer_size.y);

    Mat4 view_mtx {1.0f};
    Mat4 proj_mtx {1.0f};
    
    auto cam_entity = scene.camera();

    // calculate view and projection matrix
    if (cam_entity == entt::null) {
        view_mtx = glm::lookAt(Vec3(0.0f, 0.0f, 1.0f), {0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f});
        proj_mtx = glm::perspective(glm::radians(60.0f), aspect_ratio, 0.1f, 100.0f);


    } else {
        const auto& cam_transform = scene.registry().get<TransformComponent>(cam_entity).transformMatrix();

        Vec3 pos = cam_transform * Vec4(0, 0, 0, 1.0f);
        Vec3 at = cam_transform * Vec4(0, 0, -1.0f, 1.0f);
        Vec3 up = glm::normalize(cam_transform * Vec4(0, 1.0f, 0, 1.0f));

        view_mtx = glm::lookAt(pos, at, up);

        const auto& cam_data = scene.registry().get<CameraComponent>(cam_entity);
        proj_mtx = glm::perspective(glm::radians(cam_data.fovy), aspect_ratio, cam_data.near, cam_data.far);
    }

    auto reg_view = scene.registry().view<SceneGraphNode, const VisualComponent>();
    reg_view.each(
            [&view_mtx, &proj_mtx] (const auto entity, SceneGraphNode& transform, const VisualComponent& visual)
            {
                auto mesh = visual.visual->getMesh();
                auto material = visual.visual->getMaterial();

                mesh->m_vertex_array.bind();
                material->getShader()->m_shader_program.bind();

                setUserUniforms(*material);
                setTransformUniforms(transform.transformMatrix(), view_mtx, proj_mtx, *material);

                gl::call::fast(glDrawElements)(
                        GL_TRIANGLES,
                        mesh->m_index_count,
                        static_cast<GLenum>(mesh->m_index_type),
                        nullptr);
            }
    );

    // finish frame
    s_handle.swapBuffers();
}

void Renderer::setUserUniforms(const Material &material) {
    for (const auto& u : material.m_uniforms)
        u->bind();
}

void Renderer::setTransformUniforms(const Mat4& model, const Mat4& view, const Mat4& projection, const Material& material) {
    auto shader = material.getShader();
    auto model_loc = shader->builtInUniformLoc(Shader::BuiltInUniform::Model);
    auto view_loc = shader->builtInUniformLoc(Shader::BuiltInUniform::View);
    auto proj_loc = shader->builtInUniformLoc(Shader::BuiltInUniform::Projection);

    gl::call::fast(glUniformMatrix4fv)(model_loc, 1, false, glm::value_ptr(model));
    gl::call::fast(glUniformMatrix4fv)(view_loc, 1, false, glm::value_ptr(view));
    gl::call::fast(glUniformMatrix4fv)(proj_loc, 1, false, glm::value_ptr(projection));
}

void Renderer::drawPerfMon(const PerformanceMonitor& perf_monitor,
                           DeltaClock::milliseconds_double delta) noexcept
{
    // draw performance monitor
}

void Renderer::setContext(RenderingWindowHandle handle) {
    s_handle = handle;
    s_handle.makeContextCurrent();
    s_handle.setFrameBufferSizeCallback<setFrameBufferSize>();
    setFrameBufferSize(s_handle.getFrameBufferSize());
    glClearColor(.1f, .1f, .1f, 1.0f);
}

void Renderer::setFrameBufferSize(Vec2i size) {
    s_frame_buffer_size_changed = true;
    s_frame_buffer_size = size;
}

void Renderer::initialize(RenderingWindowHandle handle) {
    setContext(handle);

    if constexpr(c_debug_build) {
        glDebugMessageCallback(debugMessageCallback, nullptr);
    }
}


constexpr const char *errorSourceString(GLenum source) noexcept {
    switch (source)
    {
        case GL_DEBUG_SOURCE_API:
            return "API";

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            return "WINDOW_SYSTEM";

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            return "SHADER_COMPILER";

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            return "THIRD_PARTY";

        case GL_DEBUG_SOURCE_APPLICATION:
            return "APPLICATION";

        case GL_DEBUG_SOURCE_OTHER:
            return "OTHER";

        default:
            return "<invalid>";
    }
}

constexpr const char *errorTypeString(GLenum type) noexcept {
    switch (type)
    {
        case GL_DEBUG_TYPE_ERROR:
            return "ERROR";

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            return "DEPRECATED_BEHAVIOR";

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            return "UNDEFINED_BEHAVIOR";

        case GL_DEBUG_TYPE_PORTABILITY:
            return "PORTABILITY";

        case GL_DEBUG_TYPE_PERFORMANCE:
            return "PERFORMANCE";

        case GL_DEBUG_TYPE_OTHER:
            return "OTHER";

        default:
            return "<invalid>";
    }
}

constexpr const char *errorSeverityString(GLenum severity) noexcept {
    switch (severity)
    {
        case GL_DEBUG_SEVERITY_HIGH:
            return "HIGH";

        case GL_DEBUG_SEVERITY_MEDIUM:
            return "MEDIUM";

        case GL_DEBUG_SEVERITY_LOW:
            return "LOW";

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            return "NOTIFICATION";

        default:
            return "<invalid>";
    }
}

void GLAPIENTRY Renderer::debugMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                               GLsizei length, const GLchar* message, const void* userParam)
{
    LogLevel log_level;
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            log_level = LogLevel::Error;
            break;
        case GL_DEBUG_SEVERITY_MEDIUM:
            log_level = LogLevel::Warning;
            break;
        case GL_DEBUG_SEVERITY_LOW:
            log_level = LogLevel::Message;
            break;
        case GL_DEBUG_SEVERITY_NOTIFICATION:
            log_level = LogLevel::Trace;
            break;
        default:
            log_level = LogLevel::Warning;
            break;
    }

    Log::write(log_level) << "*** OpenGL DEBUG MESSAGE ***"
                          << "\nsource      : " << errorSourceString(source)
                          << "\ntype        : " << errorTypeString(type)
                          << "\nseverity    : " << errorSeverityString(severity)
                          << "\ndescription : " << message
                          << "\n\n";
}

} // namespace folk