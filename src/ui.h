#include <SDL2/SDL.h>
#include <map>
#include <string>
#include "chip8.h"
#include "debug.h"

#ifndef UI_H
#define UI_H

#define WINDOW_TITLE "Chip8"
#define BEEP_FILE "beep.wav"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 640

class UI {
    public:
        UI();
        ~UI();
        void drawScreen(u_int8_t (&map)[MAP_WIDTH][MAP_HEIGHT]);
        void getInput();
        void run(string rom, bool debug);
        bool quit;
    private:
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Event e;
        std::map<int,int> keyMap;
        std::map<int,int>::iterator it;
        Chip8 chip8;
        Debug *dbg;
        bool paused;
        bool debugMode;
        SDL_AudioSpec wavSpec;
        Uint32 wavLength;
        Uint8 *wavBuffer;
        SDL_AudioDeviceID deviceId;
};

#endif