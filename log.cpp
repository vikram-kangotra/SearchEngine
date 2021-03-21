#include "log.h"

#include <iostream>
#include <fstream>
#include <chrono>

namespace Time
{
    std::string getCurrentTime(const char* fmt)
    {
        using namespace std::chrono::_V2;
        std::time_t time = system_clock::to_time_t(system_clock::now());
        char timeBuf[100];
        strftime(timeBuf, 100, fmt, localtime(&time));
        return timeBuf;
    }
}

namespace Log
{
    namespace output
    {
        OutputLocation outputLocation = OutputLocation::FILE;
        std::string outputFileName = "log.txt";

        void writeToFile(const std::string& str)
        {
            std::ofstream file(outputFileName, std::ofstream::app);
            file << str << std::endl;
            file.close();
        }

        void write(const std::string& str)
        {
            switch(outputLocation)
            {
                case OutputLocation::CONSOLE: std::cout << str << std::endl;
                                                break;

                case OutputLocation::FILE: writeToFile(str);
                                            break;
            }
        }
    }

    void write(const std::string& str)
    {
        std::string outStr = Time::getCurrentTime() + ": " + str;
        output::write(outStr);
    }

    void setOutputLocation(output::OutputLocation outputLocation, const std::string& outputFileName)
    {
        output::outputLocation = outputLocation;

        if(!outputFileName.empty() && outputLocation == output::OutputLocation::FILE)
            output::outputFileName = outputFileName;
    }
}
