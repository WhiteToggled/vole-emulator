#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/VoleMachine.h"
#include "../include/InstructionSet.h"

using namespace std;
VoleMachine machine;

void input_memory() {

    string hex_addr_str, hex_value_str;
    unsigned hex_addr_int, hex_value_int;

    cout << "Enter the memory address and corresponding value separated by a whitespace. " << endl;
    cout << "Press (n N) to continue to execution. \n\n";

    while (true) {

        cin >> hex_addr_str;
        if (hex_addr_str == "n" || hex_addr_str == "N")
            return;
        cin >> hex_value_str;

        stringstream ss;
        ss << hex << hex_addr_str;
        ss >> hex_addr_int;
        ss.clear();
        ss << hex << hex_value_str;
        ss >> hex_value_int;

        machine.write_memory(static_cast<uint8_t>(hex_addr_int), static_cast<uint8_t>(hex_value_int));
    }
}

int main(int argc, char* argv[]) {

    // TODO UI 
    // 1. Highlight used addresses and registers.
    // 2. Make a way to go through each machine cycle by pressing -> and <-
    // 3. Make a UI in curses

    string char_usr_pc;
    int int_usr_pc;
    input_memory();
    cin.clear();
    cin.ignore(200,'\n');
    cout << "Enter program counter value: ";
    cin >> char_usr_pc;
    stringstream pc;
    pc << hex << char_usr_pc;
    pc >> int_usr_pc;
    machine.set_program_counter(static_cast<uint8_t>(int_usr_pc));
    machine.start_machine();


    return 0;

}
