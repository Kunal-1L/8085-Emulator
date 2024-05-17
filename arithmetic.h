#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;
#ifndef ARITHMETIC_H
#define ARITHMETIC_H

class Arithmetic{
    public:
        static void ADD(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void ADC(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void ADI(string operand, vector<int>& flags, unordered_map<string, string>& registers);
        static void ACI(string operand, vector<int>& flags, unordered_map<string, string>& registers);
        static void SUB(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void SBB(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void SUI(string operand, vector<int>& flags, unordered_map<string, string>& registers);
        static void SBI(string operand, vector<int>& flags, unordered_map<string, string>& registers);
        static void DCR(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void INR(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void INX(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void DCX(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void DAD(string operand, vector<int>& flags, unordered_map<string, string>& registers, map<string, string>& directMap);
        static void CMA(vector<int>& flags, unordered_map<string, string>& registers);
};

#endif