#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;
#ifndef CONVERTER_H
#define CONVERTER_H

class Converter{
    public:
        static vector<string> convertToVector(string input);
        static string decimalToHex(const int decimalValue);
        static int hexToDecimal(const string hexValue);
        static void updateProgramCounter(map<string, vector<string>>& instructionMap, string& address);
};

#endif