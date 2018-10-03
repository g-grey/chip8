#include <iostream>
#include "chip8.h"
#include "ui.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: ./chip8 <rom>" << endl;
        return 1;
    }

    UI ui;    
    Chip8 chip8;
    chip8.loadRom(argv[1]);

    while (!ui.quit) {
        //int start = SDL_GetTicks();

        if (!chip8.paused) {
            chip8.execute();

            if (chip8.updateScreen) {
                ui.drawScreen(chip8.map);      
            }
        }

        ui.getInput();

        /*
        int time = SDL_GetTicks() - start;
        if (time < 0) continue;

        int sleepTime = 5 - time;
        if (sleepTime > 0) SDL_Delay(sleepTime);
        */
    }

    return 0;
}