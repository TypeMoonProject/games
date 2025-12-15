#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_definitions.h"

// 初始化游戏数据
// @param gameData 游戏数据结构体指针
void initGameData(GameData* gameData);

// 生成新顾客
// @return 生成的顾客结构体
Customer generateCustomer();



// 处理补货操作
// @param gameData 游戏数据结构体指针
void handleRestock(GameData* gameData);

// 处理切肉操作
// @param gameData 游戏数据结构体指针
void handlePrepMeat(GameData* gameData);

// 处理切土豆操作
// @param gameData 游戏数据结构体指针
void handlePrepPotato(GameData* gameData);

// 处理炸薯条操作
// @param gameData 游戏数据结构体指针
void handleFryPotato(GameData* gameData);

// 更新游戏逻辑
// @param gameData 游戏数据结构体指针
void updateGame(GameData* gameData);

// 初始化升级数据
// @param upgradeData 升级数据结构体指针
void initUpgradeData(UpgradeData* upgradeData);

#endif // GAME_LOGIC_H
