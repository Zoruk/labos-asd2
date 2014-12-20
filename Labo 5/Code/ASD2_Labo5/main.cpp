#include <iostream>

#include "wordgenerartor.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    WordGenerartor w("Super Salut");
    for (auto s : w.getWords()) {
        cout << s << endl;
    }
    return 0;
}

