#include "GlyphoInterpreter.hpp"
#include <map>

/*
    codul functioneaza astfel
    daca elementul nu se afla in map, il introduc in map cu contorul curent si cheia, unde cheia este string-ul respectiv
    dupa ce este inserat, incrementez contorul
    {"ab" ,"ba" ,"ab" ,"abc"} ->
    gaseste ab, nu se afla in map, deci adauga {"ab", 0}, incrementeaza contorul
    gaseste ba, nu se afla in map, deci adauga {"ba", 1}, incrementeaza contorul
    gaseste ab, se afla in map, nu face nimic
    gaseste abc, nu se afla in map, deci adauga {"abc", 2}, incrementeaza contorul, dar nu are efect, pentru ca nu mai urmeaza elemente
*/
string GlyphoInterpreter::parsePattern(vector<string>& codeString) {
    map<string, int> mp;
    vector<int> cod;
    string codFinal;
    int cnt = 0, characterCode;

    for (auto& cs : codeString) {
        if (mp.find(cs) == mp.end()) {
            mp.insert(make_pair(cs, cnt));
            // cs reprezinta fiecare string
            // cnt este un contor cu care tin evidenta la codul de o sa iasa

            cnt++;
            // incrementez contorul numai daca nu este gasit elementul
        }
    }

    for (auto& cs : codeString) {
        // mp.find(cs)->first = cheia
        // mp.find(cs)->second = valoarea

        characterCode = mp.find(cs)->second;

        // tin intr-un vector de int-uri codul transformat pentru interpretor
        cod.push_back(characterCode);
    }

    for (auto& c : cod) {
        // modificare intr-un string
        codFinal += to_string(c);
    }

    return codFinal;
}
