#pragma once
#include <string>
#include <fstream>
#include <vector>
#include "GlyphoInterpreter.hpp"
#include "GlyphoError.hpp"
#include "GlyphoStack.hpp"

using namespace std;

void readGlyphoCode(string file, char& character, vector<string>& instr,
    string& instrStr, vector<string>& instr_concat, GlyphoInterpreter gi);
