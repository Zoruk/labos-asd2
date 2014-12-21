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

    WrongWord wrongword("lates", d);
    cout << wrongword;
    cout << d.size() << endl;

    SpellingChecker spellingchecker("Data/input_sh.txt", d);

    return 0;
}
