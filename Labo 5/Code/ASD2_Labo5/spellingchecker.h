#ifndef SPELLINGCHECKER_H
#define SPELLINGCHECKER_H

#include <string>
#include "wrongword.h"
#include "worddictionary.h"

class SpellingChecker
{
private:
    std::list<WrongWord> wrongWords;

public:
    SpellingChecker(const std::string file, const WordDictionary& dico);

    const std::list<WrongWord>& getWrongWords() const { return wrongWords; }
};

#endif // SPELLINGCHECKER_H
