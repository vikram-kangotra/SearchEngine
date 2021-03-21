#include "searcher.h"

void Searcher::search(const std::string& url)
{
    crawler.crawl(url);
}

const std::vector<std::string>& Searcher::getLinks()
{
    return crawler.getLinks();
}
