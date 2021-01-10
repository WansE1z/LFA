#include "GlyphoInterpreter.hpp"
#include "GlyphoStack.hpp"
#include "GlyphoReader.hpp"

int main(int argc, char* argv[]) {
    GlyphoInterpreter gi; // interpretorul
    GlyphoStack gs; // stiva
    vector<string> instr, instr_concat; // vectorul de instructiuni respectiv cel concatenat
    string instrStr, instrMod; // string-ul instructiunii, care tine fiecare "linie" de 4 caractere
    int sizeI, base; // marimea instructiunii, baza
    char character;

    readGlyphoCode(argv[1], character, instr, instrStr, instr_concat, gi);
    // citesc codul glypho si il adaug in vectorul de instructiuni

    sizeI = instr.size();
    // updatez size-ul vectorului de instructiuni
    // tin intr-o variabila size-ul pentru ca la anumite operatii spre exemplu execute, size-ul se modifica

    checkSyntaxError(instrStr, sizeI);
    // verific daca exista erori de sintaxa spre exemplu string-ul instrStr nu contine 4 caractere sau 0

    checkParanClosed(instr);
    // ma asigur ca parantezele sunt inchise corect, sa nu existe cazuri -> "(" "(()" ")", etc.

    if (argc == 3) base = atoi(argv[2]);
    if (argc == 2) base = 10;
    // default este baza 10, daca totusi se da de la consola, sa fie citita baza

    // parcurg in toate instructiuniile
    // tin minte instructiunea intr-un string pentru ca atunci cand se revine la lbrace, i-ul va fi modificat
    // execut fiecare operator din vectorul de instructiuni
    for (int i = 0; i < sizeI; i++) {
        instrMod = instr[i];
        gs.operatorsExecute(instrMod, gi, instr, sizeI, i, base);
    }

    return 0;
}
