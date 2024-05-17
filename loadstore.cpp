#include "loadstore.h"
#include "converter.h"

void Loadstore::MOV(string reg1, string reg2, map<string,string>& directMap, unordered_map<string,string>& registers) {
    if (reg2 == "M") {
        string indirectMemoryAddress = registers["H"] + registers["L"];
        registers[reg1] = directMap[indirectMemoryAddress];
    } else if (reg1 == "M") {
        string indirectMemoryAddress = registers["H"] + registers["L"];
        directMap[indirectMemoryAddress] = registers[reg2];
    } else {
        registers[reg1] = registers[reg2];
    }
}

void Loadstore::MVI(string reg, string data, map<string,string>& directMap, unordered_map<string,string>& registers) {
    if (reg == "M") {
        string indirectMemoryAddress = registers["H"] + registers["L"];
        directMap[indirectMemoryAddress] = data;
    } else {
        registers[reg] = data;
    }
}

void Loadstore::LXI(string regpair,string address,map<string,string>&directMap,unordered_map<string,string>&registers)
{
    if(regpair=="B")
    {
        registers["B"]=address.substr(0,2);
        registers["C"]=address.substr(2,4);
    }
    else if(regpair=="D")
    {
        registers["D"]=address.substr(0,2);
        registers["E"]=address.substr(2,4);
    }
    else if(regpair=="H")
    {
        registers["H"]=address.substr(0,2);
        registers["L"]=address.substr(2,4);
    }
}

void Loadstore::LDA(string address, map<string,string>& directMap, unordered_map<string,string>& registers) {
    registers["A"] = directMap[address];
}

void Loadstore::STA(string address, map<string,string>& directMap, unordered_map<string,string>& registers) {
    directMap[address] = registers["A"];
}

void Loadstore:: LHLD(string address, map<string,string>& directMap, unordered_map<string,string>& registers) {
    int loweraddress = Converter::hexToDecimal(address);
    int higheraddress = loweraddress + 1;
    string higheradd = Converter::decimalToHex(higheraddress);
    registers["H"] = directMap[higheradd];
    registers["L"] = directMap[address];
}

void Loadstore::SHLD(string address, map<string,string>& directMap, unordered_map<string,string>& registers) {
    int loweraddress = Converter::hexToDecimal(address);
    int higheraddress = loweraddress + 1;
    string higheradd = Converter::decimalToHex(higheraddress);
    directMap[address] = registers["L"];
    directMap[higheradd] = registers["H"];
}

void Loadstore::LDAX(string regpair, map<string,string>& directMap, unordered_map<string,string>& registers) {
    string indirectmemory;
    bool flag = false;
    if (regpair == "B") {
        indirectmemory = registers["B"] + registers["C"];
        flag = true;
    } else if (regpair == "D") {
        indirectmemory = registers["D"] + registers["E"];
        flag = true;
    } else if (regpair == "H") {
        indirectmemory = registers["H"] + registers["L"];
        flag = true;
    }
    if (flag) {
        registers["A"] = directMap[indirectmemory];
    }
}

void Loadstore::STAX(string regpair, map<string,string>& directMap, unordered_map<string,string>& registers) {
    string indirectmemory;
    bool flag = false;
    if (regpair == "B") {
        indirectmemory = registers["B"] + registers["C"];
        flag = true;
    } else if (regpair == "D") {
        indirectmemory = registers["D"] + registers["E"];
        flag = true;
    } else if (regpair == "H") {
        indirectmemory = registers["H"] + registers["L"];
        flag = true;
    }
    if (flag) {
        directMap[indirectmemory] = registers["A"];
    }
}

void Loadstore::XCHG(map<string,string>& directMap, unordered_map<string,string>& registers) {
    swap(registers["D"], registers["H"]);
    swap(registers["E"], registers["L"]);
}
