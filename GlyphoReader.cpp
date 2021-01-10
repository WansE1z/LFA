#include "GlyphoReader.hpp"

void readGlyphoCode(string file, char& character, vector<string>& instr,
    string &instrStr, vector<string>& instr_concat, GlyphoInterpreter gi)
{
    ifstream fin(file);

    // cat timp exista caractere
    while (fin >> character) {

        // daca este mai mic de 33 sau mai mare de 126, nu este valabil
        if (character < 33 || character > 126) continue;

        // string de tin maxim 4 caractere, sa verific ca este valabil in blocks
        instrStr.push_back(character);

        if (instrStr.length() == 4) {
            // daca este de lungime 4

            for (int i = 0; i < 4; i++) instr_concat.push_back(to_string(instrStr[i]));
            // instructiunea concatenata este un vector de tine fiecare caracter in vector
            // spre exemplu, instr_concat[0] = "a", etc.

            instr.push_back(gi.parsePattern(instr_concat));
            // string-ul concatenat este parsat de catre interpretor, fiind pus in vectorul de instructiuni

            instrStr.clear();
            // dau clear la string, pentru a relua procesul

            instr_concat.clear();
            // dau clear la vector, sa pot da push_back din nou
        }
    }
}
