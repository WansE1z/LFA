#include "GlyphoError.hpp"

// -1 - eroare sintactica
// -2 - exceptie(eroare la rulare)

// in enunt se preciza ca daca string-ul parsat de catre execute o sa fie 0110 sau 0123 nu se va intampla nimic
// aparent, se intampla, asa ca tratez si acest caz conform checker-ului
void checkErrorParsedString(GlyphoInterpreter gi, vector<string> parsedString, int i) {
    if (gi.parsePattern(parsedString) == "0110") {
        cerr << "Exception:" << i << endl;
        exit(-2);
    }
    if (gi.parsePattern(parsedString) == "0123") {
        cerr << "Exception:" << i << endl;
        exit(-2);
    }
}

// functie care verifica lungimea ramasa a string-ului sa nu fie mai mica de 4 sau diferita de 0
// teoretic un cod dat de la input prost inseamna ca are size-ul diferit de 4, sau diferit de 0
void checkSyntaxError(string instruction_string, int sizeI) {
    if (instruction_string.size() < 4 && instruction_string.size() != 0) {
        cerr << "Error:" << sizeI << endl;
        exit(-1);
    }
}

void checkParanClosed(vector<string> braceVect)
{
    stack <string> s;

    for (long unsigned int i = 0; i < braceVect.size(); i++) {
        if (braceVect[i] == "0110" || braceVect[i] == "0123") {
            // daca gasesc l-brace, push pe stack
            if (braceVect[i] == "0110") {
                s.push(braceVect[i]);
            }
            else
            { // in caz de parantezele sunt valide, nu se poate ca stiva sa fie goala
                if (s.empty()) {
                    cerr << "Error:" << i << endl;
                    exit(-1);
                }
                else {
                    // daca contine o paranteza inchisa, dau pop din stack la paranteza deschisa
                    if (braceVect[i] == "0123" && s.top() == "0110") {
                        s.pop();
                    }
                    else {
                        // daca nu, inseamna ca parantezele nu corespund
                        cerr << "Error:" << i << endl;
                        exit(-1);
                    }
                }
            }
        }
    }
    if (!s.empty()) {
        // daca stiva nu este goala, inseamna ca a ramas o paranteza sau mai multe pe stiva
        // deci afisez ultima linie, ca in checker
        cerr << "Error:" << braceVect.size() << endl;
        exit(-1);
    }
}

// pentru operatiile pop,rot,rrot,dup,l-brace,output
void checkExecutionError1Pop(list<long long int> glyStack, int i) {
    if (glyStack.empty()) {
        cerr << "Exception:" << i << endl;
        exit(-2);
    }
}

// pentru operatiile add, multiply, swap, execute
void checkExecutionErrorMultiplePops(list<long long int> glyStack, int i, int pops) {
    if (glyStack.size() < (long unsigned int)pops) {
        cerr << "Exception:" << i << endl;
        exit(-2);
    }
}

void checkCorrectBase(string str, int base, int i)
{
    if (base <= 10)
    {
        // daca baza este mai mica de 10
        // atunci, caracterul trebuie sa fie 0 -> base - 1
        // daca nu se afla intre aceste margini, inseamna ca nu este in baza corespunzatoare
        for (long unsigned int j = 0; j < str.length(); j++)
            if (!(str[j] >= '0' && str[j] < ('0' + base))) {
                if (str[j] == '-') continue;
                cerr << "Exception:" << i << endl;
                exit(-2);
            }
    }
    else
    {
        // pentru cele mai mari ca 10, includem si caracterele A...
        for (long unsigned int j = 0; j < str.length(); j++)
            if (!((str[j] >= '0' &&
                str[j] < ('0' + base)) ||
                (str[j] >= 'A' &&
                    str[j] < ('A' + base - 10))
                )) {
                if (str[j] == '-') continue;
                cerr << "Exception:" << i << endl;
                exit(-2);
            }
    }
}

int val(char c)
{
    if (c >= '0' && c <= '9')
        return (int)c - '0';
    else
        return (int)c - 'A' + 10;
}

int toDeci(string str, int base)
{
    int len = str.length();
    int power = 1; // Initialize power of base 
    int num = 0;  // Initialize result 
    int i;

    // Decimal equivalent is str[len-1]*1 + 
    // str[len-2]*base + str[len-3]*(base^2) + ... 
    for (i = len - 1; i >= 0; i--)
    {
        // A digit in input number must be 
        // less than number's base 
        if (val(str[i]) >= base)
        {
            return -1;
        }

        num += val(str[i]) * power;
        power = power * base;
    }

    return num;
}
