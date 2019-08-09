#include <iostream>
#include "ui.h"

#define MIN_ARGS 2
#define MAX_ARGS 4
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

using namespace std;

int main(int argc, char **argv) {
    if (argc < MIN_ARGS || argc > MAX_ARGS) {
        cout << "Usage: ./chip8 [--debug | -d] [--mute | -m] <rom>" << endl;
        return EXIT_FAILURE;
    }
    
    bool debugMode = false;
    bool mute = false;
    string rom = "";

    for (int x = 1; x < argc; ++x) {
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

    return EXIT_SUCCESS;
}