#include "bgfx_callback_handler.hpp"

#include "folk/core/log.hpp"
#include "folk/core/error.hpp"

namespace Folk {

void BGFXCallbackHandler::screenShot(const char* file_path,
                                     uint32_t width,
                                     uint32_t height,
                                     uint32_t pitch,
                                     const void* data,
                                     uint32_t size,
                                     bool yflip)
{
    m_log.begin(LogLevel::WARNING) << "BGFX screenShot used but not implemented";
}

void BGFXCallbackHandler::captureBegin(uint32_t _width, uint32_t _height, uint32_t _pitch,
                                       bgfx::TextureFormat::Enum _format, bool _yflip)
{
    m_log.begin(LogLevel::WARNING) << "BGFX captureBegin used but not implemented";
}

void BGFXCallbackHandler::captureEnd() {}

void BGFXCallbackHandler::captureFrame(const void *_data, uint32_t _size) {
    m_log.begin(LogLevel::WARNING) << "BGFX captureFrame used but not implemented";
}


BGFXCallbackHandler::BGFXCallbackHandler(Log& log, ExceptionHandler& exc)
        : m_log(log), m_handler(exc)
{}

void BGFXCallbackHandler::fatal(const char* file_path,
                                uint16_t line,
                                bgfx::Fatal::Enum code,
                                const char* description)
{
    m_log.begin(LogLevel::ERROR)
            << file_path << ": " << line << " | " << std::hex << code;

    if (code != bgfx::Fatal::Enum::DebugCheck)
        m_handler.throwException<CriticalError>(description, FOLK_HERE_ARGS);
}

void BGFXCallbackHandler::traceVargs(const char* file_path,
                                     uint16_t line,
                                     const char* format,
                                     va_list arg_list)
{
    constexpr std::size_t buflen = 2048;
    char temp[buflen];

    std::vsnprintf(temp, buflen, format, arg_list);

    m_log.begin(LogLevel::TRACE)
            << file_path << ": " << line << " | " << temp;
}

} // namespace Folk