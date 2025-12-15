#ifndef BEGGAR_MECHANICS_H
#define BEGGAR_MECHANICS_H

#include "game_definitions.h"

//检查是否点击了正在逃跑的乞丐
void checkBeggarClick(GameData* gameData, int mouseX, int mouseY);
//生成随机顾客，包含乞丐
void generateBeggar(GameData* gameData);
//处理乞丐的逃跑逻辑
bool BeggarEscape(GameData* gameData, Customer* customer, int customerIndex);
//抓住逃跑的乞丐，获得奖励
void catchEscapingBeggar(GameData* gameData, int customerIndex);

#endif // BEGGAR_MECHANICS_H