#ifndef SEARCHER_H
#define SEARCHER_H

#include <vector>
#include <string>

#include "crawler.h"

class Searcher
{
public:
    void search(const std::string& url);
    const std::vector<std::string>& getLinks();
private:
    Crawler crawler;
};

#endif // SEARCHER_H
