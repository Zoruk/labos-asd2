#include "worddictionarytst.h"

WordDictionaryTST::WordDictionaryTST()
{
}

void WordDictionaryTST::add(const std::string s) {
    words.put(s.c_str());
}

void WordDictionaryTST::del(const std::string s) {
    words.deleteElement(s.c_str());
}

bool WordDictionaryTST::contain(const std::string s) const {
    return words.contains(s.c_str());
}
