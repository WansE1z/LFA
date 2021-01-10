#pragma once

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <list>
#include "GlyphoInterpreter.hpp"
#include "GlyphoError.hpp"

using namespace std;

#define NOP 0
#define INPUT 1
#define ROT 2
#define SWAP 3
#define PUSH 4
#define RROT 5
#define DUP 6
#define ADD 7
#define LBRACE 8
#define OUTPUT 9
#define MULTIPLY 10
#define EXECUTE 11
#define NEGATE 12
#define POP 13
#define RBRACE 14

using namespace std;

class GlyphoStack {
public:
	list<long long int> glyStack;
	list<pair<int, bool>> checkList;
	list<int> pozExecute;
	list<string> glyStackBigNumbers;
	long long int pop1, pop2, pop3, pop4;
	int nrExecs = 0;

	void checkBraces(string instrMod, int& i);

	int switchFunction(string glyCode);

	string macroToCode(int glyCode);

	void pushBottom(long long int number);
	void swapNumbersInStack(long long int number, long long int number2);
	void popBottomPushFirst(long long int number);
	void addNumbers(long long int number1, long long int number2);
	void multiplyNumbers(long long int number1, long long int number2);
	void negateNumber(long long int number);
	void popNumbersOutOfStack(int pops);
	void operatorsExecute(string glyCode, GlyphoInterpreter gi, vector<string>& instr, int& sizeI, int &i, int& base);
};