#include <iomanip>
#include "debug.h"

Debug::Debug(Chip8 &ch8) :
    chip8(ch8) {}

Debug::~Debug() {}

void Debug::printRom() {
    printHeader("ROM");
    
    for (int x = PC_START; x < PC_START+chip8.romSize; x += 2) {
        char cursor = x == chip8.programCounter ? '>' : ' ';

        cout << cursor << "0x" 
             << setfill('0') << setw(4) << hex << uppercase
             << x << ": " << "0x" << ((chip8.memory[x] << 8) | chip8.memory[x+1]) << endl;
    }
}

void Debug::printRegisters() {
    printHeader("REGISTERS");

    cout << "PC: 0x"
         << setfill('0') << setw(4) << hex << uppercase
         << chip8.programCounter << endl;

    cout << " I: 0x"
         << setfill('0') << setw(4) << hex << uppercase
         << chip8.i << endl;

    cout << "SP: 0x"
         << setfill('0') << setw(4) << hex << uppercase
         << chip8.stackPointer << endl << endl;
    
    for (int x = 0; x < NUM_REGISTERS; x++) {
        cout << "V" 
             << hex << uppercase
             << x << ": " << "0x" 
             << setfill('0') << setw(4)
             << (unsigned int)chip8.registers[x] << endl;
    }
}

void Debug::printMemory() {
    printHeader("MEMORY");
    
    for (int x = 0; x < MEMORY_SIZE; x++) {
        printf("0x%x: 0x%x ", x, chip8.memory[x]);

        if (x % 15 == 0) printf("\n");
    }

    printf("\n");
}

void Debug::printStack() {
    printHeader("STACK");
    
    printf("\nsp: %d\n", chip8.stackPointer);

    for (int x = 0; x < STACK_SIZE; x++) {
        printf("%d: 0x%x\n", x, chip8.stack[x]);
    }
}

void Debug::printMap() {
    printHeader("MAP");
    
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (chip8.map[w][h]) {
                cout << "#";
            } else {
                cout << "-";
            } 
        }
        cout << endl;
    }
}

void Debug::printKeys() {
    printHeader("KEYS");

    for (int x = 0; x < NUM_KEYS; x++) {
        printf("%d: 0x%x\n", x, chip8.keyStates[x]);
    }
}

void Debug::printStep() {
    printHeader("STEP");

    cout << "Executing...0x" 
         << setfill('0') << setw(4) << hex << uppercase
         << ((chip8.memory[chip8.programCounter] << 8) | chip8.memory[chip8.programCounter+1])
         << endl;
}

void Debug::printOpcode() {
    printHeader("OPCODE");
    
    cout << "0x"
         << setfill('0') << setw(4) << hex << uppercase
         << ((chip8.memory[chip8.programCounter] << 8) | chip8.memory[chip8.programCounter+1])
         << endl;
}

void Debug::printHeader(string text) {
    cout << endl << text << endl;
}