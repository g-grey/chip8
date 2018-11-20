#include <iomanip>
#include "debug.h"

Debug::Debug(Chip8 &ch8) {
    chip8 = ch8;
}

Debug::~Debug() {}

void Debug::printRom() {
    cout << endl << "ROM" << endl;
    
    for (int x = PC_START; x < PC_START+chip8.romSize; x += 2) {
        uint16_t opcode = (chip8.memory[x] << 8) | chip8.memory[x+1];
        cout << "0x" << setfill('0') << setw(4) << hex << x << ": " << "0x" << opcode << endl;
    }
}

void Debug::printRegisters() {
    cout << endl << "REGISTERS" << endl;
    
    printf("PC: 0x%x\n", chip8.programCounter);
    printf("I: 0x%x\n", chip8.i);
    printf("SP: 0x%x\n\n", chip8.stackPointer);

    for (int x = 0; x < NUM_REGISTERS; x++) {
        printf("V%X: 0x%x\n", x, chip8.registers[x]);
    }
}

void Debug::printMemory() {
    cout << endl << "MEMORY" << endl;
    
    for (int x = 0; x < MEMORY_SIZE; x++) {
        printf("0x%x: 0x%x ", x, chip8.memory[x]);

        if (x % 15 == 0) printf("\n");
    }

    printf("\n");
}

void Debug::printStack() {
    cout << endl << "STACK" << endl;
    
    printf("\nsp: %d\n", chip8.stackPointer);

    for (int x = 0; x < STACK_SIZE; x++) {
        printf("%d: 0x%x\n", x, chip8.stack[x]);
    }
}

void Debug::printMap() {
    cout << endl << "MAP" << endl;
    
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (chip8.map[w][h]) printf("#");
            else printf("-");
        }
        printf("\n");
    }
}

void Debug::printKeys() {
    cout << endl << "KEYS" << endl;

    for (int x = 0; x < NUM_KEYS; x++) {
        printf("%d: 0x%x\n", x, chip8.keyStates[x]);
    }
}

void Debug::printOpcode() {
    cout << endl << "OPCODE" << endl;
    printf("0x%x\n", chip8.opcode);
}