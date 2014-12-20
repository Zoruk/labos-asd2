#ifndef WORDDICTIONARYSTL_H
#define WORDDICTIONARYSTL_H

#include "worddictionary.h"
#include <unordered_set>

class WordDictionarySTL : public WordDictionary
{
private:
    std::unordered_set<std::string> words;

public:
    WordDictionarySTL();
    void add(const std::string s) override { words.insert(s); }
    void del(const std::string s) override { words.erase(s); }
    bool contain(const std::string s) override { return words.count(s) != 0; }
};

#endif // WORDDICTIONARYSTL_H
