#include "fetch.h"
#include "loadstore.h"
#include "arithmetic.h"
#include "logical.h"

void Fetch::fetchingFunctions(std::string startingAddress, std::map<std::string, std::vector<std::string>>& instructionMap, std::map<std::string, std::string>& directMap, std::unordered_map<std::string, std::string>& registers, std::vector<int>& flags) {
    auto addr = instructionMap.find(startingAddress);
    for (auto address = addr; address != instructionMap.end(); address++) {
        // Based on the opcode, execute the corresponding instruction
        if (address->second[0] == "MOV") {
            Loadstore::MOV(address->second[1], address->second[2], directMap, registers);
        } 
        else if (address->second[0] == "MVI") {
            Loadstore::MVI(address->second[1], address->second[2], directMap, registers);
        } 
        else if (address->second[0] == "LXI") {
            Loadstore::LXI(address->second[1], address->second[2], directMap, registers);
        } 
        else if (address->second[0] == "LDA") {
            Loadstore::LDA(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "STA") {
            Loadstore::STA(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "LHLD") {
            Loadstore::LHLD(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "SHLD") {
            Loadstore::SHLD(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "LDAX") {
            Loadstore::LDAX(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "STAX") {
            Loadstore::STAX(address->second[1], directMap, registers);
        } 
        else if (address->second[0] == "XCHG") {
            Loadstore::XCHG(directMap, registers);
        } 
        else if (address->second[0] == "JMP") {
            Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
            return;
        } 
        else if (address->second[0] == "JC") {
            if(flags[7]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
                return;
            }
        } 
        else if (address->second[0] == "JNC") {
            if(!flags[7]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
                return;
            }
        } 
        else if (address->second[0] == "JZ") {
            if(flags[1]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);  
                return;
            }
        }
        else if (address->second[0] == "JNZ") {
            if(!flags[1]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);   
                return;
            }
        }
        else if (address->second[0] == "JPE") {
            if(flags[5]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
                return;
            }
        }
        else if (address->second[0] == "JPO") {
            if(!flags[5]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);    
                return;
            }
        }
        else if (address->second[0] == "JM") {
            if(flags[0]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags); 
                return;
            }
        }
        else if (address->second[0] == "JP") {
            if(!flags[0]){
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags); 
                return;
            }
        }
        else if (address->second[0] == "ADD") {
            Arithmetic::ADD( address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "ADI") {
            Arithmetic::ADI( address->second[1], flags, registers); 
        }
        else if (address->second[0] == "SUB") {
            Arithmetic::SUB( address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "SUI") {
            Arithmetic::SUI( address->second[1], flags, registers); 
        }
        else if (address->second[0] == "DCR") {
            Arithmetic::DCR( address->second[1], flags, registers, directMap); 
        }
        else if (address->second[0] == "INR") {
            Arithmetic::INR( address->second[1], flags, registers, directMap); 
        }
        else if (address->second[0] == "INX") {
            Arithmetic::INX( address->second[1], flags, registers, directMap); 
        }
        else if (address->second[0] == "DCX") {
            Arithmetic::DCX( address->second[1], flags, registers, directMap); 
        }
        else if (address->second[0] == "DAD") {
            Arithmetic::DAD( address->second[1], flags, registers, directMap); 
        }
        else if (address->second[0] == "CMA") {
            Arithmetic::CMA(flags, registers); 
        }
        else if (address->second[0] == "ADC") {
            Arithmetic::ADC(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "ACI") {
            Arithmetic::ACI(address->second[1], flags, registers);
        }
        else if (address->second[0] == "SBB") {
            Arithmetic::SBB(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "SBI") {
            Arithmetic::SBI(address->second[1], flags, registers);
        }
        else if (address->second[0] == "CMP") {
            Logical::CMP(address->second[1], directMap, flags, registers);
        }
        else if (address->second[0] == "ANA") {
            Logical::ANA(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "ANI") {
            Logical::ANI(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "ORA") {
            Logical::ORA(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "ORI") {
            Logical::ORI(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "XRA") {
            Logical::XRA(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "XRI") {
            Logical::XRI(address->second[1], flags, registers, directMap);
        }
        else if (address->second[0] == "CALL") {
            Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
        }
        else if (address->second[0] == "CC") {
            if(flags[7])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);
        }
        else if (address->second[0] == "CNC") {
            if(!flags[7])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);  
        }
        else if (address->second[0] == "CZ") {
            if(flags[1])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "CNZ") {
            if(!flags[1])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "CPE") {
            if(flags[5])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "CPO") {
            if(!flags[5])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "CM") {
            if(flags[0])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "CP") {
            if(!flags[0])
                Fetch::fetchingFunctions(address->second[1], instructionMap, directMap, registers, flags);        
        }
        else if (address->second[0] == "RET") {
            return;
        }
        else if (address->second[0] == "RC") {
            if(!flags[7])
                return;
        }
        else if (address->second[0] == "RNC") {
            if(!flags[7])
                return;
        }
        else if (address->second[0] == "RZ") {
            if(flags[1])
                return;
        }
        else if (address->second[0] == "RNZ") {
            if(!flags[1])
                return;
        }
        else if (address->second[0] == "RPE") {
            if(flags[5])
                return;
        }
        else if (address->second[0] == "RPO") {
            if(!flags[5])
                return;
        }
        else if (address->second[0] == "RM") {
            if(flags[0])
                return;
        }
        else if (address->second[0] == "RP") {
            if(!flags[0])
                return;
        }
        else if (address->second[0] == "HLT") {
            return;
        }
    }
}
