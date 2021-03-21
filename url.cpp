#include "url.h"

#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#include "log.h"


void URL::open(const std::string& url, int port)
{
    if(port == -1)
        port = determinePortFromURL(url);

    mSocketD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    timeval tv;
    tv.tv_sec = 2;
    tv.tv_usec = 0;
    setsockopt(mSocketD, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof(timeval));

    sockaddr_in addr = { 0 };
    addr.sin_addr.s_addr = resolveHost(url);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);

    if(connect(mSocketD, (const sockaddr*)&addr, sizeof addr) < 0) {
        char err[100];
        sprintf(err, "Failed to connect to %s in url.cpp", url.c_str());
        throw std::string(err);
    }

    Log::write("Connected");
}

uint32_t URL::resolveHost(const std::string& url)
{
    Log::write("Resolving " + url);

    hostent* host = gethostbyname(url.c_str());

    if(host == nullptr || host->h_addr == nullptr) {
        char err[100];
        sprintf(err, "Failed to resolve %s in url.cpp", url.c_str());
        throw std::string(err);
    }

    in_addr addr = *reinterpret_cast<in_addr*>(host->h_addr);

    mIp = inet_ntoa(addr);

    Log::write("Resolved host. IP is " + mIp);

    return addr.s_addr;
}

void URL::sendRequest(const std::string& req)
{
    if(req.empty() || send(mSocketD, req.c_str(), req.size(), 0) == -1) {
        char err[100];
        sprintf(err, "Failed to send request in url.cpp");
        throw std::string(err);
    }
}

std::string URL::read()
{
    std::string Data;
    char recvBuf[256] = { 0 };

    while(true)
    {
        int len = recv(mSocketD, recvBuf, 256, 0);
        if(len <= 0)
            break;
        Data += recvBuf;
    }

    return Data;
}

void URL::Close()
{
    close(mSocketD);
}
