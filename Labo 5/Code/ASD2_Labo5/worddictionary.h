#ifndef WORDDICTIONARY_H
#define WORDDICTIONARY_H

#include <string>

class WordDictionary
{
public:
    WordDictionary();
    virtual ~WordDictionary();

    virtual void add(const std::string s) = 0;
    virtual void del(const std::string s) = 0;
    virtual bool contain(const std::string s) const = 0;
    virtual std::size_t size() const = 0;

    void load(const std::string file, bool lowercase);
};

#endif // WORDDICTIONARY_H
