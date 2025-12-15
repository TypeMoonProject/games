#include "src/include/my/render.h"
#include <stdio.h>

// 绘制带悬停效果的矩形
static void drawHoverRect(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color normalColor, SDL_Color hoverColor, bool hover) {
    if (hover) {
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    } else {
        SDL_SetRenderDrawColor(renderer, normalColor.r, normalColor.g, normalColor.b, normalColor.a);
    }
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &rect);
}

// 绘制矩形边框
static void drawBorder(SDL_Renderer* renderer, int x, int y, int width, int height, SDL_Color color, int borderWidth) {
    for (int i = 0; i < borderWidth; i++) {
        SDL_Rect borderRect = {x - i, y - i, width + 2 * i, height + 2 * i};
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        SDL_RenderDrawRect(renderer, &borderRect);
    }
}

// 渲染库存项
static void renderInventoryItem(SDL_Renderer* renderer, TTF_Font* font, const char* name, int amount, int maxAmount, int x, int y) {
    char inventoryText[100];
    sprintf(inventoryText, "%s: %d/%d", name, amount, maxAmount);
    renderText(renderer, font, inventoryText, x, y, (SDL_Color){0, 0, 0, 255});
}

// 渲染进度条
static void renderProgressBar(SDL_Renderer* renderer, int x, int y, int width, int height, int progress) {
    // 进度条背景
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect bgRect = {x, y, width, height};
    SDL_RenderFillRect(renderer, &bgRect);
    
    // 进度条填充
    SDL_SetRenderDrawColor(renderer, 0, 200, 0, 255);
    SDL_Rect fillRect = {x, y, width * progress / 100, height};
    SDL_RenderFillRect(renderer, &fillRect);
}

// 绘制原材料和食物的函数
void drawBread(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer,255,220,100,255);
    if(hover){
        SDL_SetRenderDrawColor(renderer,255,240,150,255);
    }
    SDL_Rect breadRect = {x, y, 60, 30};
    SDL_RenderFillRect(renderer, &breadRect);
    SDL_SetRenderDrawColor(renderer, 200, 150, 50, 255);
    for (int i = 0; i < 7; i++) {
        SDL_RenderDrawLine(renderer, x + 5 + i * 8, y + 2, x + 5 + i * 8, y + 28);
    }
}

void drawMeat(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer, 180, 50, 50, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 200, 70, 70, 255);
    }
    SDL_Rect meatRect = {x + 10, y + 5, 40, 20};
    SDL_RenderFillRect(renderer, &meatRect);
    
    SDL_SetRenderDrawColor(renderer, 150, 30, 30, 255);
    for (int i = 0; i < 5; i++) {
        SDL_RenderDrawLine(renderer, x + 14 + i * 8, y + 8, x + 14 + i * 8, y + 22);
    }
}

void drawCucumber(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer, 100, 200, 100, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 120, 220, 120, 255);
    }
    SDL_Rect cucumberRect = {x + 10, y + 10, 40, 12};
    SDL_RenderFillRect(renderer, &cucumberRect);
    SDL_SetRenderDrawColor(renderer, 70, 150, 70, 255);
    SDL_RenderDrawLine(renderer, x + 10, y + 12, x + 50, y + 12);
    SDL_RenderDrawLine(renderer, x + 10, y + 16, x + 50, y + 16);
}

void drawSauce(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer, 255, 150, 50, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 255, 180, 80, 255);
    }
    
    SDL_Point saucePoints[4] = {{x + 30, y + 2},{x + 60, y + 28},{x, y + 28},{x + 30, y + 2}
    };
    SDL_RenderDrawLines(renderer, saucePoints, 4);
    
    for (int i = y + 3; i < y + 28; i++) {
        int left = x + (i - (y + 2)) * (30) / 26;
        int right = x + 60 - (i - (y + 2)) * (30) / 26;
        SDL_RenderDrawLine(renderer, left, i, right, i);
    }
}

void drawFries(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer, 255, 220, 80, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 255, 240, 120, 255);
    }
    
    for (int i = 0; i < 6; i++) {
        SDL_Rect fryRect = {x + 12 + i * 8, y + 8, 6, 18};
        SDL_RenderFillRect(renderer, &fryRect);
    }
}

void drawKetchup(SDL_Renderer* renderer, int x, int y, bool hover) {
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 220, 70, 70, 255);
    }
    SDL_Rect bottleBody = {x + 15, y + 8, 30, 22};
    SDL_RenderFillRect(renderer, &bottleBody);
    
    // 瓶盖
    SDL_Rect bottleCap = {x + 22, y + 3, 16, 6};
    SDL_SetRenderDrawColor(renderer, 220, 220, 220, 255);
    SDL_RenderFillRect(renderer, &bottleCap);
}

void drawWrapper(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制包装纸（白色矩形）
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    }
    SDL_Rect wrapperRect = {x + 5, y + 5, 50, 20};
    SDL_RenderFillRect(renderer, &wrapperRect);
    
    // 添加纹理
    SDL_SetRenderDrawColor(renderer, 180, 180, 180, 255);
    SDL_RenderDrawLine(renderer, x + 5, y + 10, x + 55, y + 10);
    SDL_RenderDrawLine(renderer, x + 5, y + 15, x + 55, y + 15);
}

void drawFryBox(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制薯条盒（红色盒子）
    SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 220, 70, 70, 255);
    }
    
    // 盒子身体
    SDL_Rect boxBody = {x + 10, y + 8, 40, 22};
    SDL_RenderFillRect(renderer, &boxBody);
    
    // 盒盖
    SDL_Rect boxTop = {x + 5, y + 3, 50, 6};
    SDL_RenderFillRect(renderer, &boxTop);
}

void drawCokeCup(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制可乐杯（白色杯子）
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 250, 250, 250, 255);
    }
    
    // 杯子身体
    SDL_Rect cupBody = {x + 15, y + 10, 30, 20};
    SDL_RenderFillRect(renderer, &cupBody);
    
    // 杯盖
    SDL_Rect cupTop = {x + 18, y + 5, 24, 6};
    SDL_RenderFillRect(renderer, &cupTop);
}

void drawCoke(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 先绘制杯子
    drawCokeCup(renderer, x, y, hover);
    
    // 绘制可乐液体（深棕色）
    SDL_SetRenderDrawColor(renderer, 80, 20, 20, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 100, 40, 40, 255);
    }
    
    // 可乐液体（在杯子内部）
    SDL_Rect cokeLiquid = {x + 18, y + 13, 24, 14};
    SDL_RenderFillRect(renderer, &cokeLiquid);
    
    // 杯盖（保持白色）
    SDL_Rect cupTop = {x + 18, y + 5, 24, 6};
    SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255);
    SDL_RenderFillRect(renderer, &cupTop);
    
    // 泡沫
    SDL_SetRenderDrawColor(renderer, 255, 255, 200, 255);
    SDL_Rect foam = {x + 22, y + 12, 16, 4};
    SDL_RenderFillRect(renderer, &foam);
}

void drawFriesInBox(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制薯条盒（红色盒子）
    drawFryBox(renderer, x, y, hover);
    
    // 在盒子里绘制几根薯条
    SDL_SetRenderDrawColor(renderer, 255, 220, 80, 255);
    int fryPositions[4] = {x + 18, x + 25, x + 32, x + 39};
    for (int i = 0; i < 4; i++) {
        SDL_Rect fryRect = {fryPositions[i], y + 12, 4, 14};
        SDL_RenderFillRect(renderer, &fryRect);
    }
}

void drawDeliverIcon(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制交付图标（绿色箭头）
    SDL_SetRenderDrawColor(renderer, 50, 180, 50, 255);
    if (hover) {
        SDL_SetRenderDrawColor(renderer, 70, 200, 70, 255);
    }
    
    SDL_Point arrowPoints[4] = {
        {x + 40, y + 15},
        {x + 15, y + 8},
        {x + 15, y + 22},
        {x + 40, y + 15}
    };
    SDL_RenderDrawLines(renderer, arrowPoints, 4);
    
    for(int i = y + 6; i < y + 15; i++) {
        int right = x + 30 - (i - (y + 5)) * 20 / 10;
        SDL_RenderDrawLine(renderer, x + 10, i, right, i);
    }
}

void drawRestockIcon(SDL_Renderer* renderer, int x, int y, bool hover) {
    // 绘制补货图标（蓝色箱子）
    SDL_SetRenderDrawColor(renderer, 50, 50, 180, 255);
    if(hover) {
        SDL_SetRenderDrawColor(renderer, 70, 70, 200, 70);
    }
    // 箱子身体
    SDL_Rect boxBody = {x + 8, y + 5, 24, 14};
    SDL_RenderFillRect(renderer, &boxBody);
    
    // 箱子盖子
    SDL_Rect boxTop = {x + 10, y + 2, 20, 4};
    SDL_SetRenderDrawColor(renderer, 70, 70, 200, 255);
    SDL_RenderFillRect(renderer, &boxTop);
    
    // 箱子把手
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawLine(renderer, x + 15, y + 5, x + 25, y + 5);
}


void renderText(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, SDL_Color color) {
    if (text == NULL || text[0] == '\0') {
        return; 
    }
    // 创建文本表面
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, color);
    if (surface == NULL) {
        fprintf(stderr, "Failed to create text surface: %s\n", TTF_GetError());
        return;
    }
    // 从表面创建纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to create text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }
    // 获取文本尺寸
    int textWidth = surface->w;
    int textHeight = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}

// 渲染按钮
bool renderButton(SDL_Renderer* renderer, TTF_Font* font, const char* text, int x, int y, int width, int height, bool hover) {
    // 根据悬停状态设置按钮颜色
    SDL_Color buttonColor;
    if (hover) {
        buttonColor = (SDL_Color){100, 100, 100, 255};
    } else {
        buttonColor = (SDL_Color){150, 150, 150, 255};
    }
    SDL_Color textColor = (SDL_Color){255, 255, 255, 255};
    // 绘制按钮背景
    SDL_Rect rect = {x, y, width, height};
    SDL_SetRenderDrawColor(renderer, buttonColor.r, buttonColor.g, buttonColor.b, buttonColor.a);
    SDL_RenderFillRect(renderer, &rect);
    // 计算文本居中位置
    SDL_Surface* surface = TTF_RenderUTF8_Solid(font, text, textColor);
    if (surface == NULL) {
        fprintf(stderr, "Failed to create button text surface: %s\n", TTF_GetError());
        return false;
    }
    int textX = x + (width - surface->w) / 2;
    int textY = y + (height - surface->h) / 2;
    // 创建并渲染文本纹理
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
        fprintf(stderr, "Failed to create button text texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return false;
    }
    SDL_Rect textRect = {textX, textY, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    // 释放资源
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    return true;
}

void renderMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY) {
    // 设置温暖的背景色
    SDL_SetRenderDrawColor(renderer, 100, 60, 30, 255);
    SDL_RenderClear(renderer);
    // 渲染背景
    SDL_SetRenderDrawColor(renderer, 150, 100, 50, 255);
    SDL_Rect bgRect = {100, 100, 800, 550};
    SDL_RenderFillRect(renderer, &bgRect);
    // 渲染标题边框
    SDL_SetRenderDrawColor(renderer, 200, 150, 100, 255);
    SDL_Rect titleRect = {250, 80, 500, 100};
    SDL_RenderFillRect(renderer, &titleRect);
    // 渲染标题
    renderText(renderer, font, "沙威玛传奇", 350, 100, (SDL_Color){255, 255, 255, 255});
    // 渲染统计信息区域
    SDL_SetRenderDrawColor(renderer, 200, 150, 100, 255);
    SDL_Rect statsRect = {400, 200, 200, 80};
    SDL_RenderFillRect(renderer, &statsRect);
    // 渲染统计信息
    char dayText[50];
    char goldText[50];
    sprintf(dayText, "天数: %d", gameData->day);
    sprintf(goldText, "金币: %d", gameData->gold);
    renderText(renderer, font, dayText, 420, 220, (SDL_Color){255, 255, 255, 255});
    renderText(renderer, font, goldText, 420, 250, (SDL_Color){255, 255, 255, 255});
    // 渲染按钮
    bool startButtonHover = mouseX >= 350 && mouseX <= 650 && mouseY >= 320 && mouseY <= 370;
    renderButton(renderer, font, "开始新的一天", 350, 320, 300, 50, startButtonHover);
    // 渲染厨师形象在菜单上
    int chefX = 150;
    int chefY = 350;
    // 厨师身体
    SDL_SetRenderDrawColor(renderer, 200, 100, 50, 255);
    SDL_Rect chefBody = {chefX - 30, chefY, 60, 80};
    SDL_RenderFillRect(renderer, &chefBody);
    // 厨师头部
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_Rect chefHead = {chefX - 20, chefY - 40, 40, 40};
    SDL_RenderFillRect(renderer, &chefHead);
    // 厨师帽子
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_Rect chefHat1 = {chefX - 25, chefY - 50, 50, 15};
    SDL_RenderFillRect(renderer, &chefHat1);
    SDL_Rect chefHat2 = {chefX - 15, chefY - 60, 30, 20};
    SDL_RenderFillRect(renderer, &chefHat2);
    // 厨师手臂
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_Rect chefLeftArm = {chefX - 50, chefY + 10, 20, 50};
    SDL_RenderFillRect(renderer, &chefLeftArm);
    SDL_Rect chefRightArm = {chefX + 30, chefY + 10, 20, 50};
    SDL_RenderFillRect(renderer, &chefRightArm);
    // 渲染顾客形象在菜单上
    int customerX = 800;
    int customerY = 350;
    // 顾客身体
    SDL_SetRenderDrawColor(renderer, 50, 100, 150, 255);
    SDL_Rect customerBody = {customerX - 30, customerY, 60, 80};
    SDL_RenderFillRect(renderer, &customerBody);
    // 顾客头部
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_Rect customerHead = {customerX - 20, customerY - 40, 40, 40};
    SDL_RenderFillRect(renderer, &customerHead);
    // 顾客手臂
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_Rect customerLeftArm = {customerX - 50, customerY + 10, 20, 50};
    SDL_RenderFillRect(renderer, &customerLeftArm);
    SDL_Rect customerRightArm = {customerX + 30, customerY + 10, 20, 50};
    SDL_RenderFillRect(renderer, &customerRightArm);
}

//绘制人物
void drawMan(SDL_Renderer *renderer,int x,int y,int judge){
    SDL_Rect Head = {x-20,y-40,40,40};
    SDL_Rect Body = {x-30,y,60,80};
    SDL_Rect Hat1 = {x-25,y-50,50,15};
    SDL_Rect Hat2 = {x-15,y-60,30,20};
    SDL_Rect LeftArm = {x-50,y+10,20,50};
    SDL_Rect RightArm = {x+30,y+10,20,50};
    
    // 身体
    SDL_SetRenderDrawColor(renderer, 200, 100, 50, 255);
    SDL_RenderFillRect(renderer, &Body);
    // 头部
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_RenderFillRect(renderer, &Head);
    // 手臂
    SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
    SDL_RenderFillRect(renderer, &LeftArm);
    SDL_RenderFillRect(renderer, &RightArm);
    if(judge==1){
        // 帽子
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &Hat1);
        SDL_RenderFillRect(renderer, &Hat2);
    }
}

//游戏界面
void renderGame(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY) {
    // 清空屏幕
    SDL_SetRenderDrawColor(renderer, 255, 245, 230, 255);
    SDL_RenderClear(renderer);
    
    // 渲染游戏界面边框
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_Rect borderRect = {50, 50, 1100, 800};
    SDL_RenderDrawRect(renderer, &borderRect);
    
    // 渲染状态栏
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
    SDL_Rect statusBarRect = {60, 60, 1080, 50};
    SDL_RenderFillRect(renderer, &statusBarRect);
    
    // 渲染状态栏文本
    char dayText[50];
    char goldText[50];
    char timeText[50];
    sprintf(dayText, "第 %d 天", gameData->day);
    sprintf(goldText, "金币: %d", gameData->gold);
    sprintf(timeText, "剩余时间: %d 秒", gameData->timeLeft);
    renderText(renderer, font, dayText, 80, 70, (SDL_Color){255, 255, 255, 255});
    renderText(renderer, font, goldText, 450, 70, (SDL_Color){255, 255, 255, 255});
    renderText(renderer, font, timeText, 750, 70, (SDL_Color){255, 255, 255, 255});
    
    // 渲染库存区域
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect inventoryRect = {60, 120, 200, 450};
    SDL_RenderFillRect(renderer, &inventoryRect);
    
    SDL_Color inventoryTextColor = {0, 0, 0, 255};
    renderText(renderer, font, "库存", 140, 130, inventoryTextColor);
    
    // 渲染库存项目
    renderInventoryItem(renderer, font, "面饼", gameData->inventory[INGREDIENT_BREAD], gameData->maxInventory[INGREDIENT_BREAD], 70, 160);
    renderInventoryItem(renderer, font, "肉", gameData->inventory[INGREDIENT_MEAT], gameData->maxInventory[INGREDIENT_MEAT], 70, 190);
    renderInventoryItem(renderer, font, "黄瓜", gameData->inventory[INGREDIENT_CUCUMBER], gameData->maxInventory[INGREDIENT_CUCUMBER], 70, 220);
    renderInventoryItem(renderer, font, "沙司", gameData->inventory[INGREDIENT_SAUCE], gameData->maxInventory[INGREDIENT_SAUCE], 70, 250);
    
    // 渲染升级按钮
    bool upgradeButtonHover = mouseX >= 950 && mouseX <= 1050 && mouseY >= 60 && mouseY <= 100;
    renderButton(renderer, font, "升级店铺", 950, 60, 100, 40, upgradeButtonHover);
    
    renderInventoryItem(renderer, font, "薯条", gameData->inventory[INGREDIENT_FRIES], gameData->maxInventory[INGREDIENT_FRIES], 70, 280);
    renderInventoryItem(renderer, font, "番茄酱", gameData->inventory[INGREDIENT_KETCHUP], gameData->maxInventory[INGREDIENT_KETCHUP], 70, 310);
    renderInventoryItem(renderer, font, "可乐", gameData->inventory[INGREDIENT_COKE], gameData->maxInventory[INGREDIENT_COKE], 70, 340);
    renderInventoryItem(renderer, font, "包装纸", gameData->inventory[INGREDIENT_WRAPPER], gameData->maxInventory[INGREDIENT_WRAPPER], 70, 370);
    renderInventoryItem(renderer, font, "薯条盒", gameData->inventory[INGREDIENT_FRY_BOX], gameData->maxInventory[INGREDIENT_FRY_BOX], 70, 400);
    renderInventoryItem(renderer, font, "可乐杯", gameData->inventory[INGREDIENT_COKE_CUP], gameData->maxInventory[INGREDIENT_COKE_CUP], 70, 430);
    
    // 渲染厨师形象
    int chefX = 100;
    int chefY = 480;
    drawMan(renderer,chefX,chefY,1);
    
    // 渲染顾客区域
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect customerAreaRect = {280, 120, 850, 200};
    SDL_RenderFillRect(renderer, &customerAreaRect);
    
    SDL_Color customerTextColor = {0, 0, 0, 255};
    renderText(renderer, font, "顾客", 580, 130, customerTextColor);
    
    // 渲染顾客
    for (int i = 0; i < gameData->customerCount; i++) {
        Customer* customer = &gameData->customers[i];
        int x = 300 + i * 180;
        int y = 160;
        
        // 顾客背景 - 根据顾客类型设置不同颜色
        SDL_SetRenderDrawColor(renderer, customer->type == CUSTOMER_TYPE_BEGGAR ? 200 : 150, 
                               customer->type == CUSTOMER_TYPE_BEGGAR ? 150 : 180, 
                               customer->type == CUSTOMER_TYPE_BEGGAR ? 150 : 200, 255);
        SDL_Rect customerRect = {x, y, 160, 140};
        SDL_RenderFillRect(renderer, &customerRect);
        
        // 渲染顾客形象
        // 顾客头部
        SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
        SDL_Rect customerHead = {x + 60, y + 10, 40, 40};
        SDL_RenderFillRect(renderer, &customerHead);
        
        // 顾客身体
        SDL_SetRenderDrawColor(renderer, customer->type == CUSTOMER_TYPE_BEGGAR ? 100 : 50, 
                               customer->type == CUSTOMER_TYPE_BEGGAR ? 50 : 100, 
                               customer->type == CUSTOMER_TYPE_BEGGAR ? 50 : 150, 255);
        SDL_Rect customerBody = {x + 50, y + 50, 60, 60};
        SDL_RenderFillRect(renderer, &customerBody);
        
        // 顾客手臂
        SDL_SetRenderDrawColor(renderer, 255, 220, 180, 255);
        SDL_Rect customerLeftArm = {x + 30, y + 60, 20, 40};
        SDL_Rect customerRightArm = {x + 110, y + 60, 20, 40};
        SDL_RenderFillRect(renderer, &customerLeftArm);
        SDL_RenderFillRect(renderer, &customerRightArm);
        
        // 渲染顾客类型标识
        if (customer->type == CUSTOMER_TYPE_BEGGAR) {
            renderText(renderer, font, "乞丐", x + 10, y + 20, (SDL_Color){255, 0, 0, 255});
        }
        
        // 渲染顾客需求
        char customerText[50] = "";
        if (customer->needsShawarma) strcat(customerText, "卷饼 ");
        if (customer->needsFries) strcat(customerText, "薯条 ");
        if (customer->needsCoke) strcat(customerText, "可乐");
        renderText(renderer, font, customerText, x + 10, y + 120, (SDL_Color){0, 0, 0, 255});
        
        // 渲染卷饼具体配料需求
        if (customer->needsShawarma) {
            char shawarmaDetails[100] = "";
            if (customer->requestedShawarma.hasMeat) strcat(shawarmaDetails, "肉 ");
            if (customer->requestedShawarma.hasCucumber) strcat(shawarmaDetails, "黄瓜 ");
            if (customer->requestedShawarma.hasSauce) strcat(shawarmaDetails, "酱 ");
            if (customer->requestedShawarma.hasFries) strcat(shawarmaDetails, "薯条 ");
            if (customer->requestedShawarma.hasKetchup) strcat(shawarmaDetails, "番茄酱");
            
            if (strlen(shawarmaDetails) > 0) {
                renderText(renderer, font, shawarmaDetails, x + 10, y + 160, (SDL_Color){0, 0, 0, 255});
            }
        }
        
        // 渲染耐心条
        int patienceWidth = (customer->patience * 140) / customer->maxPatience;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_Rect patienceRect = {x + 10, y + 145, patienceWidth, 10};
        SDL_RenderFillRect(renderer, &patienceRect);
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect patienceBorderRect = {x + 10, y + 145, 140, 10};
        SDL_RenderDrawRect(renderer, &patienceBorderRect);
        
        // 渲染乞丐逃跑提示
        if (customer->type == CUSTOMER_TYPE_BEGGAR && customer->isRunningAway) {
            renderText(renderer, font, "点击抓住!", x + 10, y + 160, (SDL_Color){255, 255, 0, 255});
            
            // 逃跑动画效果 - 闪烁边框
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            for (int j = 0; j < 3; j++) {
                SDL_Rect flashRect = {x - j, y - j, 160 + 2 * j, 140 + 2 * j};
                SDL_RenderDrawRect(renderer, &flashRect);
            }
        }
    }
    
    // 渲染制作区域
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect craftingAreaRect = {280, 340, 850, 120};
    SDL_RenderFillRect(renderer, &craftingAreaRect);
    
    SDL_Color craftingTextColor = {0, 0, 0, 255};
    renderText(renderer, font, "制作区域", 580, 350, craftingTextColor);
    
    // 渲染当前制作的餐品
    int shawarmaX = 290;
    int shawarmaY = 390;
    int itemSize = 60;
    
    // 渲染当前卷饼的重叠效果
    if (gameData->currentShawarma.hasBread) {
        // 面包
        drawBread(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.hasSauce) {
        // 酱料在面包上
        drawSauce(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.hasMeat) {
        // 肉在酱料上
        drawMeat(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.hasCucumber) {
        // 黄瓜在肉上
        drawCucumber(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.hasFries) {
        // 薯条在黄瓜上
        drawFries(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.hasKetchup) {
        // 番茄酱在最上层
        drawKetchup(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    if (gameData->currentShawarma.isWrapped) {
        // 如果已包装，在最外层绘制包装纸
        drawWrapper(renderer, shawarmaX + 90, shawarmaY - 10, false);
    }
    
    // 渲染当前薯条
    if (gameData->currentFries.hasBox) {
        // 先绘制薯条盒
        drawFryBox(renderer, shawarmaX + 90, shawarmaY + itemSize - 10, false);
        
        if (gameData->currentFries.hasFries) {
            // 如果有薯条，绘制在盒子里
            drawFries(renderer, shawarmaX + 90, shawarmaY + itemSize - 10, false);
        }
    }
    
    // 渲染当前可乐
    if (gameData->currentCoke.hasCup) {
        // 先绘制可乐杯（调整位置，避免被按钮区域遮挡）
        drawCokeCup(renderer, shawarmaX + 200, shawarmaY - 10, false);
        
        if (gameData->currentCoke.hasCoke) {
            // 如果有可乐，绘制在杯子里（调整位置，避免被按钮区域遮挡）
            drawCoke(renderer, shawarmaX + 200, shawarmaY - 10, false);
        }
    }
    
    // 渲染按钮区域
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_Rect buttonsRect = {280, 480, 850, 190};
    SDL_RenderFillRect(renderer, &buttonsRect);
    int iconY = 510;
    int iconWidth = 80;
    int iconHeight = 45;
    int iconSpacing = 25;
    bool placeBreadHover = mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawBread(renderer, 290, iconY, placeBreadHover);
    bool addMeatHover = mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawMeat(renderer, 290 + iconWidth + iconSpacing, iconY, addMeatHover);
    bool addCucumberHover = mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawCucumber(renderer, 290 + 2 * (iconWidth + iconSpacing), iconY, addCucumberHover);
    bool addSauceHover = mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawSauce(renderer, 290 + 3 * (iconWidth + iconSpacing), iconY, addSauceHover);
    iconY += iconHeight + iconSpacing;
    bool addFriesHover = mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawFries(renderer, 290, iconY, addFriesHover);
    
    // 添加番茄酱
    bool addKetchupHover = mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawKetchup(renderer, 290 + iconWidth + iconSpacing, iconY, addKetchupHover);
    
    // 包装卷饼
    bool wrapShawarmaHover = mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawWrapper(renderer, 290 + 2 * (iconWidth + iconSpacing), iconY, wrapShawarmaHover);
    
    // 交给顾客
    bool deliverShawarmaHover = mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawDeliverIcon(renderer, 290 + 3 * (iconWidth + iconSpacing), iconY, deliverShawarmaHover);
    
    // 薯条制作区域
    iconY += iconHeight + iconSpacing;
    
    // 拿薯条盒
    bool takeFryBoxHover = mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawFryBox(renderer, 290, iconY, takeFryBoxHover);
    
    // 装薯条
    bool addFriesToBoxHover = mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawFriesInBox(renderer, 290 + iconWidth + iconSpacing, iconY, addFriesToBoxHover);
    
    // 交薯条
    bool deliverFriesHover = mouseX >= 290 + 2 * (iconWidth + iconSpacing) && mouseX <= 290 + 3 * iconWidth + 2 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawDeliverIcon(renderer, 290 + 2 * (iconWidth + iconSpacing), iconY, deliverFriesHover);
    
    // 拿可乐杯
    bool takeCokeCupHover = mouseX >= 290 + 3 * (iconWidth + iconSpacing) && mouseX <= 290 + 4 * iconWidth + 3 * iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawCokeCup(renderer, 290 + 3 * (iconWidth + iconSpacing), iconY, takeCokeCupHover);
    
    // 可乐制作区域
    iconY += iconHeight + iconSpacing;
    
    // 装可乐
    bool addCokeToCupHover = mouseX >= 290 && mouseX <= 290 + iconWidth && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawCoke(renderer, 290, iconY, addCokeToCupHover);
    
    // 交可乐
    bool deliverCokeHover = mouseX >= 290 + iconWidth + iconSpacing && mouseX <= 290 + 2 * iconWidth + iconSpacing && mouseY >= iconY && mouseY <= iconY + iconHeight;
    drawDeliverIcon(renderer, 290 + iconWidth + iconSpacing, iconY, deliverCokeHover);
    
    // 渲染补货和预处理按钮
    int buttonY = iconY;
    int buttonWidth = 120;
    int buttonHeight = 35;
    int buttonSpacing = 20;
    
    // 使用结构体数组简化按钮渲染
    typedef struct {
        int x;
        int y;
        const char* text;
    } Button;
    
    Button buttons[] = {
        {290 + 2 * (iconWidth + iconSpacing), buttonY, "补货"},
        {290 + 2 * (iconWidth + iconSpacing) + buttonWidth + buttonSpacing, buttonY, "切肉"},
        {290, buttonY + buttonHeight + buttonSpacing, "切土豆"},
        {290 + buttonWidth + buttonSpacing, buttonY + buttonHeight + buttonSpacing, "炸薯条"},
        {290 + 2 * (buttonWidth + buttonSpacing), buttonY + buttonHeight + buttonSpacing, "丢弃"}
    };
    
    int buttonCount = sizeof(buttons) / sizeof(buttons[0]);
    
    for (int i = 0; i < buttonCount; i++) {
        Button btn = buttons[i];
        bool hover = mouseX >= btn.x && mouseX <= btn.x + buttonWidth && mouseY >= btn.y && mouseY <= btn.y + buttonHeight;
        renderButton(renderer, font, btn.text, btn.x, btn.y, buttonWidth, buttonHeight, hover);
    }
    
    //烹饪进度条
    buttonY += buttonHeight + buttonSpacing;
    
    if (gameData->currentCookingState != COOKING_STATE_IDLE) {
        //烹饪状态文本
        const char* cookingText;
        switch (gameData->currentCookingState) {
            case COOKING_STATE_PREP_MEAT:
                cookingText = "切肉中...";
                break;
            case COOKING_STATE_PREP_POTATO:
                cookingText = "切土豆中...";
                break;
            case COOKING_STATE_FRY_POTATO:
                cookingText = "炸薯条中...";
                break;
            default:
                cookingText = "烹饪中...";
                break;
        }
        
        //烹饪状态文本
        renderText(renderer, font, cookingText, 290, buttonY, (SDL_Color){255, 255, 255, 255});
        
        // 渲染进度条
        buttonY += 30;
        renderProgressBar(renderer, 290, buttonY, 4 * buttonWidth + 3 * buttonSpacing, 20, gameData->cookingProgress);
        
        // 渲染进度百分比文本
        char progressText[20];
        sprintf(progressText, "%d%%", gameData->cookingProgress);
        int textX = 290 + (4 * buttonWidth + 3 * buttonSpacing) / 2 - 30; // 粗略居中
        renderText(renderer, font, progressText, textX, buttonY + 2, (SDL_Color){0, 0, 0, 255});
    }
}

//游戏结束界面
void renderGameOver(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, int mouseX, int mouseY) {
    // 设置背景色并清空屏幕
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    
    // 渲染游戏结束文本
    renderText(renderer, font, "游戏结束", 320, 150, (SDL_Color){255, 255, 255, 255});
    
    // 渲染金币统计
    char goldText[100];
    sprintf(goldText, "当天获得金币: %d", gameData->gold);
    renderText(renderer, font, goldText, 300, 250, (SDL_Color){255, 255, 255, 255});
    
    sprintf(goldText, "累计金币: %d", gameData->gold);
    renderText(renderer, font, goldText, 300, 300, (SDL_Color){255, 255, 255, 255});
    
    // 渲染继续按钮
    bool continueButtonHover = mouseX >= 350 && mouseX <= 650 && mouseY >= 400 && mouseY <= 450;
    renderButton(renderer, font, "继续", 350, 400, 300, 50, continueButtonHover);
}

//渲染升级界面
void renderUpgradeMenu(SDL_Renderer* renderer, TTF_Font* font, GameData* gameData, UpgradeData* upgradeData, int mouseX, int mouseY) {
    // 设置背景色并清空屏幕
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);
    // 渲染标题和金币信息
    renderText(renderer, font, "店铺升级", 320, 100, (SDL_Color){255, 255, 255, 255});
    
    char goldText[100];
    sprintf(goldText, "当前金币: %d", gameData->gold);
    renderText(renderer, font, goldText, 330, 150, (SDL_Color){255, 255, 255, 255});
    // 设置按钮参数
    int buttonY = 200;
    int buttonWidth = 400;
    int buttonHeight = 60;
    int buttonSpacing = 20;
    // 自动切肉机升级按钮
    bool autoMeatPrepHover = mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
    char autoMeatPrepText[100];
    if (gameData->autoMeatPrep) {
        strcpy(autoMeatPrepText, "自动切肉机 - 已购买");
    } else {
        strcpy(autoMeatPrepText, "自动切肉机 - 50 金币");
    }
    renderButton(renderer, font, autoMeatPrepText, 200, buttonY, buttonWidth, buttonHeight, autoMeatPrepHover);
    buttonY += buttonHeight + buttonSpacing;
    // 金盘子升级按钮
    bool goldPlateHover = mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
    char goldPlateText[100];
    if (gameData->goldPlate) {
        strcpy(goldPlateText, "金盘子 - 已购买");
    } else {
        strcpy(goldPlateText, "金盘子 - 100 金币");
    }
    renderButton(renderer, font, goldPlateText, 200, buttonY, buttonWidth, buttonHeight, goldPlateHover);
    buttonY += buttonHeight + buttonSpacing;
    // 扩充店面前往升级按钮
    bool expandShopHover = mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
    char expandShopText[100];
    sprintf(expandShopText, "扩充店面 - %d 金币", (gameData->maxCustomers - MAX_CUSTOMERS) * 100 + 150);
    renderButton(renderer, font, expandShopText, 200, buttonY, buttonWidth, buttonHeight, expandShopHover);
    buttonY += buttonHeight + buttonSpacing;
    // 返回按钮
    bool backButtonHover = mouseX >= 200 && mouseX <= 200 + buttonWidth && mouseY >= buttonY && mouseY <= buttonY + buttonHeight;
    renderButton(renderer, font, "返回", 200, buttonY, buttonWidth, buttonHeight, backButtonHover);
}
