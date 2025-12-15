#ifndef RENDER_H
#define RENDER_H

#include "game_definitions.h"

// 渲染文本
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param text 要渲染的文本字符串
// @param x 文本渲染的X坐标
// @param y 文本渲染的Y坐标
// @param color 文本颜色
void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color);

// 渲染按钮
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param text 按钮上的文本字符串
// @param x 按钮左上角X坐标
// @param y 按钮左上角Y坐标
// @param width 按钮宽度
// @param height 按钮高度
// @param hover 鼠标是否悬停在按钮上
// @return 是否点击了按钮
bool renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, int width, int height, bool hover);

// 渲染菜单界面
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void renderMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);

// 渲染游戏界面
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void renderGame(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);

// 渲染游戏结束界面
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY);

// 渲染升级界面
// @param renderer SDL渲染器指针
// @param font 字体指针
// @param gameData 游戏数据结构体指针
// @param upgradeData 升级数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void renderUpgradeMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, UpgradeData* upgradeData, int mouseX, int mouseY);

#endif // RENDER_H
