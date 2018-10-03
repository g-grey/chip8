#ifndef DEBUG_H
#define DEBUG_H

class Debug {
    public:
        Debug();
        ~Debug();
        void printRom();
        void printRegisters();
        void printMemory();
        void printStack();
        void printMap();
        void printKeys();
    private:
};

#endif