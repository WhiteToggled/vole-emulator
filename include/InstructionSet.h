#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <cstdint>
class VoleMachine;

class InstructionSet {
public:
    static void LOAD(VoleMachine &machine, uint8_t reg, uint8_t address);
    static void LOAD_VAL(VoleMachine &machine, uint8_t reg, uint8_t value);
    static void STORE(VoleMachine &machine, uint8_t reg, uint8_t address);
    static void MOVE(VoleMachine &machine, uint8_t reg, uint8_t regDest);
    static void ADD(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
    static void ADD_FLOAT(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
    static void OR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
    static void AND(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
    static void XOR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
    static void ROTATE(VoleMachine &machine, uint8_t reg, uint8_t numBits);
    static void JUMP(VoleMachine &machine, uint8_t reg, uint8_t address);
    static void HALT(VoleMachine &machine);


private:
    static void parse_float(uint8_t num, int &sign, int &exp, int &mantissa);
    static uint8_t package_float(int sign, int expt, int mantissa);

};

#endif // !INSTRUCTIONSET_H
