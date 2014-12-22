#include <iostream>
#include <sstream>
#include <fstream>

#include "worddictionarystl.h"
#include "worddictionarytst.h"

#include "spellingchecker.h"
#include "wordgenerartor.h"
#include "wrongword.h"
#include "ternarysearchtrie.h"

using namespace std;

int main()
{
    WordDictionaryTST dTST;
    WordDictionarySTL dSTL;

    dTST.load("Data/dictionary.txt", true);
    dSTL.load("Data/dictionary.txt", true);

    cout << dTST.size() << " " << dSTL.size() << endl;

    SpellingChecker spellingcheckerTST("Data/input_sh.txt", dTST);
    SpellingChecker spellingcheckerSTL("Data/input_sh.txt", dSTL);

    ofstream resultTST("result_tst.txt", ofstream::trunc | ofstream::out),
             resultSTL("result_stl.txt", ofstream::trunc | ofstream::out);
    resultSTL << spellingcheckerSTL;
    resultTST << spellingcheckerTST;

    return 0;
}
