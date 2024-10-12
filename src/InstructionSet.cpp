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
