#include "renderer.hpp"

#include "folk/render/visual_component.hpp"
#include "folk/scene/transform_component.hpp"
#include "folk/window/glfw.hpp"
#include "folk/log.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace Folk {

RenderContextHandle Renderer::s_handle {};
bool Renderer::s_frame_buffer_size_changed {false};
Vec2i Renderer::s_frame_buffer_size {};

void Renderer::drawFrame(SceneManager &scene, std::chrono::duration<double> delta)
{
    if (s_frame_buffer_size_changed) {
        glViewport(0, 0, s_frame_buffer_size.x, s_frame_buffer_size.y);
        s_frame_buffer_size_changed = false;
    }

    auto aspect_ratio = static_cast<float>(s_frame_buffer_size.x) / static_cast<float>(s_frame_buffer_size.y);

    Mat4 view_mtx {1.0f};
    Mat4 proj_mtx {1.0f};
    
    auto cam_entity = scene.camera();

    // calculate view and projection matrix
    if (cam_entity == entt::null) {
        // at_vector = {0, 0, 0};
        // eye_vector = {0, 0, 0};
        proj_mtx = glm::perspective(60.0f, aspect_ratio, 0.1f, 100.0f);
    } else {
        view_mtx = glm::inverse(scene.registry().get<TransformComponent>(cam_entity).transformMatrix());
        const auto& cam_data = scene.registry().get<CameraComponent>(cam_entity);
        proj_mtx = glm::perspective(cam_data.fovy, aspect_ratio, cam_data.near, cam_data.far);
    }

    auto reg_view = scene.registry().view<SceneGraphNode, const VisualComponent>();
    reg_view.each(
            [] (const auto entity, SceneGraphNode& transform, const VisualComponent& visual)
            {
                // setViewTransform(view_mtx, proj_mtx);

                auto mesh = visual.visual->getMesh();
                // setVertexBuffer( mesh->vertex_buffer );
                // setIndexBuffer( mesh->index_buffer );

                // setTransform( transform.transformMatrix() );

                // setProgram(visual.visual->getMaterial()->getShader()->handle):
                // draw();
            }
    );

    glClear(GL_COLOR_BUFFER_BIT);

    // end frame (swap buffers?)
    s_handle.swapBuffers();
}

void Renderer::drawPerfMon(const PerformanceMonitor& perf_monitor,
                           DeltaClock::milliseconds_double delta) noexcept
{
    // draw perfomance monitor
}

void Renderer::setContext(RenderContextHandle handle) {
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

void GLAPIENTRY messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                const GLchar* message, const void* userParam)
{
    const char* source_str;
    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        source_str = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        source_str = "WINDOW_SYSTEM";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        source_str = "SHADER_COMPILER";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        source_str = "THIRD_PARTY";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        source_str = "APPLICATION";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        source_str = "OTHER";
        break;

    default:
        source_str = "?";
        break;
    }

    const char* type_str;
    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        type_str = "ERROR";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        type_str = "DEPRECATED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        type_str = "UNDEFINED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        type_str = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        type_str = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        type_str = "OTHER";
        break;

    default:
        type_str = "?";
        break;
    }

    const char* severity_str;
    LogLevel log_level;
    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        severity_str = "HIGH";
        log_level = LogLevel::Error;
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        severity_str = "MEDIUM";
        log_level = LogLevel::Warning;
        break;

    case GL_DEBUG_SEVERITY_LOW:
        severity_str = "LOW";
        log_level = LogLevel::Warning;
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        severity_str = "NOTIFICATION";
        log_level = LogLevel::Message;
        break;

    default:
        severity_str = "?";
        log_level = LogLevel::Message;
        break;
    }

    Log::write(log_level) << "*** OpenGL DEBUG MESSAGE ***"
                          << "\nsource      : " << source_str
                          << "\ntype        : " << type_str
                          << "\nseverity    : " << severity_str
                          << "\ndescription : " << message
                          << "\n\n";
}

void Renderer::initialize() {
    glGetError();
    glDebugMessageCallback(messageCallback, nullptr);

    auto err = glGetError();
    if (err) {
        throw FOLK_CRITICAL_ERROR("Renderer initialization failed!");
    }
}

} // namespace folk