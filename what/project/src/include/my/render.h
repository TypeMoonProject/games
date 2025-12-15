#ifndef RENDER_H
#define RENDER_H

#include "game_definitions.h"

// 渲染文本
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);
// 渲染按钮
bool renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, int width, int height, bool hover);
// 渲染菜单界面
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);
// 渲染游戏界面
void renderGame(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);
// 渲染游戏结束界面
void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);
// 渲染升级界面
void renderUpgradeMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, UpgradeData* upgradeData, int mouseX, int mouseY);

#endif
