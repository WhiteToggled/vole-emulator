#include "../include/InstructionSet.h"
#include "../include/VoleMachine.h"

VoleMachine::VoleMachine() { 
    
    // Constructor
    for(int i = 0; i< MEMORY_SIZE; ++i) {
        memory[i] = 0;
    }

    for(int i = 0; i< NUM_REGISTERS; ++i) {
        registers[i] = 0;
    }

    program_counter = 0;
    instruction_register = 0;
}

uint8_t VoleMachine::read_memory(uint8_t address) {
    return memory[address];
}

void VoleMachine::write_memory(uint8_t address, uint8_t value) {
    memory[address] = value;
}

uint8_t VoleMachine::read_register(uint8_t reg) {
    if (reg < NUM_REGISTERS) {
        return registers[reg];
    }
    return 0;
}

void VoleMachine::write_register(uint8_t reg, uint8_t value) {
    if (reg < NUM_REGISTERS) {
        registers[reg] = value;
    }
}
