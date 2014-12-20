#ifndef WORDGENERARTOR_H
#define WORDGENERARTOR_H

#include <list>
#include <string>

class WordGenerartor
{
private:
    std::list<std::string> words;
    const std::string word;
    typedef std::string::size_type size_type;
    const size_type wordLength;
    static const char* letters;
    static const size_type NBLETTERS;

    void removeOneLetter();
    void addOneLetter();
    void changeOneLetter();
    void swapTwoLetter();


public:
    WordGenerartor(const std::string word);
    const std::list<std::string>& getWords() { return words; }
};

#endif // WORDGENERARTOR_H
