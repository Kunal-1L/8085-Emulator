#include<string>
#include<map>
#include<vector>
#include<unordered_map>
using namespace std;

#ifndef LOADSTORE_H
#define LOADSTORE_H

class Loadstore{
    public:
        static void MOV(string reg1, string reg2, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void MVI(string reg, string data, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void LXI(string regpair, string address, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void LDA(string address, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void STA(string address, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void LHLD(string address, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void SHLD(string address, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void LDAX(string regpair, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void STAX(string regpair, map<string,string>& directMap, unordered_map<string,string>& registers);
        static void XCHG(map<string,string>& directMap, unordered_map<string,string>& registers);
};

#endif