#include "converter.h"
#include <sstream>

int Converter::hexToDecimal(const string hexValue) {
    int decimalValue;
    stringstream(hexValue) >> hex >> decimalValue;
    return decimalValue;
}

string Converter::decimalToHex(const int decimalValue) {
    stringstream ss;
    ss << hex << uppercase << decimalValue;
    return ss.str();
}


vector<string> Converter:: convertToVector(string input) {
    vector<string> convert;
    string element;
    bool flag = false;

    for (char c : input) {
        if (c == ' ' || c == ',') {
            if (!element.empty()) {
                convert.push_back(element);
                element.clear();
            }
            flag = false;
        } else {
            element += c;
            flag = true;
        }
    }

    if (flag) {
        convert.push_back(element);
    }

    return convert;
}


void Converter:: updateProgramCounter(map<string, vector<string>>& instructionMap, string& address) {
    vector<string> command = instructionMap[address];
    int programCounter = Converter::hexToDecimal(address);
    int flag = false;
    for (auto &val : command) {
        if (flag) {
            if (val.length() == 2)
                programCounter += 1;
            if (val.length() == 4)
                programCounter += 2;
        } else
            flag = true;
    }
    address = Converter::decimalToHex(programCounter + 1);
}



