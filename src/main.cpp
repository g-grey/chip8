#include <iostream>
#include "ui.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2 || argc > 3) {
        cout << "Usage: ./chip8 [--debug | -d] <rom>" << endl;
        return 1;
    }
    
    string rom = "";
    bool debugMode = false;

    for (int x = 1; x < argc; x++) {
        string arg = argv[x];

        if (arg == "--debug" || arg == "-d") {
            debugMode = true;
        } else {
            rom = arg;
        }
    }

    UI ui;
    ui.run(rom, debugMode);

    return 0;
}