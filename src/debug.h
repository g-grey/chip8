#include <iostream>
#include "chip8.h"

using namespace std;

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
    private:
        Chip8 chip8;
};

#endif