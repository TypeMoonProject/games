#include "src/include/my/game_logic.h"
#include "src/include/my/beggar_mechanics.h"
#include "src/include/my/input_handling.h"

//补货
void handleRestock(GameData* gameData){
    int i=0;
    for(i=0;i<INGREDIENT_COUNT;i++){
        gameData->inventory[i] = gameData->maxInventory[i];
    }
}

//切肉
void handlePrepMeat(GameData* gameData){
    if(gameData->currentCookingState==COOKING_STATE_IDLE){
        gameData->currentCookingState=COOKING_STATE_PREP_MEAT;
        gameData->cookingProgress=0;
        gameData->cookingTimer=0;
    }
}

//切土豆
void handlePrepPotato(GameData* gameData){
    if(gameData->currentCookingState==COOKING_STATE_IDLE){
        gameData->currentCookingState=COOKING_STATE_PREP_POTATO;
        gameData->cookingProgress=0;
        gameData->cookingTimer=0;
    }
}

//炸薯条
void handleFryPotato(GameData* gameData){
    if(gameData->currentCookingState==COOKING_STATE_IDLE){
        gameData->currentCookingState=COOKING_STATE_FRY_POTATO;
        gameData->cookingProgress=0;
        gameData->cookingTimer=0;
    }
}


// 更新游戏逻辑
void updateGame(GameData* gameData){
    gameData->timeLeft--;
    if(gameData->timeLeft<=0){
        gameData->state=GAME_STATE_GAME_OVER;
        return;
    }if(gameData->currentCookingState!=COOKING_STATE_IDLE){
        gameData->cookingTimer++;
        int cookTime=0;
        switch(gameData->currentCookingState){
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
        gameData->cookingProgress=(gameData->cookingTimer*100)/cookTime;
        if(gameData->cookingTimer>=cookTime){
            switch(gameData->currentCookingState){
                case COOKING_STATE_PREP_MEAT:
                    if(gameData->inventory[INGREDIENT_MEAT]<gameData->maxInventory[INGREDIENT_MEAT]){
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
                    break;
            }gameData->currentCookingState=COOKING_STATE_IDLE;
            gameData->cookingProgress=0;
            gameData->cookingTimer=0;
        }
    }
    if (gameData->customerCount<gameData->maxCustomers&&getRandomInt(0,99)<50) {
        generateBeggar(gameData);
    }
    for (int i=0;i<gameData->customerCount;i++) {
        Customer* customer=&gameData->customers[i];
        
        if (!customer->isSatisfied) {
            customer->patience--;
            if (customer->patience <= 0) {
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
            if (customer->type == CUSTOMER_TYPE_BEGGAR) {
                if (BeggarEscape(gameData, &gameData->customers[i], i)) {
                    i--;
                }
            } else {
                customer->timeSinceSatisfaction++;
                for (int j = i; j < gameData->customerCount - 1; j++) {
                    gameData->customers[j] = gameData->customers[j + 1];
                }
                gameData->customerCount--;
                i--;
            }
        }
    }
}
