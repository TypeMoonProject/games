#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <time.h>
#include "src/include/my/game_definitions.h"
#include "src/include/my/render.h"
#include "src/include/my/game_logic.h"
#include "src/include/my/input_handling.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "Failed to initialize SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() < 0) {
        fprintf(stderr, "Failed to initialize SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Failed to initialize SDL_mixer: %s\n", Mix_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Window* window = SDL_CreateWindow("沙威玛传奇", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    // 创建渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    TTF_Font* font = TTF_OpenFont("font/simhei.ttf", 24);
    if (font == NULL) {
        fprintf(stderr, "Failed to load font: %s\n", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    
    SDL_SetRenderDrawColor(renderer, 255, 245, 230, 255);
    srand((unsigned int)time(NULL));
    GameData gameData;
    initGameData(&gameData);
    
    // 库存
    for (int i = 0; i < INGREDIENT_COUNT; i++) {
        gameData.maxInventory[i] = MAX_INVENTORY;
    }
    for (int i = 0; i < INGREDIENT_COUNT; i++) {
        gameData.inventory[i] = gameData.maxInventory[i] / 2;
    }
    
    UpgradeData upgradeData;
    initUpgradeData(&upgradeData);
    
    Mix_Music* bgm = Mix_LoadMUS("sourse/music/money.wav");
    if (bgm == NULL) {
        fprintf(stderr, "Failed to load background music: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgm, -1);
    }
    
    bool quit = false;
    SDL_Event e;
    int mouseX = 0, mouseY = 0;
    Uint32 lastTime = SDL_GetTicks();
    Uint32 lastSecond = SDL_GetTicks();
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type==SDL_QUIT) {
                quit=true;
            }else if(e.type==SDL_MOUSEMOTION) {
                mouseX=e.motion.x;
                mouseY=e.motion.y;
            }else if(e.type==SDL_MOUSEBUTTONDOWN) {
                if (e.button.button == SDL_BUTTON_LEFT) {
                    mouseX = e.button.x;
                    mouseY = e.button.y;
                    switch (gameData.state) {
                        case GAME_STATE_MENU:
                            handleMenuClick(&gameData, mouseX, mouseY, &upgradeData);
                            break;
                        case GAME_STATE_PLAYING:
                            handleGameClick(&gameData, mouseX, mouseY);
                            break;
                        case GAME_STATE_GAME_OVER:
                            handleGameOverClick(&gameData, mouseX, mouseY);
                            break;
                        case GAME_STATE_UPGRADE:
                            handleUpgradeMenuClick(&gameData, mouseX, mouseY, &upgradeData);
                            break;
                    }
                }
            }
        }
        Uint32 currentTime = SDL_GetTicks();
        if (currentTime - lastSecond >= 1000) {
            updateGame(&gameData);
            lastSecond = currentTime;
        }
        
        switch (gameData.state) {
            case GAME_STATE_PLAYING:
                renderGame(renderer, font, &gameData, mouseX, mouseY);
                break;
            case GAME_STATE_UPGRADE:
                renderUpgradeMenu(renderer, font, &gameData, &upgradeData, mouseX, mouseY);
                break;
            case GAME_STATE_GAME_OVER:
                renderGameOver(renderer, font, &gameData, mouseX, mouseY);
                break;
            case GAME_STATE_MENU:
                renderMenu(renderer, font, &gameData, mouseX, mouseY);
                break;
        }
        
        SDL_RenderPresent(renderer);
        
        // 控制帧率
        Uint32 deltaTime = SDL_GetTicks() - lastTime;
        if (deltaTime < 16) {
            SDL_Delay(16 - deltaTime);
        }
        lastTime = SDL_GetTicks();
    }
    
    if((bgm!=NULL)&&(font!=NULL)&&(renderer!=NULL)&&(window!=NULL)){
        Mix_FreeMusic(bgm);
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
    }
    SDL_Quit();
    Mix_Quit();
    TTF_Quit();
    
    return 0;
}