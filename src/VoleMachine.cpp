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

void VoleMachine::fetch() {

    uint8_t high_byte = read_memory(program_counter);
    uint8_t low_byte = read_memory(program_counter + 1);

    // Concatenate the two
    uint16_t instruction = (high_byte << 8) | low_byte;

    instruction_register = instruction;
    program_counter += 2;
}

void VoleMachine::decode_execute() {

    uint8_t opcode = instruction_register >> 12;      // _ X X X 
    uint8_t reg = (instruction_register >> 8) & 0xF;  // X _ X X 
    uint8_t regS = (instruction_register >> 4) & 0xF; // X X _ X
    uint8_t regD = instruction_register & 0xF;        // X X X _
    uint8_t valueXY = instruction_register & 0xFF;    // X X _ _

    switch (opcode) {
        case 0x1:
            LOAD(*this, reg, valueXY);
            break;
        case 0x2:
            LOAD_VAL(*this, reg, valueXY);
            break;
        case 0x3:
            STORE(*this, reg, valueXY);
            break;
        case 0x4:
            MOVE(*this, regS, regD);
            break;
        case 0x5:
            ADD(*this, reg, regS, regD);
            break;
        case 0x6:
            ADD_FLOAT(*this, reg, regS, regD);
            break;
        case 0x7:
            OR(*this, reg, regS, regD);
            break;
        case 0x8:
            AND(*this, reg, regS, regD);
            break;
        case 0x9:
            XOR(*this, reg, regS, regD);
            break;
        case 0xA:
            ROTATE(*this, reg, valueXY);
            break;
        case 0xB:
            JUMP(*this, reg, valueXY);
            break;
        case 0xC:
            HALT(*this);
            break;
        default: 
            // idk Error
            break;
    }
}

