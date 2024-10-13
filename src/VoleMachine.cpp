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

uint8_t VoleMachine::read_memory(uint8_t address) const {
    return memory[address];
}

void VoleMachine::write_memory(uint8_t address, uint8_t value) {
    memory[address] = value;
}

uint8_t VoleMachine::read_register(uint8_t reg) const {
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

void VoleMachine::set_program_counter(uint8_t address) {
    program_counter = address;
}

uint8_t VoleMachine::get_program_counter() const {
    return program_counter;
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
            InstructionSet::LOAD(*this, reg, valueXY);
            break;
        case 0x2:
            InstructionSet::LOAD_VAL(*this, reg, valueXY);
            break;
        case 0x3:
            InstructionSet::STORE(*this, reg, valueXY);
            break;
        case 0x4:
            InstructionSet::MOVE(*this, regS, regD);
            break;
        case 0x5:
            InstructionSet::ADD(*this, reg, regS, regD);
            break;
        case 0x6:
            InstructionSet::ADD_FLOAT(*this, reg, regS, regD);
            break;
        case 0x7:
            InstructionSet::OR(*this, reg, regS, regD);
            break;
        case 0x8:
            InstructionSet::AND(*this, reg, regS, regD);
            break;
        case 0x9:
            InstructionSet::XOR(*this, reg, regS, regD);
            break;
        case 0xA:
            InstructionSet::ROTATE(*this, reg, valueXY);
            break;
        case 0xB:
            InstructionSet::JUMP(*this, reg, valueXY);
            break;
        case 0xC:
            InstructionSet::HALT(*this);
            break;
        default: 
            // idk Error
            break;
    }
}

