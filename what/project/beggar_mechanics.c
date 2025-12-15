#include "src/include/my/beggar_mechanics.h"
#include "src/include/my/game_definitions.h"
#include "src/include/my/game_logic.h"
#include <stdio.h>

/**
 * @brief 检查是否点击了正在逃跑的乞丐
 * 
 * @param gameData 游戏数据指针
 * @param mouseX 鼠标X坐标
 * @param mouseY 鼠标Y坐标
 */
void checkBeggarClick(GameData* gameData, int mouseX, int mouseY) {
    // 检查是否点击了正在逃跑的乞丐
    for (int i = 0; i < gameData->customerCount; i++) {
        Customer* customer = &gameData->customers[i];
        if (customer->type == CUSTOMER_TYPE_BEGGAR && customer->isRunningAway) {
            // 计算顾客的点击区域（基于render.cpp中的渲染位置）
            int customerX = 200 + i * 180;
            int customerY = 180;
            int customerWidth = 160;
            int customerHeight = 140;
            
            // 检查鼠标是否点击在顾客区域内
            if (mouseX >= customerX && mouseX <= customerX + customerWidth && 
                mouseY >= customerY && mouseY <= customerY + customerHeight) {
                // 抓住乞丐，获得奖励
                catchEscapingBeggar(gameData, i);
                break;
            }
        }
    }
}

/**
 * @brief 生成随机顾客，包含乞丐逻辑
 * 
 * @param gameData 游戏数据指针
 */
void generateRandomCustomerWithBeggarLogic(GameData* gameData) {
    if (gameData->customerCount < gameData->maxCustomers) {
        Customer newCustomer = generateCustomer();
        if (newCustomer.type == CUSTOMER_TYPE_BEGGAR && !gameData->hasActiveBeggar) {
            gameData->customers[gameData->customerCount++] = newCustomer;
            gameData->hasActiveBeggar = true;
        } else if (newCustomer.type == CUSTOMER_TYPE_NORMAL) {
            gameData->customers[gameData->customerCount++] = newCustomer;
        }
    }
}

/**
 * @brief 处理乞丐的逃跑逻辑
 * 
 * @param gameData 游戏数据指针
 * @param customer 顾客指针
 * @param customerIndex 顾客索引
 * @return 是否需要移除该顾客
 */
bool handleBeggarEscapeLogic(GameData* gameData, Customer* customer, int customerIndex) {
    if (customer->type == CUSTOMER_TYPE_BEGGAR) {
        // 乞丐满足后开始计时逃跑
        customer->timeSinceSatisfaction++;
        
        // 3秒后开始逃跑
        if (customer->timeSinceSatisfaction >= 3) {
            customer->isRunningAway = true;
            
            // 再过2秒如果没被抓住就逃跑
            if (customer->timeSinceSatisfaction >= 5) {
                // 移除该顾客（将后面的顾客向前移动）
                for (int j = customerIndex; j < gameData->customerCount - 1; j++) {
                    gameData->customers[j] = gameData->customers[j + 1];
                }
                gameData->customerCount--;
                gameData->hasActiveBeggar = false;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief 抓住逃跑的乞丐，获得奖励
 * 
 * @param gameData 游戏数据指针
 * @param customerIndex 顾客索引
 */
void catchEscapingBeggar(GameData* gameData, int customerIndex) {
    // 抓住乞丐，获得奖励
    gameData->gold += gameData->beggarEscapeReward;
    
    // 移除该顾客（将后面的顾客向前移动）
    for (int j = customerIndex; j < gameData->customerCount - 1; j++) {
        gameData->customers[j] = gameData->customers[j + 1];
    }
    gameData->customerCount--;
    gameData->hasActiveBeggar = false;
}
