#include "GlyphoStack.hpp"

/* 
    folosesc o pereche de liste
    in cazul l-brace, adaug in perechea de liste pozitia l-brace-ului si conditia bool-ului
    in cazul r-brace, daca exista vreun element pe stiva, verific daca este != 0
    daca este, atunci i-ul din for-ul mare din main, il modific pentru a-l reintoarce la instructiunea l-brace
*/
void GlyphoStack::checkBraces(string instrMod, int &i) {
    if (instrMod.compare("0110") == 0) {
        checkExecutionError1Pop(glyStack, i);
        checkList.push_back(make_pair(i, !glyStack.back() == 0));
    }
    if (instrMod.compare("0123") == 0) {
        checkExecutionError1Pop(glyStack, checkList.back().first);
        if (glyStack.back() != 0) i = checkList.back().first - 1;
        checkList.pop_back();
    }
}

int GlyphoStack::switchFunction(string glyCode) {
    // parsare de la cod la int, pentru a putea avea macro-uri
    if (glyCode == "0000") return 0;
    else if (glyCode == "0001") return 1;
    else if (glyCode == "0010") return 2;
    else if (glyCode == "0011") return 3;
    else if (glyCode == "0012") return 4;
    else if (glyCode == "0100") return 5;
    else if (glyCode == "0101") return 6;
    else if (glyCode == "0102") return 7;
    else if (glyCode == "0110") return 8;
    else if (glyCode == "0111") return 9;
    else if (glyCode == "0112") return 10;
    else if (glyCode == "0120") return 11;
    else if (glyCode == "0121") return 12;
    else if (glyCode == "0122") return 13;
    else if (glyCode == "0123") return 14;
    else return -1;
}

string GlyphoStack::macroToCode(int glyCode) {
    if (glyCode == 0) return "0000";
    else if (glyCode == 1) return "0001";
    else if (glyCode == 2) return "0010";
    else if (glyCode == 3) return "0011";
    else if (glyCode == 4) return "0012";
    else if (glyCode == 5) return "0100";
    else if (glyCode == 6) return "0101";
    else if (glyCode == 7) return "0102";
    else if (glyCode == 8) return "0110";
    else if (glyCode == 9) return "0111";
    else if (glyCode == 10) return "0112";
    else if (glyCode == 11) return "0120";
    else if (glyCode == 12) return "0121";
    else if (glyCode == 13) return "0122";
    else if (glyCode == 14) return "0123";
    else return "0000";
}

void GlyphoStack::pushBottom(long long int number)
{
    glyStack.pop_back();
    glyStack.push_front(number);
}

void GlyphoStack::swapNumbersInStack(long long int number1, long long int number2) {
    glyStack.push_back(number1);
    glyStack.push_back(number2);
}

void GlyphoStack::popBottomPushFirst(long long int number) {
    glyStack.erase(glyStack.begin());
    glyStack.push_back(number);
}

void GlyphoStack::addNumbers(long long int number1, long long int number2) {
    glyStack.push_back(number1 + number2);
}

void GlyphoStack::multiplyNumbers(long long int number1, long long int number2) {
    glyStack.push_back(number1 * number2);
}

void GlyphoStack::negateNumber(long long int number) {
    glyStack.push_back(-number);
}

// in functie de numarul de pop-uri, actualizez numerele
void GlyphoStack::popNumbersOutOfStack(int pops) {
    if (pops == 1) {
        pop1 = glyStack.back();
        glyStack.pop_back();
    }
    if (pops == 2) {
        pop1 = glyStack.back();
        glyStack.pop_back();

        pop2 = glyStack.back();
        glyStack.pop_back();
    }
    if (pops == 4) {
        pop1 = glyStack.back();
        glyStack.pop_back();

        pop2 = glyStack.back();
        glyStack.pop_back();

        pop3 = glyStack.back();
        glyStack.pop_back();

        pop4 = glyStack.back();
        glyStack.pop_back();
    }
    if (pops == 0) {
        glyStack.pop_back();
    }
}

void GlyphoStack::operatorsExecute(string glyphoCode, GlyphoInterpreter gi, vector<string>& instr, int& sizeI, int &i, int& base){

    // obtin codul pentru switch
    int code = switchFunction(glyphoCode);

    vector<int> numbers;
    vector<string> parsedString;
    string verifyLRBrace, pop1_string;
    string::size_type sz;

    // verific parantezele sa se respecte
    checkBraces(instr[i], i);

    // daca stiva este goala sau bool-ul returnat este true
    // adica, daca nu exista l-brace sau r-brace deschise
    if (checkList.empty() || checkList.back().second) {
        switch (code) {
            // nu se intampla nimic la nop
            case NOP: {
                break;
            }
            case INPUT: {
                cin >> pop1_string;
                // citesc numarul ca string

                if (base == 10) {
                    // daca baza este 10, verific sa fie un numar valabil in baza 10
                    checkCorrectBase(pop1_string, 10, i);

                    // dau atoi sa il convertesc la un numar
                    pop1 = atoi(pop1_string.c_str());
                    
                    // adaug pe stiva
                    glyStack.push_back(pop1);
                }
                else {
                    // nu am implementat numere foarte mari, asa ca
                    // trebuie sa aiba sub 19 cifre numarul
                    checkCorrectBase(pop1_string, base, i);
                    if (pop1_string.size() <= 19) {
                        // convertesc din orice baza in baza 10
                        pop1 = stoll(pop1_string, &sz, base);

                        // adaug pe stiva
                        glyStack.push_back(pop1);
                    }
                    else {
                        glyStackBigNumbers.push_back(pop1_string);
                    }
                }
                break;
            }
            case ROT: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // scoate un element din varful stivei si il va pune la coada
                pop1 = glyStack.back();
                pushBottom(pop1);
                break;
            }
            case SWAP: {
                // verificare exceptie
                checkExecutionErrorMultiplePops(glyStack, i, 2);

                // interschimba elementele din varful stivei 
                popNumbersOutOfStack(2);
                swapNumbersInStack(pop1, pop2);
                break;
            }
            case PUSH: {
                // va pune in varful stivei un nou element cu valoarea 1
                glyStack.push_back(1);
                break;
            }
            case RROT: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // scoate elementul de la coada stivei si il va pune in varf
                pop1 = glyStack.front();
                popBottomPushFirst(pop1);
                break;
            }
            case DUP: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // duplica elementul din varful stivei
                glyStack.push_back(glyStack.back());
                break;
            }
            case ADD: {
                // verificare exceptie
                checkExecutionErrorMultiplePops(glyStack, i, 2);

                // scoate doua elemente din varful stivei, le calculeaza suma si pune rezultate in varful stivei
                popNumbersOutOfStack(2);
                addNumbers(pop1, pop2);
                break;
            }
            case LBRACE: {
                // va ignora codul pana la paranteza corespunzatoare, daca elementul din varful stivei este 0
                break;
            }
            case OUTPUT: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // scoate elementul din varful stivei si il afiseaza la iesirea standard
                popNumbersOutOfStack(1);
                if (pop1_string.size() <= 19) {
                    if (base == 10) cout << pop1 << endl;
                    else cout << toDeci(to_string(pop1), base) << endl;
                }
                else {
                    pop1_string = glyStackBigNumbers.back();
                    glyStackBigNumbers.pop_back();
                    cout << pop1_string;
                }
                break;
            }
            case MULTIPLY: {
                // verificare exceptie
                checkExecutionErrorMultiplePops(glyStack, i, 2);

                // scoate doua elemente din varful stivei, le calculeaza produsul si pune rezultatul in varful stivei
                popNumbersOutOfStack(2);
                multiplyNumbers(pop1, pop2);
                break;
            }
            case EXECUTE: {
                // vector in care tin minte prima oara cand apare execute
                // pentru ca daca un execute executa un execute si execute-ul de urmeaza cauzeaza eroare
                // trebuie returnata exceptie de la primul execute
                pozExecute.push_back(i);

                // verificare exceptie
                checkExecutionErrorMultiplePops(glyStack, pozExecute.front(), 4);

                // scoate patru elemente din varful stivei si le interpreteaza ca pe o instructiune
                popNumbersOutOfStack(4);
                
                // adaug numerele in vector
                numbers.push_back(pop1);
                numbers.push_back(pop2);
                numbers.push_back(pop3);
                numbers.push_back(pop4);
                for (int i = 0; i < 4; i++) parsedString.push_back(to_string(numbers[i]));
                
                // metoda execute nu poate sa execute lbrace sau rbrace, pentru ca schimba structura codului
                if (gi.parsePattern(parsedString) != "0110" && gi.parsePattern(parsedString) != "0123") {
                    // inserez instructiunea generata de execute imediat dupa ce a fost facuta
                    instr.insert(instr.begin() + i + 1, gi.parsePattern(parsedString));

                    // updatez valoarea size-ului, s-a adaugat o instructiune noua
                    sizeI = instr.size();
                }

                // verific ca in caz de string-ul parsat este 0110 / 0123, sa generez erorile cuvenite
                checkErrorParsedString(gi, parsedString, i);
                parsedString.clear();
                break;
            }
            case NEGATE: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // scoate elementul din varful stivei si pune inapoi inversul lui
                popNumbersOutOfStack(1);
                negateNumber(pop1);
                break;
            }
            case POP: {
                // verificare exceptie
                checkExecutionError1Pop(glyStack, i);

                // scoate un element din varful stivei
                popNumbersOutOfStack(0);
                break;
            }
            case RBRACE: {
                // executia revine la elementul L-brace asociat daca este respectata conditia
                break;
            }
        }
    }
}
