#ifndef BEGGAR_MECHANICS_H
#define BEGGAR_MECHANICS_H

#include "game_definitions.h"

/**
 * @brief 检查是否点击了正在逃跑的乞丐
 * 
 * @param gameData 游戏数据指针
 * @param mouseX 鼠标X坐标
 * @param mouseY 鼠标Y坐标
 */
void checkBeggarClick(GameData* gameData, int mouseX, int mouseY);

/**
 * @brief 生成随机顾客，包含乞丐逻辑
 * 
 * @param gameData 游戏数据指针
 */
void generateRandomCustomerWithBeggarLogic(GameData* gameData);

/**
 * @brief 处理乞丐的逃跑逻辑
 * 
 * @param gameData 游戏数据指针
 * @param customer 顾客指针
 * @param customerIndex 顾客索引
 * @return 是否需要移除该顾客
 */
bool handleBeggarEscapeLogic(GameData* gameData, Customer* customer, int customerIndex);
/**
 * @brief 抓住逃跑的乞丐，获得奖励
 * 
 * @param gameData 游戏数据指针
 * @param customerIndex 顾客索引
 */
void catchEscapingBeggar(GameData* gameData, int customerIndex);

#endif // BEGGAR_MECHANICS_H