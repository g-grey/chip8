#include "ui.h"

UI::UI() {
    quit = false;
    paused = false;
    debugMode = false;
    
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);

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

    SDL_LoadWAV(BEEP_FILE, &wavSpec, &wavBuffer, &wavLength);
    deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    keyMap = {
        {SDLK_1, 1},
        {SDLK_2, 2},
        {SDLK_3, 3},
        {SDLK_4, 0xC},
        {SDLK_q, 4},
        {SDLK_w, 5},
        {SDLK_e, 6},
        {SDLK_r, 0xD},
        {SDLK_a, 7},
        {SDLK_s, 8},
        {SDLK_d, 9},
        {SDLK_f, 0xE},
        {SDLK_z, 0xA},
        {SDLK_x, 0},
        {SDLK_c, 0xB},
        {SDLK_v, 0xF}
    };

    dbg = new Debug(chip8);
}

UI::~UI() {
    delete dbg;
    SDL_DestroyWindow(window);
    SDL_CloseAudioDevice(deviceId);
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
}

void UI::run(std::string rom, bool debug) {
    paused = debugMode = debug;
    chip8.loadRom(rom);
    while (!quit) {
        int start = SDL_GetTicks();
        
        if (!paused && !chip8.getWaitForInput()) {
            chip8.execute();

            if (chip8.getUpdateScreen()) {
                drawScreen(chip8.getMap());
            }

            paused = debugMode;

            
            if (chip8.beep()) {            
                SDL_QueueAudio(deviceId, wavBuffer, wavLength);
                SDL_PauseAudioDevice(deviceId, 0);
            }

            chip8.decrementTimers();
        }

        getInput();

        // TODO - delay not working quite right
        int time = SDL_GetTicks() - start;
        if (time < 0) continue;

        int sleepTime = 5 - time;
        if (sleepTime > 0) SDL_Delay(sleepTime);
    }
}

void UI::drawScreen(std::vector<std::vector<uint8_t>> map) {
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
            if (e.key.keysym.sym == SDLK_m) {
                dbg->printMap();
            }

            if (e.key.keysym.sym == SDLK_n) {
                dbg->printStep();
                paused = false;
            }

            if (e.key.keysym.sym == SDLK_o) {
                dbg->printOpcode();
            }

            if (e.key.keysym.sym == SDLK_p) {
                dbg->printRegisters();
            }

            if (e.key.keysym.sym == SDLK_j) {
                dbg->printRom();
            }

            if (e.key.keysym.sym == SDLK_k) {
                dbg->printKeys();
            }

            if (e.key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
            }

            for (it = keyMap.begin(); it != keyMap.end(); it++) {
                if (e.key.keysym.sym == it->first) {
                    chip8.setKeyState(it->second, true);

                    if (chip8.getWaitForInput()) {
                        chip8.setWaitForInput(false);
                        chip8.setRegister(chip8.getRegisterToSet(), it->second);
                    }
                }
            }
        }

        if (e.type == SDL_KEYUP) {
            for (it = keyMap.begin(); it != keyMap.end(); it++) {
                if (e.key.keysym.sym == it->first) {
                    chip8.setKeyState(it->second, false);
                }
            }
        }
    }
}
