#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <unistd.h>
#include "chip8.h"

using namespace std;

int main(int argc, char **argv) {
    srand(time(NULL));

    Chip8 chip8;
    chip8.loadRom(argv[1]);

    SDL_Window *window;
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Chip8",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1280,
        640,
        SDL_WINDOW_SHOWN
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_RenderClear(renderer);

    SDL_Event e;
    bool quit = false;
    map<int,int>::iterator it;
    map<int,int> key_map;
    key_map[SDLK_1] = 1;
    key_map[SDLK_2] = 2;
    key_map[SDLK_3] = 3;
    key_map[SDLK_4] = 0xc;
    key_map[SDLK_q] = 4;
    key_map[SDLK_w] = 5;
    key_map[SDLK_e] = 6;
    key_map[SDLK_r] = 0xd;
    key_map[SDLK_a] = 7;
    key_map[SDLK_s] = 8;
    key_map[SDLK_d] = 9;
    key_map[SDLK_f] = 0xe;
    key_map[SDLK_z] = 0xa;
    key_map[SDLK_x] = 0;
    key_map[SDLK_c] = 0xb;
    key_map[SDLK_v] = 0xf;

    while (!quit) {
        int start = SDL_GetTicks();

        if (!chip8.paused) {
            chip8.execute();

            if (chip8.updateScreen) {
                // TODO - just draw current sprite rather than entire screen
                for (int h = 0; h < MAP_HEIGHT; h++) {
                    for (int w = 0; w < MAP_WIDTH; w++) {
                        SDL_Rect r;
                        r.x = w*20;
                        r.y = h*20;
                        r.w = 20;
                        r.h = 20;

                        if (chip8.map[w][h]) {
                            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                        } else {
                            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                        }

                        SDL_RenderFillRect(renderer, &r);
                    }
                }

                SDL_RenderPresent(renderer);
            }
        }

        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_n) {
                    chip8.paused = false;
                }

                if (e.key.keysym.sym == SDLK_p) {
                    chip8.printRegisters();
                }

                if (e.key.keysym.sym == SDLK_o) {
                    chip8.printMap();
                }

                if (e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }

                for (it = key_map.begin(); it != key_map.end(); it++) {
                    if (e.key.keysym.sym == it->first) {
                        chip8.keyStates[it->second] = true;

                        if (chip8.paused) {
                            chip8.paused = false;
                            chip8.registers[chip8.setRegister] = it->second;
                        }
                    }
                }
            }

            if (e.type == SDLK_UP) {
                for (it = key_map.begin(); it != key_map.end(); it++) {
                    if (e.key.keysym.sym == it->first) {
                        chip8.keyStates[it->second] = false;
                    }
                }
            }
        }

        int time = SDL_GetTicks() - start;
        if (time < 0) continue;

        int sleepTime = 5 - time;
        if (sleepTime > 0) SDL_Delay(sleepTime);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}