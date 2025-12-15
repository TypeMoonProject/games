#include "src/include/my/game_logic.h"
#include "src/include/my/beggar_mechanics.h"
#include "src/include/my/input_handling.h"

// 处理补货操作
// @param gameData 游戏数据结构体指针
void handleRestock(GameData* gameData) {
    // 为所有食材补充到最大库存
    for (int i = 0; i < INGREDIENT_COUNT; i++) {
        gameData->inventory[i] = gameData->maxInventory[i];
    }
}

// 处理切肉操作
// @param gameData 游戏数据结构体指针
void handlePrepMeat(GameData* gameData) {
    // 如果当前没有其他烹饪任务，则开始切肉
    if (gameData->currentCookingState == COOKING_STATE_IDLE) {
        gameData->currentCookingState = COOKING_STATE_PREP_MEAT;
        gameData->cookingProgress = 0;
        gameData->cookingTimer = 0;
    }
}

// 处理切土豆操作
// @param gameData 游戏数据结构体指针
void handlePrepPotato(GameData* gameData) {
    // 如果当前没有其他烹饪任务，则开始切土豆
    if (gameData->currentCookingState == COOKING_STATE_IDLE) {
        gameData->currentCookingState = COOKING_STATE_PREP_POTATO;
        gameData->cookingProgress = 0;
        gameData->cookingTimer = 0;
    }
}

// 处理炸薯条操作
// @param gameData 游戏数据结构体指针
void handleFryPotato(GameData* gameData) {
    // 如果当前没有其他烹饪任务，则开始炸薯条
    if (gameData->currentCookingState == COOKING_STATE_IDLE) {
        gameData->currentCookingState = COOKING_STATE_FRY_POTATO;
        gameData->cookingProgress = 0;
        gameData->cookingTimer = 0;
    }
}


// 更新游戏逻辑
// 参数: gameData - 指向游戏数据结构体的指针
// 功能: 更新游戏的所有逻辑，包括时间、烹饪进度、顾客生成和状态更新等
void updateGame(GameData* gameData) {
    // 更新游戏时间
    gameData->timeLeft--;
    
    // 检查游戏是否结束
    if (gameData->timeLeft <= 0) {
        gameData->state = GAME_STATE_GAME_OVER;
        return;
    }
    
    // 处理烹饪状态和时间管理
    if (gameData->currentCookingState != COOKING_STATE_IDLE) {
        gameData->cookingTimer++;
        int cookTime = 0;
        
        // 根据不同的烹饪状态设置烹饪时间
        switch (gameData->currentCookingState) {
            case COOKING_STATE_PREP_MEAT:
                cookTime = COOK_TIME_PREP_MEAT;
                break;
            case COOKING_STATE_PREP_POTATO:
                cookTime = COOK_TIME_PREP_POTATO;
                break;
            case COOKING_STATE_FRY_POTATO:
                cookTime = COOK_TIME_FRY_POTATO;
                break;
            case COOKING_STATE_IDLE:
            default:
                cookTime = 0;
                break;
        }
        
        // 计算烹饪进度
        gameData->cookingProgress = (gameData->cookingTimer * 100) / cookTime;
        
        // 检查是否完成烹饪
        if (gameData->cookingTimer >= cookTime) {
            // 根据烹饪状态更新库存
            switch (gameData->currentCookingState) {
                case COOKING_STATE_PREP_MEAT:
                    if (gameData->inventory[INGREDIENT_MEAT] < gameData->maxInventory[INGREDIENT_MEAT]) {
                        gameData->inventory[INGREDIENT_MEAT]++;
                    }
                    break;
                case COOKING_STATE_PREP_POTATO:
                case COOKING_STATE_FRY_POTATO:
                    if (gameData->inventory[INGREDIENT_FRIES] < gameData->maxInventory[INGREDIENT_FRIES]) {
                        gameData->inventory[INGREDIENT_FRIES]++;
                    }
                    break;
                case COOKING_STATE_IDLE:
                default:
                    break;
            }
            
            // 重置烹饪状态
            gameData->currentCookingState = COOKING_STATE_IDLE;
            gameData->cookingProgress = 0;
            gameData->cookingTimer = 0;
        }
    }
    
    // 随机生成新顾客，使用乞丐机制逻辑
    if (gameData->customerCount < gameData->maxCustomers && getRandomInt(0, 99) < 50) { // 50%概率生成新顾客
        generateRandomCustomerWithBeggarLogic(gameData);
    }
    
    // 更新顾客状态
    for (int i = 0; i < gameData->customerCount; i++) {
        Customer* customer = &gameData->customers[i];
        
        if (!customer->isSatisfied) {
            customer->patience--;
            if (customer->patience <= 0) {
                // 顾客离开，移除该顾客（将后面的顾客向前移动）
                if (customer->type == CUSTOMER_TYPE_BEGGAR) {
                    gameData->hasActiveBeggar = false;
                }
                for (int j = i; j < gameData->customerCount - 1; j++) {
                    gameData->customers[j] = gameData->customers[j + 1];
                }
                gameData->customerCount--;
                i--;
            }
        } else {
            // 已满足的顾客处理
            if (customer->type == CUSTOMER_TYPE_BEGGAR) {
                // 乞丐满足后开始计时逃跑
                if (handleBeggarEscapeLogic(gameData, &gameData->customers[i], i)) {
                    i--;
                }
            } else {
                customer->timeSinceSatisfaction++;
                // 普通顾客满足后直接离开
                // 移除该顾客（将后面的顾客向前移动）
                for (int j = i; j < gameData->customerCount - 1; j++) {
                    gameData->customers[j] = gameData->customers[j + 1];
                }
                gameData->customerCount--;
                i--;
            }
        }
    }
}
