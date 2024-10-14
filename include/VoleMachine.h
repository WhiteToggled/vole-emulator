#ifndef VOLEMACHINE_H
#define VOLEMACHINE_H

#include <cstdint>
#include "InstructionSet.h"

class VoleMachine {
public:
    static const int MEMORY_SIZE = 256;
    static const int NUM_REGISTERS = 16;

    VoleMachine();

    uint8_t read_memory(uint8_t address) const;
    void write_memory(uint8_t address, uint8_t value);

    uint8_t read_register(uint8_t reg) const;
    void write_register(uint8_t reg, uint8_t value);

    void set_program_counter(uint8_t address);

    void fetch();
    void decode_execute();

    void start_machine();
    void halt_machine();

    // Debugging
    void get_current_state() const;
    void get_program_counter() const;
    void get_instruction_register() const;
    void get_memory() const;
    void get_registers() const;

private:
    uint8_t memory[MEMORY_SIZE];
    uint8_t registers[NUM_REGISTERS];
    uint8_t program_counter;
    uint16_t instruction_register;
    bool is_halted;
};

#endif // !VOLEMACHINE_H
