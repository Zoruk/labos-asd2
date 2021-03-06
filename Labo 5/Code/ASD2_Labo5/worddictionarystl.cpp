#include "worddictionarystl.h"

WordDictionarySTL::WordDictionarySTL()
{
}

void WordDictionarySTL::add(const std::string s) {
    words.insert(s);
}

void WordDictionarySTL::del(const std::string s) {
    words.erase(s);
}

bool WordDictionarySTL::contain(const std::string s) const {
    return words.count(s) != 0;
}

std::size_t WordDictionarySTL::size() const {
    return (std::size_t)words.size();
}
