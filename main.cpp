#include "arithmetic.h"
#include "converter.h"
#include "fetch.h"
#include "loadstore.h"
#include "logical.h"
using namespace std;
#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<fstream>


class Emulator{
    public:
        vector<int> flags;
        unordered_map<string, string> registers;
        map<string, vector<string>> instructionMap;
        map<string, string> directMap;
        string address;
        string startingAddress;
    public:
        Emulator(): flags(7,0){   
            cout << "RAM ADDRESS: ";
            cin >> address;
            startingAddress = address;
            transform(address.begin(), address.end(), address.begin(), ::toupper);
        }
        void programInput(){
            string instruction;
            getchar();
            while (true) {
                cout << address << ": ";
                getline(cin, instruction);
                if(instruction == "q")
                    break;
                instructionMap[address] = Converter::convertToVector(instruction);
                Converter::updateProgramCounter(instructionMap, address);
            }
        }
        void check()
        {
            int choice=0;
            cout<<"If you want to input through file press 1, else press 2: ";
            cin>>choice;
            if(choice==1)
            {
                string fileName;
                cout << "Enter Program File Name: ";
                cin >> fileName;
                programInputbyfile(fileName);
                cout << "Enter Input File Name(if any): ";
                cin >> fileName;
                inputInstructionsinfile(fileName);
            }
            else
            {
                programInput();
                inputInstructions();
            }
            
        }
        void programInputbyfile(string fileName)
        {
            ifstream inFile(fileName);
            string instruction;
            while(getline(inFile,instruction))
            {
                instructionMap[address] = Converter::convertToVector(instruction);
                Converter::updateProgramCounter(instructionMap, address);
            }
        }
        void inputInstructionsinfile(string fileName)
        {
            ifstream inputinfile(fileName);
            string input;
            while(getline(inputinfile,input))
            {
                vector<string> temp = Converter::convertToVector(input);
                //cout<<"check"<<endl;
                address = temp[0];
                directMap[address] = temp[1];
                address = Converter::decimalToHex(Converter::hexToDecimal(address) + 1);
            }
        }
        void inputInstructions(){
            do {
                char ch;
                string instruction;
                cout << "Enter 'q' to quit ";
                ch = getchar();
                cin.ignore();
                bool flag = false;
                while (ch != 'q') {
                    flag = true;
                    getline(cin, instruction);
                    if (instruction.length() == 0) {
                        break;
                    } else if (instruction.length() == 2) {
                        directMap[address] = instruction;
                    } else {
                        vector<string> temp = Converter::convertToVector(instruction);
                        if (temp.size() < 3)
                            break;
                        address = temp[1];
                        directMap[address] = temp[2];
                    }
                    address = Converter::decimalToHex(Converter::hexToDecimal(address) + 1);
                    cout << address << ": ";
                }
                if (!flag)
                    break;
            } while (true);
        }
        void execute(){
            Fetch::fetchingFunctions(startingAddress, instructionMap, directMap, registers, flags) ;
        }
        void output(){
            cout << "Direct Map Contents:" << endl;
            for (const auto& entry : directMap) {
                cout << entry.first << " -> " << entry.second << endl;
            }
            cout << "Registers Contents:" << endl;
            for (const auto& entry : registers) {
                cout << entry.first << " -> " << entry.second << endl;
            }
            cout << "Flags Contents:" << endl;
            cout << "Carry Flag: " << flags[7] << endl;
            cout << "Zero Flag: " << flags[1] << endl;
            cout << "Sign Flag: " << flags[0] << endl;
            cout << "Auxiliary Carry Flag: " << flags[3] << endl;
            cout << "Parity Flag: " << flags[5] << endl;
        }
};
int main() {
    
    Emulator obj = Emulator();
    obj.check();
    obj.execute();
    obj.output();
    return 0;
}




