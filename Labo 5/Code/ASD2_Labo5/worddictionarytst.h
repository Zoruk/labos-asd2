#ifndef WORDDICTIONARYTST_H
#define WORDDICTIONARYTST_H

#include "worddictionary.h"
#include "ternarysearchtrie.h"
#include "ternarysearchtriebis.h"
class WordDictionaryTST : public WordDictionary
{
private:
    TernarySearchTrieBis words;
public:
    WordDictionaryTST();

    void add(const std::string s);
    void del(const std::string s); // TODO
    bool contain(const std::string s) const;
    std::size_t size() const { return words.size(); } //TODO
};

#endif // WORDDICTIONARYTST_H
