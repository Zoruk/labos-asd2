#include "spellingchecker.h"

#include <iostream>

#include <fstream>
#include <cctype>
#include <algorithm>

static bool checkChar(const char c) {
    if (!isprint(c))
        return true;

    if (isdigit(c))
        return true;

    if (ispunct(c) && c != '\'')
        return true;

    return false;
}

SpellingChecker::SpellingChecker(const std::string file, const WordDictionary& dico)
{
    std::ifstream texteStream(file);

    std::string word;
    while (texteStream >> word) {
        word.erase(std::remove_if(word.begin(), word.end(), checkChar), word.end());
        if (word.length() == 0)
            continue;
        if (!dico.contain(word))
            wrongWords.push_back(WrongWord(word, dico));
    }
}
