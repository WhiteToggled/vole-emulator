#include "../include/InstructionSet.h"
#include "../include/VoleMachine.h"
#include <cstdlib>

void InstructionSet::LOAD(VoleMachine &machine, uint8_t reg, uint8_t address) {
    uint8_t value = machine.read_memory(address);
    machine.write_register(reg, value);
}

void InstructionSet::LOAD_VAL(VoleMachine &machine, uint8_t reg, uint8_t value) {
    machine.write_register(reg, value);
}

void InstructionSet::STORE(VoleMachine &machine, uint8_t reg, uint8_t address) {
    uint8_t value = machine.read_register(reg);
    machine.write_memory(address, value);
}
    
void InstructionSet::MOVE(VoleMachine &machine, uint8_t reg, uint8_t regDest) {
    uint8_t value = machine.read_register(reg);
    machine.write_register(regDest, value);
}

void InstructionSet::ADD(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2) {
    uint8_t value1 = machine.read_register(reg1);
    uint8_t value2 = machine.read_register(reg2);

    machine.write_register(regDest, value1+value2);
}

void InstructionSet::ADD_FLOAT(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2) {
    uint8_t value1 = machine.read_register(reg1);
    uint8_t value2 = machine.read_register(reg2);

    int sign1, expt1, mantissa1;
    int sign2, expt2, mantissa2;

    parse_float(value1, sign1, expt1, mantissa1);
    parse_float(value2, sign2, expt2, mantissa2);

    // Aligns both exponents
    while (expt1 < expt2) {
        mantissa1 = mantissa1 >> 1;
        expt1++;
    }
    while (expt2 < expt1) {
        mantissa2 = mantissa2 >> 1;
        expt2++;
    }

    int res_mantissa = (sign1*mantissa1) + (sign2*mantissa2);
    int res_sign = (res_mantissa < 0) ? -1: 1;
    res_mantissa = std::abs(res_mantissa);
    int res_expt = expt1; // They're both equal so either is fine

    // Accounting for overflow in 4-bit mantissa
    if (res_mantissa > 15) { 
        res_mantissa = res_mantissa >> 1;
        res_expt++;
    }

    if (res_expt > 3) {
        res_mantissa = 15;
        res_expt = 3;
    }

    uint8_t sum = package_float(res_sign, res_expt, res_mantissa);

    machine.write_register(regDest, sum);
}

void InstructionSet::parse_float(uint8_t num, int &sign, int &expt, int &mantissa) {
    sign = (num & 0x80) ? -1 : 1;
    expt = ((num >> 4) & 0x07) - 4; // The -4 is to account for excess notation
    mantissa = num & 0x0F;
}

uint8_t InstructionSet::package_float(int sign, int expt, int mantissa) {
    int result = 0;

    if (sign < 0) result = result | 0x80; // 1_______
    result = result | ((expt + 4) & 0x07) << 4; // S EEE ____
    result = result | mantissa & 0x0F; // S EEE MMMM
    
    return result;
}


void InstructionSet::OR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2) {
    uint8_t value1 = machine.read_register(reg1);
    uint8_t value2 = machine.read_register(reg2);

    uint8_t value = value1 | value2;
    machine.write_register(regDest, value);
}

void InstructionSet::AND(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2) {
    uint8_t value1 = machine.read_register(reg1);
    uint8_t value2 = machine.read_register(reg2);

    uint8_t value = value1 & value2;
    machine.write_register(regDest, value);
}

void InstructionSet::XOR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2) {
    uint8_t value1 = machine.read_register(reg1);
    uint8_t value2 = machine.read_register(reg2);

    uint8_t value = value1 ^ value2;
    machine.write_register(regDest, value);
}

void InstructionSet::ROTATE(VoleMachine &machine, uint8_t reg, uint8_t numBits) {
    numBits  = numBits % 8;
    uint8_t value = machine.read_register(reg);
    uint8_t rotated = value >> numBits | value << (8 - numBits);

    machine.write_register(reg, rotated);
}

void InstructionSet::JUMP(VoleMachine &machine, uint8_t reg, uint8_t address) {
    uint8_t reg0 = machine.read_register(0); 

    if (machine.read_register(reg) == reg0) {
        machine.set_program_counter(address);
    }
}

void InstructionSet::HALT(VoleMachine &machine) {
    machine.halt_machine();
}
