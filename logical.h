#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;

#ifndef LOGICAL_H
#define LOGICAL_H

class Logical{
    public:
        static void ANA(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void ANI(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void ORA(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void ORI(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void XRA(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void XRI(string operand, vector<int>& flags, unordered_map<string, string>& registers,map<string, string>& directMap);
        static void CMP(string operand, map<string, string>& directMap, vector<int>& flags,unordered_map<string, string>& registers);
};

#endif