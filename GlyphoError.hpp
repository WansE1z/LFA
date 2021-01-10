#include "GlyphoInterpreter.hpp"

#pragma once
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void checkErrorParsedString(GlyphoInterpreter gi, vector<string> parsedString, int sizeI);

void checkSyntaxError(string instruction_string, int sizeI);

void checkExecutionError1Pop(list<long long int> glyStack, int i);

void checkExecutionErrorMultiplePops(list<long long int> glyStack, int i, int pops);

void checkCorrectBase(string str, int base, int i);

void checkParanClosed(vector<string> instr);

int val(char c);

int toDeci(string str, int base);
