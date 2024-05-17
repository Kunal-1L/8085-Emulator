#include "arithmetic.h"
#include "converter.h"

void Arithmetic::ADD(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int operandValue, accumulatorValue;
    
    accumulatorValue = Converter::hexToDecimal(registers["A"]);

    if (operand == "M") {
        std::string indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }

    int result = accumulatorValue + operandValue;

    flags[7] = (result > 255) ? 1 : 0; // Carry flag

    int lowerNibbleAcc = accumulatorValue & 0xF;
    int lowerNibbleOperand = operandValue & 0xF;
    flags[3] = ((lowerNibbleAcc + lowerNibbleOperand) > 15) ? 1 : 0; // Auxiliary Carry flag

    result %= 256;

    registers["A"] = Converter::decimalToHex(result);
    if (registers["A"].length() == 1) {
        registers["A"] = "0" + registers["A"]; 
    }
    
    flags[1] = (result == 0) ? 1 : 0; // Zero flag

    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Arithmetic::ADC(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    std::string carry = "00";
    if(flags[7])
        carry = "01";
    ADD(operand, flags, registers, directMap);
    if(carry == "01")
        ADI(carry, flags, registers);
}

void Arithmetic::ADI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {
    
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue = Converter::hexToDecimal(operand);

    int result = accumulatorValue + operandValue;

    flags[7] = (result > 255) ? 1 : 0; // Carry flag

    int lowerNibbleAcc = accumulatorValue & 0xF;
    int lowerNibbleOperand = operandValue & 0xF;
    flags[3] = ((lowerNibbleAcc + lowerNibbleOperand) > 15) ? 1 : 0; // Auxiliary Carry flag

    result %= 256;

    registers["A"] = Converter::decimalToHex(result);
    if (registers["A"].length() == 1) 
        registers["A"] = "0" + registers["A"]; 

    flags[1] = (result == 0) ? 1 : 0; // Zero flag

    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Arithmetic::ACI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {
    
    std::string carry = "00";
    if(flags[7])
        carry = "01";
    ADI(operand, flags, registers);
    if(carry == "01")
        ADI(carry, flags, registers);
}

void Arithmetic::SUB(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int operandValue;
    
    if (operand == "M") {
        std::string indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }

    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int lowerNibbleAcc = accumulatorValue & 0xF; 
    int lowerNibbleOperand = operandValue & 0xF; 

    int result = accumulatorValue - operandValue;

    flags[7] = (accumulatorValue < operandValue) ? 1 : 0; // Carry flag

    flags[1] = (result == 0) ? 1 : 0; // Zero flag

    flags[3] = (lowerNibbleAcc < lowerNibbleOperand) ? 1 : 0; // Auxiliary Carry flag

    if (result < 0) {
        result += 256; 
    }
    
    result %= 256;
    
    std::string temp = Converter::decimalToHex(result); 
    registers["A"] = (temp.length() == 1) ? "0" + temp : temp;

    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Arithmetic::SBB(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    std::string borrow = "00";
    if(flags[7])
        borrow = "01";
    SUB(operand, flags, registers, directMap);
    if(borrow == "01")
        SUI(borrow, flags, registers);
}

void Arithmetic::SUI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {

    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue = Converter::hexToDecimal(operand);

    int lowerNibbleAcc = accumulatorValue & 0xF;
    int lowerNibbleOperand = operandValue & 0xF;

    int result = accumulatorValue - operandValue;

    flags[7] = (accumulatorValue < operandValue) ? 1 : 0; // Carry flag
    
    flags[3] = (lowerNibbleAcc < lowerNibbleOperand) ? 1 : 0; // Auxiliary Carry flag

    flags[1] = (result == 0) ? 1 : 0; // Zero flag

    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    if (result < 0) {
        result += 256; 
    }

    result %= 256;

    std::string resultHex = Converter::decimalToHex(result); 
    registers["A"] = (resultHex.length() == 1) ? "0" + resultHex : resultHex;

    int parity = 0;
    for (int x = result; x; x &= (x - 1)) {
        parity ^= 1;
    }
    flags[5] = !parity; // Parity flag

}

void Arithmetic::SBI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {
    
    std::string borrow = "00";
    if(flags[7])
        borrow = "01";
    SUI(operand, flags, registers);
    if(borrow == "01")
        SUI(borrow, flags, registers);
}

void Arithmetic::DCR(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int operandValue;
    std::string indirectMemoryAddress;
    
    if (operand == "M") {
        indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }
    
    int result = operandValue - 1;

    if (result < 0) {
        result += 256;
    }

    flags[3] = (operandValue == 0x00) ? 1 : 0; // if lowerNibble is 0 borrow required

    result %= 256;
    std::string resultHex = Converter::decimalToHex(result); 
    
    if (operand == "M") {
        directMap[indirectMemoryAddress] = (resultHex.length() == 1) ? "0" + resultHex : resultHex;
    } else {
        registers[operand] = (resultHex.length() == 1) ? "0" + resultHex : resultHex;
    }
    
    flags[1] = (result == 0) ? 1 : 0; // Zero flag
    
    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    int parity = 0;
    for (int x = result; x; x &= (x - 1)) {
        parity ^= 1;
    }
    flags[5] = !parity; // Parity flag
}

void Arithmetic::INR(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    int operandValue;
    std::string indirectMemoryAddress;
    if(operand == "M"){
        indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    }
    else
        operandValue = Converter::hexToDecimal(registers[operand]);
    
    int result = operandValue + 1;
    
    flags[3] = (operandValue & 0x0F) == 0x0F ? 1 : 0;  // if lowerNibble if F then aC generate

    
    result %= 256;

    std::string resultHex = Converter::decimalToHex(result); 
    if(operand == "M")
        directMap[indirectMemoryAddress] = (resultHex.length() == 1) ? "0" + resultHex : resultHex;
    else
        registers[operand] = (resultHex.length() == 1) ? "0" + resultHex : resultHex;
    
    flags[1] = (result == 0) ? 1 : 0; // Zero flag

    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag

    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Arithmetic::INX(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    if(operand == "B"){
        if(registers["C"] == "FF")
        {
            registers["C"] = "00";
            registers["B"] = Converter::decimalToHex(Converter::hexToDecimal(registers["B"]) + 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["C"]) + 1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["C"]=temp;
        }
    }
    else if(operand == "D"){
        if(registers["E"] == "FF")
        {
            registers["E"] = "00";
            registers["D"] = Converter::decimalToHex(Converter::hexToDecimal(registers["D"]) + 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["E"]) + 1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["E"]=temp;
        }
    }
    else if(operand == "H"){
        if(registers["L"] == "FF")
        {
            registers["L"] = "00";
            registers["H"] = Converter::decimalToHex(Converter::hexToDecimal(registers["H"]) + 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["L"]) + 1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["L"]=temp;
        }    
    }
    
}

void Arithmetic::DCX(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    if(operand == "B"){
        if(registers["C"] == "00")
        {
            registers["C"] = "FF";
            registers["B"] = Converter::decimalToHex(Converter::hexToDecimal(registers["B"]) - 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["C"]) - 1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["C"]=temp;
        }
    }
    else if(operand == "D"){
        if(registers["E"] == "00")
        {
            registers["E"] = "FF";
            registers["D"] = Converter::decimalToHex(Converter::hexToDecimal(registers["D"]) - 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["E"]) -1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["E"]=temp;
        }
    }
    else if(operand == "H"){
        if(registers["L"] == "00")
        {
            registers["L"] = "FF";
            registers["H"] = Converter::decimalToHex(Converter::hexToDecimal(registers["H"]) - 1);
        }
        else
        {
            std::string temp= Converter::decimalToHex(Converter::hexToDecimal(registers["L"]) - 1);
            if(temp.length()==1)
            {
                temp="0"+temp;
            }
            registers["L"]=temp;
        }   
    }
    
}

void Arithmetic::DAD(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    
    int regHval = Converter::hexToDecimal(registers["H"]);
    int regLval = Converter::hexToDecimal(registers["L"]);
    int carry = 0;
    if(operand == "B"){
        int regCval = Converter::hexToDecimal(registers["C"]);
        int result = regLval + regCval;
        if(result > 255)
            carry = 1;
        registers["L"] = Converter::decimalToHex(result % 256);
        if(registers["L"].length() == 1)
            registers["L"] = "0" + registers["L"];
    }
    else if(operand == "D"){
        int regEval = Converter::hexToDecimal(registers["E"]);
        int result = regLval + regEval;
        if(result > 255)
            carry = 1;
        registers["L"] = Converter::decimalToHex(result % 256);
        if(registers["L"].length() == 1)
            registers["L"] = "0" + registers["L"];
    }
    else if(operand == "H"){
        int regLval = Converter::hexToDecimal(registers["L"]);
        int result = regLval + regLval;
        if(result > 255)
            carry = 1;
        registers["L"] = Converter::decimalToHex(result % 256); 
        if(registers["L"].length() == 1)
            registers["L"] = "0" + registers["L"];
    }
    int temp = Converter::hexToDecimal(registers[operand]);
    int result = regHval + temp + carry;
    flags[7] = (result > 255)? 1: 0; // set Carry flag
    registers["H"] = Converter::decimalToHex(result % 256);
    if(registers["H"].length() == 1)
            registers["H"] = "0" + registers["H"];
}

void Arithmetic::CMA(std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    registers["A"] = Converter::decimalToHex(255 - accumulatorValue);
}
