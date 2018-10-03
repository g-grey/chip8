#include "ui.h"

UI::UI() {
    quit = false;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);

    keyMap = {
        {SDLK_1, 1},
        {SDLK_2, 2},
        {SDLK_3, 3},
        {SDLK_4, 0xc},
        {SDLK_q, 4},
        {SDLK_w, 5},
        {SDLK_e, 6},
        {SDLK_r, 0xd},
        {SDLK_a, 7},
        {SDLK_s, 8},
        {SDLK_d, 9},
        {SDLK_f, 0xe},
        {SDLK_z, 0xa},
        {SDLK_x, 0},
        {SDLK_c, 0xb},
        {SDLK_c, 0xf}
    };
}

UI::~UI() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void UI::drawScreen(uint8_t (&map)[MAP_WIDTH][MAP_HEIGHT]) {
    // TODO - just draw current sprite rather than entire screen
    for (int h = 0; h < MAP_HEIGHT; h++) {
        for (int w = 0; w < MAP_WIDTH; w++) {
            SDL_Rect r;
            r.x = w*20;
            r.y = h*20;
            r.w = 20;
            r.h = 20;

            if (map[w][h]) {
                SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            } else {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }

            SDL_RenderFillRect(renderer, &r);
        }
    }

    SDL_RenderPresent(renderer);
}

void UI::getInput() {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            quit = true;
        }

        if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_n) {
                //chip8.paused = false;
            }

            if (e.key.keysym.sym == SDLK_p) {
                //chip8.printRegisters();
            }

            if (e.key.keysym.sym == SDLK_o) {
                //chip8.printMap();
            }

            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }

            for (it = keyMap.begin(); it != keyMap.end(); it++) {
                if (e.key.keysym.sym == it->first) {
                    /*
                    chip8.keyStates[it->second] = true;

                    if (chip8.paused) {
                        chip8.paused = false;
                        chip8.registers[chip8.setRegister] = it->second;
                    }
                    */
                }
            }
        }

        if (e.type == SDLK_UP) {
            for (it = keyMap.begin(); it != keyMap.end(); it++) {
                if (e.key.keysym.sym == it->first) {
                    //chip8.keyStates[it->second] = false;
                }
            }
        }
    }
}