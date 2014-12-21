#ifndef WRONGWORD_H
#define WRONGWORD_H

#include <string>
#include <array>
#include <list>
#include <iostream>

#include "worddictionary.h"

class WrongWord
{
    friend std::ostream& operator<<(std::ostream& out, const WrongWord& wrongWord);

public:
    typedef std::array<std::list<std::string>, 4> Possibilities;
    enum class CorrectionType {
        LETTER_REMOVED,
        LETTER_ADDED,
        LETTER_CHANGED,
        LETTER_SWAPED
    };

private:
    std::string word;
    Possibilities posibilites;

public:
    WrongWord(std::string word, const WordDictionary& dico);

    const Possibilities& getPosibilites() { return posibilites; }

};
#endif // WRONGWORD_H
