#include <iomanip>
#include "debug.h"

Debug::Debug(Chip8 &ch8) :
    chip8(ch8) {}

Debug::~Debug() {}

void Debug::printRom() {
    printHeader("ROM");
    
    for (int x = PC_START; x < PC_START+chip8.romSize; x += 2) {
        char cursor = x == chip8.programCounter ? '>' : ' ';

        std::cout << cursor << "0x" 
                  << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
                  << x << ": " << "0x" << ((chip8.memory[x] << 8) | chip8.memory[x+1]) << std::endl;
    }
}

void Debug::printRegisters() {
    printHeader("REGISTERS");

    std::cout << "PC: 0x"
              << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
              << chip8.programCounter << std::endl;

    std::cout << " I: 0x"
              << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
              << chip8.i << std::endl;

    std::cout << "SP: 0x"
              << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
              << chip8.stackPointer << std::endl << std::endl;
    
    for (int x = 0; x < NUM_REGISTERS; ++x) {
        std::cout << "V" 
                  << std::hex << std::uppercase
                  << x << ": " << "0x" 
                  << std::setfill('0') << std::setw(4)
                  << (unsigned int)chip8.registers[x] << std::endl;
    }
}

void Debug::printMemory() {
    printHeader("MEMORY");
    
    for (int x = 0; x < MEMORY_SIZE; ++x) {
        printf("0x%x: 0x%x ", x, chip8.memory[x]);

        if (x % 15 == 0) {
            printf("\n");
        }
    }

    printf("\n");
}

void Debug::printStack() {
    printHeader("STACK");
    
    printf("\nsp: %d\n", chip8.stackPointer);

    for (int x = 0; x < STACK_SIZE; ++x) {
        printf("%d: 0x%x\n", x, chip8.stack[x]);
    }
}

void Debug::printMap() {
    printHeader("MAP");
    
    for (int h = 0; h < MAP_HEIGHT; ++h) {
        for (int w = 0; w < MAP_WIDTH; ++w) {
            if (chip8.map[w][h]) {
                std::cout << "#";
            } else {
                std::cout << "-";
            } 
        }
        std::cout << std::endl;
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

    std::cout << "Executing...0x" 
              << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
              << ((chip8.memory[chip8.programCounter] << 8) | chip8.memory[chip8.programCounter+1])
              << std::endl;
}

void Debug::printOpcode() {
    printHeader("OPCODE");
    
    std::cout << "0x"
         << std::setfill('0') << std::setw(4) << std::hex << std::uppercase
         << ((chip8.memory[chip8.programCounter] << 8) | chip8.memory[chip8.programCounter+1])
         << std::endl;
}

void Debug::printHeader(std::string text) {
    std::cout << std::endl << text << std::endl;
}
