#include "wordgenerartor.h"

#include <cstring>
#include <sstream>

#include <iostream>

const char* WordGenerartor::letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ'";
const WordGenerartor::size_type WordGenerartor::NBLETTERS = strlen(WordGenerartor::letters);

WordGenerartor::WordGenerartor(const std::string word) : word(word), wordLength(word.length())
{
    removeOneLetter();
    addOneLetter();
    changeOneLetter();
    swapTwoLetter();
}

void WordGenerartor::removeOneLetter()
{
    std::string s;
    s.reserve(wordLength - 1);
    for (size_type i = 0; i < wordLength; ++i) {
        s.append(word.substr(0, i)).append(word.substr(i + 1, wordLength - i - 1));
        //std::cout << s << std::endl;
        words.push_back(s);
        s.clear();
    }
}

void WordGenerartor::addOneLetter() {
    std::string s;
    s.reserve(wordLength + 1);

    for (size_type j = 0; j < NBLETTERS; ++j) {
        for (size_type i = 0; i <= wordLength; ++i) {
            s.append(word.substr(0, i))
                    .push_back(letters[j]);
            s.append(word.substr(i, wordLength - i));
            //std::cout << s << std::endl;
            words.push_back(s);
            s.clear();
        }
    }
}

void WordGenerartor::changeOneLetter() {
    std::string s;
    s.reserve(wordLength + 1);

    for (size_type j = 0; j < NBLETTERS; ++j) {
        for (size_type i = 0; i < wordLength; ++i) {
            s.append(word.substr(0, i)).push_back(letters[j]);
            s.append(word.substr(i + 1, wordLength - i - 1));
            //std::cout << s << std::endl;
            words.push_back(s);
            s.clear();
        }
    }
}

void WordGenerartor::swapTwoLetter() {
    std::string s;
    s.reserve(wordLength);

    for (size_type i = 0; i < wordLength - 1; ++i) {
        s = word;
        std::swap(s[i], s[i+1]);
        //std::cout << s << std::endl;
        words.push_back(s);
    }

}
