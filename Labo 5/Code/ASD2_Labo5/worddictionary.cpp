#include "worddictionary.h"

#include <fstream>
#include <cctype>
#include <algorithm>

#include <iostream>

WordDictionary::WordDictionary()
{
}

WordDictionary::~WordDictionary()
{
}

void WordDictionary::load(const std::string file, bool lowercase)
{
    std::ifstream fstream(file);
    std::string s;
    while (std::getline(fstream, s)) {
        // Dictionary is windows style ...
        s.erase(std::remove_if(s.begin(), s.end(), iscntrl), s.end());
        if (lowercase)
            for (char& c : s)
                c = tolower(c);
        add(s);
    }
    fstream.close();
}
