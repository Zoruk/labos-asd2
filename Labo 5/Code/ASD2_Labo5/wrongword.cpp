#include "wrongword.h"
#include "wordgenerartor.h"

#include <iostream>

WrongWord::WrongWord(std::string word, const WordDictionary &dico) : word(word)
{
    if (dico.contain(word))
        return;

    WordGenerartor w(word);

    for (const std::string& s : w.addOneLetter()) {
        //std::cout << "addOneLetter " << s << std::endl;
        if (dico.contain(s))
            posibilites[(std::size_t)CorrectionType::LETTER_ADDED].push_back(s);
    }

    for (const std::string& s : w.changeOneLetter()) {
        if (dico.contain(s))
            posibilites[(std::size_t)CorrectionType::LETTER_CHANGED].push_back(s);
    }

    for (const std::string& s : w.removeOneLetter()) {
        if (dico.contain(s))
            posibilites[(std::size_t)CorrectionType::LETTER_REMOVED].push_back(s);
    }

    for (const std::string& s : w.swapTwoLetter()) {
        if (dico.contain(s))
            posibilites[(std::size_t)CorrectionType::LETTER_SWAPED].push_back(s);
    }
}

std::ostream& operator<<(std::ostream& out, const WrongWord& wrongWord)
{
    out << wrongWord.word << std::endl;
    for(size_t i = 0; i < wrongWord.posibilites.size(); ++i) {
        for (const auto& w: wrongWord.posibilites[i]) {
            out << i + 1 << ":" << w << std::endl;
        }
    }
    return out;
}
