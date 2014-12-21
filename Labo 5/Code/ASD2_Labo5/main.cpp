#include <iostream>


#include "worddictionarystl.h"
#include "spellingchecker.h"
#include "wordgenerartor.h"
#include "wrongword.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    WordGenerartor w("Super Salut");
    WordDictionarySTL d; ;

    d.load("Data/dictionary.txt", true);

    for (std::string v : {"hello", "accordance", "Meliae", "Poney"}) {
        cout << v << " " << boolalpha << d.contain(v) << endl;
    }

    string word = "'lol'";
    if (word[0] == '\'') {
        word = word.substr(1, -1);
    }
    if (word[word.size() - 1] == '\'') {
        word = word.substr(0, word.size() - 1);
    }
    cout << word << endl;

    //WrongWord wrongword("lates", d);
    //cout << wrongword;
    cout << d.size() << endl;

    SpellingChecker spellingchecker("Data/input_sh.txt", d);

    std::cout << spellingchecker;
    return 0;
}
