#include "debug.h"

void Debug::printRom() {
    /*
    for (int x = PC_START; x < PC_START+romSize; x += 2) {
        opcode = (memory[x] << 8) | memory[x+1];
        printf("0x%04x: 0x%04x\n", x, opcode);
    }
    */
}

void Debug::printRegisters() {
    /*
    printf("\nRegisters\n");
    printf("PC: 0x%x\n", programCounter);
    printf("I: 0x%x\n", i);
    printf("SP: 0x%x\n\n", stackPointer);

    for (int x = 0; x < NUM_REGISTERS; x++) {
        printf("V%X: 0x%x\n", x, registers[x]);
    }
    */
}

void Debug::printMemory() {
    /*
    for (int x = 0; x < MEMORY_SIZE; x++) {
        printf("0x%x: 0x%x ", x, memory[x]);

        if (x % 15 == 0) printf("\n");
    }

    printf("\n");
    */
}

void Debug::printStack() {
    /*
    printf("\nsp: %d\n", stackPointer);

    for (int x = 0; x < STACK_SIZE; x++) {
        printf("%d: 0x%x\n", x, stack[x]);
    }
    */
}

void Debug::printMap() {
    /*
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            if (map[w][h]) printf("#");
            else printf("-");
        }
        printf("\n");
    }
    */
}

void Debug::printKeys() {
    /*
    for (int x = 0; x < NUM_KEYS; x++) {
        printf("%d: 0x%x\n", x, keyStates[x]);
    }
    */
}