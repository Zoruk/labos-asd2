#include <iostream>

#include "wordgenerartor.h"
#include "worddictionarystl.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    WordGenerartor w("Super Salut");
    WordDictionary* d = new WordDictionarySTL;

    d->load("Data/dictionary.txt", true);

    for (std::string v : {"hello", "accordance", "Meliae", "Poney"}) {
        cout << v << " " << boolalpha << d->contain(v) << endl;
    }
    cout << d->size() << endl;

    /*for (auto s : w.getWords()) {
        cout << s << endl;
    }*/

    delete d;
    return 0;
}
