#include "src/include/my/beggar_mechanics.h"
#include "src/include/my/game_definitions.h"
#include "src/include/my/game_logic.h"
#include <stdio.h>

//检查是否点击了正在逃跑的乞丐
void checkBeggarClick(GameData* gameData,int mouseX,int mouseY) {
    int i=0;
    int customerX=200+i*180;
    int customerY=180;
    int customerWidth=160;
    int customerHeight=140;
    // 检查是否点击了正在逃跑的乞丐
    for (i=0;i<gameData->customerCount;i++){
        Customer* customer=&gameData->customers[i];
        if (customer->type==CUSTOMER_TYPE_BEGGAR&&customer->isRunningAway) {
            if (mouseX>=customerX&&mouseX<=customerX+customerWidth&&mouseY>=customerY&&mouseY<=customerY+customerHeight) {
                catchEscapingBeggar(gameData,i);
                break;
            }
        }
    }
}

//生成随机顾客，包含乞丐
void generateBeggar(GameData* gameData) {
    if(gameData->customerCount<gameData->maxCustomers){
        Customer newCustomer=generateCustomer();
        if(newCustomer.type==CUSTOMER_TYPE_BEGGAR&&!gameData->hasActiveBeggar){
            gameData->customers[gameData->customerCount++]=newCustomer;
            gameData->hasActiveBeggar=true;
        }else if(newCustomer.type==CUSTOMER_TYPE_NORMAL){
            gameData->customers[gameData->customerCount++]=newCustomer;
        }
    }
}

//处理乞丐的逃跑逻辑
bool BeggarEscape(GameData* gameData,Customer* customer,int customerIndex) {
    if(customer->type==CUSTOMER_TYPE_BEGGAR) {
        customer->timeSinceSatisfaction++;       
        if(customer->timeSinceSatisfaction >= 3) {
            customer->isRunningAway = true;
            if (customer->timeSinceSatisfaction >= 5) {
                for (int j=customerIndex;j<gameData->customerCount-1;j++) {
                    gameData->customers[j] = gameData->customers[j+1];
                }gameData->customerCount--;
                gameData->hasActiveBeggar=false;
                return true;
            }
        }
    }
    return false;
}

//抓住逃跑的乞丐，获得奖励
void catchEscapingBeggar(GameData* gameData,int customerIndex) {
    gameData->gold+=gameData->beggarEscapeReward;
    for(int j=customerIndex;j<gameData->customerCount-1;j++) {
        gameData->customers[j]=gameData->customers[j+1];
    }
    gameData->customerCount--;
    gameData->hasActiveBeggar=false;
}
