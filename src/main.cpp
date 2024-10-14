#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/VoleMachine.h"
#include "../include/InstructionSet.h"

using namespace std;
VoleMachine machine;

void input_memory() {

    string hex_str;
    unsigned hex_value;
    int i = 0;
    do {

        cout << "Please enter the address for memory cell " << i << ": (or q to quit) " << endl;
        cin >> hex_str;

        if (hex_str == "q" || hex_str == "Q") 
            return;

        stringstream ss;

        ss << hex << hex_str;
        ss >> hex_value;

        machine.write_memory(i, static_cast<uint8_t>(hex_value));


        i++;
    } while (i < 256);

}

int main(int argc, char* argv[]) {


    input_memory();
    cout << "------------------" << endl;
    cout << "     Initial      " << endl;
    cout << "------------------" << endl;
    machine.get_current_state();
    machine.start_machine();
    cout << "------------------" << endl;
    cout << "       Final      " << endl;
    cout << "------------------" << endl;
    machine.get_current_state();

    return 0;

}
