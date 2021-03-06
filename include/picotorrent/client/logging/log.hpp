#pragma once

#include <functional>
#include <memory>
#include <ostream>
#include <picotorrent/client/logging/log_record.hpp>
#include <string>
#include <windows.h>

#define LOG(level) \
    ::picotorrent::client::logging::log::instance().open_record(picotorrent::client::logging::log_level::level, __FUNCTION__).stream()

namespace picotorrent
{
namespace client
{
namespace logging
{
    enum log_level
    {
        trace,
        debug,
        info,
        warning,
        error,
        fatal
    };

    class log
    {
    public:
        log();
        ~log();

        static log& instance();

        log_record open_record(log_level level, const char* functionName);
        void set_unhandled_exception_callback(const std::function<void(const std::string&)> &callback);

    private:
        void init();

        static LONG WINAPI on_unhandled_exception(PEXCEPTION_POINTERS exceptionInfo);

        std::function<void(const std::string&)> unhandled_exception_callback_;
        std::unique_ptr<std::ostream> out_;
    };

    std::ostream& operator<<(std::ostream &stream, const log_level level);
}
}
}
