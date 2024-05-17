#include "logical.h"
#include "converter.h"

void Logical::ANA(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue;
    if (operand == "M") {
        std::string indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }
    int result = accumulatorValue & operandValue;
    registers["A"] = Converter::decimalToHex(result);
    if (registers["A"].length() == 1)
        registers["A"] = "0" + registers["A"];
    flags[7] = 0;  // Carry flag
    flags[3] = 1; // Auxiliary flag
    flags[1] = (result == 0) ? 1 : 0; // Zero flag
    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag
    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Logical::ANI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue = Converter::hexToDecimal(operand);
    int result = accumulatorValue & operandValue;
    registers["A"] = Converter::decimalToHex(result);
    if (registers["A"].length() == 1)
        registers["A"] = "0" + registers["A"];
    flags[7] = 0;  // Carry flag
    flags[3] = 1; // Auxiliary flag
    flags[1] = (result == 0) ? 1 : 0; // Zero flag
    flags[0] = (result & 0x80) ? 1 : 0; // Sign flag
    int parity = 0;
    for (int x = result; x; x = x & (x - 1)) {
        parity = !parity;
    }
    flags[5] = !parity; // Parity flag
}

void Logical::ORA(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue;
    if (operand == "M") {
        std::string indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }
    int result = accumulatorValue | operandValue;
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

void Logical::ORI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue = Converter::hexToDecimal(operand);
    int result = accumulatorValue | operandValue;
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

void Logical::XRA(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue;
    if (operand == "M") {
        std::string indirectMemoryAddress = registers["H"] + registers["L"];
        operandValue = Converter::hexToDecimal(directMap[indirectMemoryAddress]);
    } else {
        operandValue = Converter::hexToDecimal(registers[operand]);
    }
    int result = accumulatorValue ^ operandValue;
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

void Logical::XRI(std::string operand, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers, std::map<std::string, std::string>& directMap) {
    int accumulatorValue = Converter::hexToDecimal(registers["A"]);
    int operandValue = Converter::hexToDecimal(operand);
    int result = accumulatorValue ^ operandValue;
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

void Logical::CMP(std::string operand, std::map<std::string, std::string>& directMap, std::vector<int>& flags, std::unordered_map<std::string, std::string>& registers) {
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
    // Set Carry flag & sign flag
    if (accumulatorValue < operandValue) {
        flags[7] = 1;
        flags[0] = 1;
    } else {
        flags[7] = 0;
        flags[0] = 0;
    }
    // Set Zero flag
    if (accumulatorValue == operandValue)
        flags[1] = 1;
    else
        flags[1] = 0;
    // Set Auxiliary Carry flag
    if (lowerNibbleAcc < lowerNibbleOperand)
        flags[3] = 1;
    else
        flags[3] = 0;
}
