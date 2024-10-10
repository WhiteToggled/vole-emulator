#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include <cstdint>
class VoleMachine;

void LOAD(VoleMachine &machine, uint8_t reg, uint8_t address);
void LOAD_VAL(VoleMachine &machine, uint8_t reg, uint8_t value);
void STORE(VoleMachine &machine, uint8_t reg, uint8_t address);
void MOVE(VoleMachine &machine, uint8_t reg, uint8_t regDest);
void ADD(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
void ADD_FLOAT(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
void OR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
void AND(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
void XOR(VoleMachine &machine, uint8_t regDest, uint8_t reg1, uint8_t reg2);
void ROTATE(VoleMachine &machine, uint8_t reg, uint8_t numBits);
void JUMP(VoleMachine &machine, uint8_t reg, uint8_t address);
void HALT(VoleMachine &machine);

#endif // !INSTRUCTIONSET_H
