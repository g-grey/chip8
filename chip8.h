#include <cstdint>

#ifndef CHIP8_H
#define CHIP8_H

#define NUM_REGISTERS 16
#define MEMORY_SIZE 4096
#define STACK_SIZE 16
#define NUM_KEYS 16
#define PC_START 512
#define MAP_WIDTH 64
#define MAP_HEIGHT 32
#define SPRITE_WIDTH 8
#define NUM_KEYS 16

class Chip8 {
    public:
        Chip8();
        void loadFont();
        void loadRom(std::string rom);
        void draw(int x, int y, int height);
        void execute();
        void printRom();
        void printRegisters();
        void printMemory();
        void printStack();
        void printMap();
        void printKeys();
        void setKeyStates(bool &keyMap);

        uint8_t registers[NUM_REGISTERS];
        uint8_t map[MAP_WIDTH][MAP_HEIGHT];
        bool keyStates[NUM_KEYS];
        bool paused;
        bool updateScreen;
        int setRegister;
    private:
        uint8_t stackPointer;
        uint8_t memory[MEMORY_SIZE];
        uint16_t stack[STACK_SIZE];
        uint16_t opcode;
        uint16_t i;
        uint16_t programCounter;
        unsigned int romSize;
        unsigned char delayTimer;
        unsigned char soundTimer;
};

#endif