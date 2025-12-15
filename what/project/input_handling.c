#include "src/include/my/input_handling.h"
#include "src/include/my/beggar_mechanics.h"
#include "src/include/my/game_logic.h"

// 处理菜单鼠标点击
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
// @param upgradeData 升级数据结构体指针
void handleMenuClick(GameData* gameData, int mouseX, int mouseY, UpgradeData* upgradeData) {
    // 开始新的一天按钮
    if (mouseX >= 350 && mouseX <= 650 && mouseY >= 320 && mouseY <= 370) {
        gameData->state = GAME_STATE_PLAYING;
        gameData->timeLeft = GAME_TIME_LIMIT;
        gameData->customerCount = 0; // 重置顾客数量为0
        gameData->hasActiveBeggar = false;
        
        // 重置当前制作的餐品
        gameData->currentShawarma.hasBread = false;
        gameData->currentShawarma.hasMeat = false;
        gameData->currentShawarma.hasCucumber = false;
        gameData->currentShawarma.hasSauce = false;
        gameData->currentShawarma.hasFries = false;
        gameData->currentShawarma.hasKetchup = false;
        gameData->currentShawarma.isWrapped = false;
        gameData->currentShawarma.isDelivered = false;
        
        gameData->currentFries.hasBox = false;
        gameData->currentFries.hasFries = false;
        gameData->currentFries.isDelivered = false;
        
        gameData->currentCoke.hasCup = false;
        gameData->currentCoke.hasCoke = false;
        gameData->currentCoke.isDelivered = false;
    }
    // 升级店铺按钮
    else if (mouseX >= 350 && mouseX <= 650 && mouseY >= 400 && mouseY <= 450) {
        // 进入升级界面
        upgradeData->state = UPGRADE_STATE_MAIN;
        // 这里可以添加升级界面的状态切换逻辑
        // 为了简化，我们直接在这里处理升级购买
        int buttonWidth = 400;
        int buttonHeight = 60;
        int buttonSpacing = 20;
        int buttonY = 200;
        
        // 自动切肉机升级
        if (!gameData->autoMeatPrep && mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
            if (gameData->gold >= 50) {
                gameData->gold -= 50;
                gameData->autoMeatPrep = true;
                // 立即应用自动切肉效果
                gameData->inventory[INGREDIENT_MEAT] = gameData->maxInventory[INGREDIENT_MEAT];
            }
        }
        
        buttonY += buttonHeight + buttonSpacing;
        
        // 金盘子升级
        if (!gameData->goldPlate && mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
            if (gameData->gold >= 100) {
                gameData->gold -= 100;
                gameData->goldPlate = true;
            }
        }
        
        buttonY += buttonHeight + buttonSpacing;
        
        // 扩充店面前往升级
        if (mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
            int cost = (gameData->maxCustomers - MAX_CUSTOMERS) * 100 + 150;
            if (gameData->gold >= cost) {
                gameData->gold -= cost;
                gameData->maxCustomers++;
            }
        }
    }
}

// 处理升级菜单鼠标点击
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
// @param upgradeData 升级数据结构体指针
void handleUpgradeMenuClick(GameData* gameData, int mouseX, int mouseY, UpgradeData* upgradeData) {
    int buttonWidth = 400;
    int buttonHeight = 60;
    int buttonSpacing = 20;
    int buttonY = 200;
    
    // 自动切肉机升级
    if (mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        if (!gameData->autoMeatPrep && gameData->gold >= 50) {
            gameData->gold -= 50;
            gameData->autoMeatPrep = true;
            // 立即应用自动切肉效果
            gameData->inventory[INGREDIENT_MEAT] = gameData->maxInventory[INGREDIENT_MEAT];
        }
    }
    
    buttonY += buttonHeight + buttonSpacing;
    
    // 金盘子升级
    if (mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        if (!gameData->goldPlate && gameData->gold >= 100) {
            gameData->gold -= 100;
            gameData->goldPlate = true;
        }
    }
    
    buttonY += buttonHeight + buttonSpacing;
    
    // 扩充店面前往升级
    if (mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        int cost = (gameData->maxCustomers - MAX_CUSTOMERS) * 100 + 150;
        if (gameData->gold >= cost) {
            gameData->gold -= cost;
            gameData->maxCustomers++;
        }
    }
    
    buttonY += buttonHeight + buttonSpacing;
    
    // 返回按钮
    if (mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight) {
        gameData->state = GAME_STATE_PLAYING;
    }
}

// 处理游戏鼠标点击
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void handleGameClick(GameData* gameData, int mouseX, int mouseY) {
    int iconWidth = 80;
    int iconHeight = 45;
    int iconSpacing = 25; // 增加间距，与渲染布局保持一致
    int buttonWidth = 120;
    int buttonHeight = 35;
    int buttonSpacing = 20;
    int iconY = 510; // 调整Y坐标，与渲染布局保持一致
    
    // 点击升级按钮
    if (mouseX >= 950 && mouseX <= 1050 && mouseY >= 60 && mouseY <= 100) {
        gameData->state = GAME_STATE_UPGRADE;
        return;
    }
    
    // 放置面饼
    if (mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_BREAD] > 0 && !gameData->currentShawarma.hasBread) {
            gameData->currentShawarma.hasBread = true;
            gameData->inventory[INGREDIENT_BREAD]--;
        }
    }
    
    // 添加肉
    else if (mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_MEAT] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.hasMeat) {
            gameData->currentShawarma.hasMeat = true;
            gameData->inventory[INGREDIENT_MEAT]--;
        }
    }
    
    // 添加黄瓜
    else if (mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_CUCUMBER] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.hasCucumber) {
            gameData->currentShawarma.hasCucumber = true;
            gameData->inventory[INGREDIENT_CUCUMBER]--;
        }
    }
    
    // 添加沙司
    else if (mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_SAUCE] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.hasSauce) {
            gameData->currentShawarma.hasSauce = true;
            gameData->inventory[INGREDIENT_SAUCE]--;
        }
    }
    
    iconY += iconHeight + iconSpacing;
    
    // 添加薯条
    if (mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_FRIES] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.hasFries) {
            gameData->currentShawarma.hasFries = true;
            gameData->inventory[INGREDIENT_FRIES]--;
        }
    }
    
    // 添加番茄酱
    else if (mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_KETCHUP] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.hasKetchup) {
            gameData->currentShawarma.hasKetchup = true;
            gameData->inventory[INGREDIENT_KETCHUP]--;
        }
    }
    
    // 包装卷饼
    else if (mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->inventory[INGREDIENT_WRAPPER] > 0 && gameData->currentShawarma.hasBread && !gameData->currentShawarma.isWrapped) {
            gameData->currentShawarma.isWrapped = true;
            gameData->inventory[INGREDIENT_WRAPPER]--;
        }
    }
    
    // 交给顾客
    else if (mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->currentShawarma.isWrapped && !gameData->currentShawarma.isDelivered) {
            bool foundCustomer = false;
            
            // 检查是否满足顾客需求
            for (int i = 0; i < gameData->customerCount; i++) {
                Customer* customer = &gameData->customers[i];
                if (customer->needsShawarma && !customer->isSatisfied) {
                    // 检查卷饼是否匹配
                    bool matches = true;
                    if (gameData->currentShawarma.hasBread != customer->requestedShawarma.hasBread) matches = false;
                    if (gameData->currentShawarma.hasMeat != customer->requestedShawarma.hasMeat) matches = false;
                    if (gameData->currentShawarma.hasCucumber != customer->requestedShawarma.hasCucumber) matches = false;
                    if (gameData->currentShawarma.hasSauce != customer->requestedShawarma.hasSauce) matches = false;
                    if (gameData->currentShawarma.hasFries != customer->requestedShawarma.hasFries) matches = false;
                    if (gameData->currentShawarma.hasKetchup != customer->requestedShawarma.hasKetchup) matches = false;
                    
                    if (matches) {
                        customer->needsShawarma = false;
                        gameData->currentShawarma.isDelivered = true;
                        
                        // 检查顾客是否所有需求都已满足
                        if (!customer->needsShawarma && !customer->needsFries && !customer->needsCoke) {
                            customer->isSatisfied = true;
                            gameData->gold += gameData->goldPlate ? 15 : 10; // 金盘子升级增加卷饼价值
                        }
                        
                        // 重置当前卷饼
                        gameData->currentShawarma.hasBread = false;
                        gameData->currentShawarma.hasMeat = false;
                        gameData->currentShawarma.hasCucumber = false;
                        gameData->currentShawarma.hasSauce = false;
                        gameData->currentShawarma.hasFries = false;
                        gameData->currentShawarma.hasKetchup = false;
                        gameData->currentShawarma.isWrapped = false;
                        gameData->currentShawarma.isDelivered = false;
                        foundCustomer = true;
                        break;
                    }
                }
            }
        }
    }
    
    iconY += iconHeight + iconSpacing;
    
    // 拿薯条盒
    if (mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (!gameData->currentFries.hasBox && gameData->inventory[INGREDIENT_FRY_BOX] > 0) {
            gameData->currentFries.hasBox = true;
            gameData->inventory[INGREDIENT_FRY_BOX]--;
        }
    }
    
    // 装薯条
    else if (mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->currentFries.hasBox && !gameData->currentFries.hasFries && gameData->inventory[INGREDIENT_FRIES] > 0) {
            gameData->currentFries.hasFries = true;
            gameData->inventory[INGREDIENT_FRIES]--;
        }
    }
    
    // 交薯条
    else if (mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->currentFries.hasBox && gameData->currentFries.hasFries && !gameData->currentFries.isDelivered) {
            gameData->currentFries.isDelivered = true;
            
            // 检查是否满足顾客需求
            for (int i = 0; i < gameData->customerCount; i++) {
                Customer* customer = &gameData->customers[i];
                if (customer->needsFries && !customer->isSatisfied) {
                    customer->needsFries = false;
                    
                    // 检查顾客是否所有需求都已满足
                    if (!customer->needsShawarma && !customer->needsFries && !customer->needsCoke) {
                        customer->isSatisfied = true;
                        gameData->gold += 5;
                    }
                    
                    // 重置当前薯条
                    gameData->currentFries.hasBox = false;
                    gameData->currentFries.hasFries = false;
                    gameData->currentFries.isDelivered = false;
                    break;
                }
            }
        }
    }
    
    // 拿可乐杯
    else if (mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (!gameData->currentCoke.hasCup && gameData->inventory[INGREDIENT_COKE_CUP] > 0) {
            gameData->currentCoke.hasCup = true;
            gameData->inventory[INGREDIENT_COKE_CUP]--;
        }
    }
    
    iconY += iconHeight + iconSpacing;
    
    // 装可乐
    if (mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->currentCoke.hasCup && !gameData->currentCoke.hasCoke && gameData->inventory[INGREDIENT_COKE] > 0) {
            gameData->currentCoke.hasCoke = true;
            gameData->inventory[INGREDIENT_COKE]--;
        }
    }
    
    // 交可乐
    else if (mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight) {
        if (gameData->currentCoke.hasCup && gameData->currentCoke.hasCoke && !gameData->currentCoke.isDelivered) {
            gameData->currentCoke.isDelivered = true;
            
            // 检查是否满足顾客需求
            for (int i = 0; i < gameData->customerCount; i++) {
                Customer* customer = &gameData->customers[i];
                if (customer->needsCoke && !customer->isSatisfied) {
                    customer->needsCoke = false;
                    
                    // 检查顾客是否所有需求都已满足
                    if (!customer->needsShawarma && !customer->needsFries && !customer->needsCoke) {
                        customer->isSatisfied = true;
                        gameData->gold += 3;
                    }
                    
                    // 重置当前可乐
                    gameData->currentCoke.hasCup = false;
                    gameData->currentCoke.hasCoke = false;
                    gameData->currentCoke.isDelivered = false;
                    break;
                }
            }
        }
    }
    
    // 补货按钮
    else if (mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 2 * (iconWidth + iconSpacing) + buttonWidth && mouseY >= iconY && mouseY <= iconY + buttonHeight) {
        handleRestock(gameData);
    }
    
    // 切肉按钮
    else if (mouseX >= 290 + 2 * (iconWidth + iconSpacing) + buttonWidth + buttonSpacing && mouseX <= 290 + 2 * (iconWidth + iconSpacing) + 2 * buttonWidth + buttonSpacing && mouseY >= iconY && mouseY <= iconY + buttonHeight) {
        handlePrepMeat(gameData);
    }
    
    iconY += buttonHeight + buttonSpacing;
    
    // 切土豆按钮
    if (mouseX >= 290 && mouseX <= 290 + buttonWidth && mouseY >= iconY && mouseY <= iconY + buttonHeight) {
        handlePrepPotato(gameData);
    }
    
    // 炸薯条按钮
    else if (mouseX >= 290 + buttonWidth + buttonSpacing && mouseX <= 290 + 2 * buttonWidth + buttonSpacing && mouseY >= iconY && mouseY <= iconY + buttonHeight) {
        handleFryPotato(gameData);
    }
    
    // 丢弃按钮
    else if (mouseX >= 290 + 2 * (buttonWidth + buttonSpacing) && mouseX <= 290 + 3 * buttonWidth + 2 * buttonSpacing && mouseY >= iconY && mouseY <= iconY + buttonHeight) {
        // 清空当前制作的卷饼
        gameData->currentShawarma.hasBread = false;
        gameData->currentShawarma.hasMeat = false;
        gameData->currentShawarma.hasCucumber = false;
        gameData->currentShawarma.hasSauce = false;
        gameData->currentShawarma.hasFries = false;
        gameData->currentShawarma.hasKetchup = false;
        gameData->currentShawarma.isWrapped = false;
        gameData->currentShawarma.isDelivered = false;
        
        // 清空当前制作的薯条
        gameData->currentFries.hasBox = false;
        gameData->currentFries.hasFries = false;
        gameData->currentFries.isDelivered = false;
        
        // 清空当前制作的可乐
        gameData->currentCoke.hasCup = false;
        gameData->currentCoke.hasCoke = false;
        gameData->currentCoke.isDelivered = false;
    }
    
    // 处理点击乞丐的逻辑
    checkBeggarClick(gameData, mouseX, mouseY);
}

// 处理游戏结束界面点击
// @param gameData 游戏数据结构体指针
// @param mouseX 鼠标X坐标
// @param mouseY 鼠标Y坐标
void handleGameOverClick(GameData* gameData, int mouseX, int mouseY) {
    // 返回菜单按钮
    if (mouseX >= 350 && mouseX <= 650 && mouseY >= 400 && mouseY <= 450) {
        gameData->state = GAME_STATE_MENU;
        gameData->day++;
        
        // 重置游戏时间
        gameData->timeLeft = GAME_TIME_LIMIT;
        
        // 自动补充部分库存
        for (int i = 0; i < INGREDIENT_COUNT; i++) {
            gameData->inventory[i] += 5;
            if (gameData->inventory[i] > gameData->maxInventory[i]) {
                gameData->inventory[i] = gameData->maxInventory[i];
            }
        }
        
        // 如果有自动切肉机，补充肉
        if (gameData->autoMeatPrep) {
            gameData->inventory[INGREDIENT_MEAT] = gameData->maxInventory[INGREDIENT_MEAT];
        }
    }
}