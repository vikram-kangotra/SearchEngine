#ifndef URL_h
#define URL_H

#include <string>

class URL
{
public:
    ~URL() {Close();}

    uint32_t resolveHost(const std::string& url);
    void open(const std::string& url, int port=-1);

    void Close();
    std::string read();

    void sendRequest(const std::string& req);

    int determinePortFromURL(const std::string& url){return 80;}         // Needs IMplementation

    const std::string& getIP() { return mIp;}
private:
    int mSocketD;
    std::string mIp;
};

#endif // URL_h
