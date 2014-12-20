#ifndef WORDDICTIONARY_H
#define WORDDICTIONARY_H

#include <string>

class WordDictionary
{
public:
    WordDictionary();

    virtual void add(const std::string s) = 0;
    virtual void del(const std::string s) = 0;
    virtual bool contain(const std::string s) = 0;
};

#endif // WORDDICTIONARY_H
