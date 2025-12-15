#include "src/include/my/game_definitions.h"

// 初始化游戏数据
// 参数: gameData - 指向游戏数据结构体的指针
// 功能: 初始化游戏的所有数据，包括游戏状态、天数、金币、时间、库存等
void initGameData(GameData* gameData) {
    // 初始化基本游戏状态
    gameData->state = GAME_STATE_MENU;
    gameData->day = 1;
    gameData->gold = 50;
    gameData->timeLeft = GAME_TIME_LIMIT;
    gameData->autoMeatPrep = false;
    gameData->goldPlate = false;
    gameData->maxCustomers = MAX_CUSTOMERS;
    gameData->hasActiveBeggar = false;
    gameData->beggarEscapeReward = 20; // 抓住逃跑乞丐奖励20金币
    
    // 初始化库存和最大库存
    for (int i = 0; i < INGREDIENT_COUNT; i++) {
        gameData->inventory[i] = 20;
        gameData->maxInventory[i] = MAX_INVENTORY;
    }
    
    // 初始化当前制作的卷饼
    gameData->currentShawarma.hasBread = false;
    gameData->currentShawarma.hasMeat = false;
    gameData->currentShawarma.hasCucumber = false;
    gameData->currentShawarma.hasSauce = false;
    gameData->currentShawarma.hasFries = false;
    gameData->currentShawarma.hasKetchup = false;
    gameData->currentShawarma.isWrapped = false;
    gameData->currentShawarma.isDelivered = false;
    
    // 初始化当前制作的薯条
    gameData->currentFries.hasBox = false;
    gameData->currentFries.hasFries = false;
    gameData->currentFries.isDelivered = false;
    
    // 初始化当前制作的可乐
    gameData->currentCoke.hasCup = false;
    gameData->currentCoke.hasCoke = false;
    gameData->currentCoke.isDelivered = false;
    
    // 初始化烹饪相关字段
    gameData->currentCookingState = COOKING_STATE_IDLE;
    gameData->cookingProgress = 0;
    gameData->cookingTimer = 0;
    
    // 初始化顾客数组
    gameData->customerCount = 0;
}

// 生成随机整数
// 参数: min - 最小值
//       max - 最大值
// 返回值: 范围内的随机整数
// 功能: 生成指定范围内的随机整数
int getRandomInt(int min, int max) {
    // 使用rand()生成随机数，并限制在指定范围内
    return min + (rand() % (max - min + 1));
}

// 生成随机顾客
// 返回值: 生成的顾客结构体
// 功能: 随机生成一个顾客，包括顾客类型、需求和请求的餐品配置
Customer generateCustomer() {
    Customer customer;
    
    // 初始化顾客基本属性
    customer.patience = 30;
    customer.maxPatience = 30;
    customer.isSatisfied = false;
    customer.isRunningAway = false;
    customer.timeSinceSatisfaction = 0;
    
    // 随机生成顾客类型（10%概率生成乞丐）
    if (getRandomInt(0, 9) == 0) {
        customer.type = CUSTOMER_TYPE_BEGGAR;
    } else {
        customer.type = CUSTOMER_TYPE_NORMAL;
    }
    
    // 随机生成顾客需求
    customer.needsShawarma = getRandomInt(0, 1);
    customer.needsFries = getRandomInt(0, 1);
    customer.needsCoke = getRandomInt(0, 1);
    
    // 确保顾客至少有一个需求
    if (!customer.needsShawarma && !customer.needsFries && !customer.needsCoke) {
        int randomChoice = getRandomInt(0, 2);
        if (randomChoice == 0) {
            customer.needsShawarma = true;
        } else if (randomChoice == 1) {
            customer.needsFries = true;
        } else {
            customer.needsCoke = true;
        }
    }
    
    // 随机生成卷饼需求
    customer.requestedShawarma.hasBread = true;
    customer.requestedShawarma.hasMeat = getRandomInt(0, 1);
    customer.requestedShawarma.hasCucumber = getRandomInt(0, 1);
    customer.requestedShawarma.hasSauce = getRandomInt(0, 1);
    customer.requestedShawarma.hasFries = getRandomInt(0, 1);
    customer.requestedShawarma.hasKetchup = getRandomInt(0, 1);
    customer.requestedShawarma.isWrapped = true;
    customer.requestedShawarma.isDelivered = false;
    
    return customer;
}

// 初始化升级数据
// 参数: upgradeData - 指向升级数据结构体的指针
// 功能: 初始化升级界面的状态
void initUpgradeData(UpgradeData* upgradeData) {
    upgradeData->state = UPGRADE_STATE_MAIN;
}
