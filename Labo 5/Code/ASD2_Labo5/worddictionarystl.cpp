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

bool WordDictionarySTL::contain(const std::string s) {
    return words.count(s) != 0;
}

std::size_t WordDictionarySTL::size() {
    return (std::size_t)words.size();
}
