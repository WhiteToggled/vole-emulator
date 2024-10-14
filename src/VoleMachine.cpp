#include "../include/InstructionSet.h"
#include <iomanip>
#include <iostream>
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

void VoleMachine::start_machine() {
    while(!is_halted) {
        fetch();
        decode_execute();
    }
}


void VoleMachine::halt_machine() {
    is_halted = true;
}


// Debugging
void VoleMachine::get_program_counter() const {
    std::cout << "Program Counter: " << int(program_counter) << std::endl;
}

void VoleMachine::get_instruction_register() const {
    std::cout << "Instruction Register: " << int(instruction_register) << std::endl;
}

void VoleMachine::get_memory() const {
    const int cells_per_row = 8;

    std::cout << "--------------" << std::endl;
    std::cout << "    Memory    " << std::endl;
    std::cout << "--------------" << std::endl;
    for (int i = 0; i < MEMORY_SIZE; i++) {
        if(i % cells_per_row == 0)
            std::cout << std::endl;
        std::cout << "[Address " << std::setw(2) << std::setfill('0') << i 
              << " : 0x" << std::setw(2) << std::setfill('0') << std::hex << int(memory[i]) << "]  ";
    }
    std::cout << std::endl;
}

void VoleMachine::get_registers() const {
    const int cells_per_row = 8;

    std::cout << "--------------" << std::endl;
    std::cout << "  Registers   " << std::endl;
    std::cout << "--------------" << std::endl;
    for (int i = 0; i < NUM_REGISTERS; i++) {
        if(i % cells_per_row == 0)
            std::cout << std::endl;
        std::cout << "[Address " << std::setw(2) << std::setfill('0') << i 
              << " : 0x" << std::setw(2) << std::setfill('0') << std::hex << int(registers[i]) << "]  ";
    }
    std::cout << std::endl;
}

void VoleMachine::get_current_state() const{
    get_program_counter();
    get_instruction_register();
    get_memory();
    get_registers();
}
