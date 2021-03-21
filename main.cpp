#include "url.h"
#include <iostream>
#include "log.h"

int main(int argc, char** argv)
{
    Log::setOutputLocation(Log::output::OutputLocation::CONSOLE);

    URL url;
    try {
        url.open("www.google.com",80);
    } catch (const std::string s) {
        std::cout << s;
        Log::write(s);
    }

    url.sendRequest("GET / HTTP/1.1\r\n\r\n");

    std::cout << url.read();

    return 0;
}
