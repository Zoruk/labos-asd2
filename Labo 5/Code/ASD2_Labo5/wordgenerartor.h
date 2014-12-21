#ifndef WORDGENERARTOR_H
#define WORDGENERARTOR_H

#include <list>
#include <string>

class WordGenerartor
{
private:
    const std::string word;
    typedef std::string::size_type size_type;
    const size_type wordLength;
    static const char* letters;
    static const size_type NBLETTERS;

public:
    WordGenerartor(const std::string word);

    std::list<std::string> removeOneLetter();
    std::list<std::string> addOneLetter();
    std::list<std::string> changeOneLetter();
    std::list<std::string> swapTwoLetter();

    std::list<std::string> getAllWords();
};
#endif // WORDGENERARTOR_H
