#include <iostream>
#include "chip8.h"

#ifndef DEBUG_H
#define DEBUG_H

class Debug {
    public:
        Debug(Chip8 &ch8);
        ~Debug();
        void printRom();
        void printRegisters();
        void printMemory();
        void printStack();
        void printMap();
        void printKeys();
        void printOpcode();
        void printStep();
    private:
        Chip8 &chip8;
        void printHeader(std::string text);
};

#endif