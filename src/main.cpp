#include <iostream>
#include "ui.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc < 2 || argc > 4) {
        cout << "Usage: ./chip8 [--debug | -d] [--mute | -m] <rom>" << endl;
        return 1;
    }
    
    bool debugMode = false;
    bool mute = false;
    string rom = "";

    for (int x = 1; x < argc; x++) {
        string arg = argv[x];

        if (arg == "--debug" || arg == "-d") {
            debugMode = true;
        } else if (arg == "--mute" || arg == "-m") {
            mute = true;
        } else {
            rom = arg;
        }
    }

    UI ui;
    ui.run(rom, debugMode);

    return 0;
}