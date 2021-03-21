#ifndef LOG_H
#define LOG_H

#include <string>

namespace Time
{
    std::string getCurrentTime(const char* fmt = "%c");
}

namespace Log
{
    namespace output
    {
        enum class OutputLocation { CONSOLE, FILE };
    }

    void write(const std::string& str);
    void setOutputLocation(output::OutputLocation outputLocation, const std::string& outputFileName = "");
}

#endif // LOG_H
