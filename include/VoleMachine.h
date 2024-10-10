#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <cstdint>
#include "InstructionSet.h"

class VoleMachine {
public:
    static const int MEMORY_SIZE = 256;
    static const int NUM_REGISTERS = 256;

    VoleMachine();

    uint8_t read_memory(uint8_t address);
    void write_memory(uint8_t address, uint8_t value);

    uint8_t read_register(uint8_t reg);
    void write_register(uint8_t reg, uint8_t value);

    void fetch(uint8_t address);
    void decodeExecute();

private:
    uint8_t memory[MEMORY_SIZE];
    uint8_t registers[NUM_REGISTERS];
    uint8_t program_counter;
    uint16_t instruction_register;
};

#endif