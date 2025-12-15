#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "game_definitions.h"

//初始化游戏数据
void initGameData(GameData* gameData);
//生成新顾客
Customer generateCustomer();
//处理补货操作
void handleRestock(GameData* gameData);
//处理切肉操作
void handlePrepMeat(GameData* gameData);
//处理切土豆操作
void handlePrepPotato(GameData* gameData);
//处理炸薯条操作
void handleFryPotato(GameData* gameData);
//更新游戏逻辑
void updateGame(GameData* gameData);
//初始化升级数据
void initUpgradeData(UpgradeData* upgradeData);

#endif 
