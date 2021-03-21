#ifndef CRAWLER_H
#define CRAWLER_H

#include <vector>
#include <string>

class Crawler
{
public:
    void crawl(const std::string& url);
    const std::vector<std::string>& getLinks();
private:
    std::vector<std::string> mLinks;
};

#endif // CRAWLER_H
