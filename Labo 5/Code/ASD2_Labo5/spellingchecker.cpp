#include "spellingchecker.h"

#include <iostream>

#include <fstream>
#include <cctype>
#include <sstream>

#include <algorithm>
#include <unordered_set>

static bool checkChar(const char c) {
    if ((ispunct(c) && c != '\'') || isdigit(c))
        return true;
    switch (c) {
    case '$':
        return true;
    default:
        return false;
    }

    if (!isprint(c))
        return true;

    if (isdigit(c))
        return true;

    if (ispunct(c) && c != '\'')
        return true;

    return false;
}

// TODO do a better read
SpellingChecker::SpellingChecker(const std::string file, const WordDictionary& dico)
{
    std::unordered_set<std::string> checked;
    std::ifstream texteStream(file);

    std::stringstream stream;

    texteStream.seekg (0, std::ios::end);
    size_t length = texteStream.tellg();
    char* buffer = new char[length];
    texteStream.seekg (0, std::ios::beg);
    texteStream.read(buffer, length);
    texteStream.close();

    for (size_t i = 0; i < length; ++i) {
        if (checkChar(buffer[i]))
            buffer[i] = ' ';
        buffer[i] = tolower(buffer[i]);
    }
    stream << buffer;
    delete[] buffer;



    std::string word;

    while (stream >> word) {

        // Remove "'" char from begining and end of string
        if (word[0] == '\'') {
            word = word.substr(1, -1);
        }
        if (word[word.size() - 1] == '\'') {
            word = word.substr(0, word.size() - 1);
        }

        if (word.length() == 0)
            continue;

        if (checked.count(word) == 0 && !dico.contain(word)) {
            wrongWords.push_back(WrongWord(word, dico));
            checked.insert(word);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const SpellingChecker& obj) {
    for (const auto& item : obj.wrongWords) {
        out << item;
    }
    return out;
}

