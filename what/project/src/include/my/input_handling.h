#ifndef INPUT_HANDLING_H
#define INPUT_HANDLING_H

#include "game_definitions.h"

// 处理菜单鼠标点击

void handleMenuClick(GameData* gameData, int mouseX, int mouseY, UpgradeData* upgradeData);

// 处理游戏鼠标点击

void handleGameClick(GameData* gameData, int mouseX, int mouseY);

// 处理游戏结束界面点击

void handleGameOverClick(GameData* gameData, int mouseX, int mouseY);

// 处理升级菜单鼠标点击

void handleUpgradeMenuClick(GameData* gameData, int mouseX, int mouseY, UpgradeData* upgradeData);

#endif // INPUT_HANDLING_H