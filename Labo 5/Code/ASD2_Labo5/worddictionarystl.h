#ifndef WORDDICTIONARYSTL_H
#define WORDDICTIONARYSTL_H

#include "worddictionary.h"
#include <unordered_set>

#include <iostream>

class WordDictionarySTL : public WordDictionary
{
private:
    std::unordered_set<std::string> words;

public:
    WordDictionarySTL();
    ~WordDictionarySTL() override { }
    void add(const std::string s) override;// { words.insert(s); std::cout << s << "\n"; }
    void del(const std::string s) override;// { words.erase(s); }
    bool contain(const std::string s) const override;// { return words.count(s) != 0; }
    std::size_t size() const override;// { return (std::size_t)words.size(); }
};

#endif // WORDDICTIONARYSTL_H
