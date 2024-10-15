#include "../include/InstructionSet.h"
#include "../include/VoleMachine.h"

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
