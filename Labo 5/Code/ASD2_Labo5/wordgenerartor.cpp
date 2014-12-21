#include "wordgenerartor.h"

#include <cstring>
#include <sstream>

#include <iostream>

const char* WordGenerartor::letters = "abcdefghijklmnopqrstuvwxyz'";
const WordGenerartor::size_type WordGenerartor::NBLETTERS = strlen(WordGenerartor::letters);

WordGenerartor::WordGenerartor(const std::string word) : word(word), wordLength(word.length())
{
}

std::list<std::string> WordGenerartor::removeOneLetter()
{
    std::list<std::string> words;
    std::string s;
    s.reserve(wordLength - 1);
    for (size_type i = 0; i < wordLength; ++i) {
        s.append(word.substr(0, i)).append(word.substr(i + 1, wordLength - i - 1));
        //std::cout << s << std::endl;
        words.push_back(s);
        s.clear();
    }
    return words;
}

std::list<std::string> WordGenerartor::addOneLetter() {
    std::list<std::string> words;
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
    return words;
}

std::list<std::string> WordGenerartor::changeOneLetter() {
    std::list<std::string> words;
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

    return words;
}

std::list<std::string> WordGenerartor::swapTwoLetter() {
    std::list<std::string> words;
    std::string s;
    s.reserve(wordLength);

    for (size_type i = 0; i < wordLength - 1; ++i) {
        s = word;
        std::swap(s[i], s[i+1]);
        //std::cout << s << std::endl;
        words.push_back(s);
    }
    return words;
}

std::list<std::string> WordGenerartor::getAllWords() {
    std::list<std::string> words, tmp;
    words = removeOneLetter();

    tmp = addOneLetter();
    words.insert(words.end(), tmp.begin(), tmp.end());

    tmp = changeOneLetter();
    words.insert(words.end(), tmp.begin(), tmp.end());

    tmp = swapTwoLetter();
    words.insert(words.end(), tmp.begin(), tmp.end());

    return words;
}
