#include <cstdint>
#include <string>
#include <vector>

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

class Chip8 {
    public:
        Chip8();
        ~Chip8();
        void loadRom(std::string rom);        
        bool beep();
        void execute();
        void decrementTimers();
        bool getPaused();
        bool getUpdateScreen();
        bool getWaitForInput();
        void setWaitForInput(bool val);
        void setRegister(int reg, uint8_t val);
        void setKeyState(int key, bool val);
        int getRegisterToSet();
        std::vector<std::vector<uint8_t>> getMap();
    private:
        void loadFont();
        void clearMap();
        void draw(int x, int y, int height);
        std::vector<std::vector<uint8_t>> map;
        uint8_t registers[NUM_REGISTERS];
        uint8_t stackPointer;
        uint8_t memory[MEMORY_SIZE];
        uint16_t stack[STACK_SIZE];
        uint16_t opcode;
        uint16_t i;
        uint16_t programCounter;
        bool paused;
        bool updateScreen;
        bool waitForInput;
        bool keyStates[NUM_KEYS];
        unsigned int romSize;
        unsigned int registerToSet;
        unsigned char delayTimer;
        unsigned char soundTimer;
        friend class Debug;
};

#endif