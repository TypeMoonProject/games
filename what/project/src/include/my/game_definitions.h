#ifndef GAME_DEFINITIONS_H
#define GAME_DEFINITIONS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h> // bool类型
#include <stdlib.h>  
#include <time.h>    

// 游戏常量定义
#define WINDOW_WIDTH 1200        // 窗口宽度（像素）
#define WINDOW_HEIGHT 900        // 窗口高度（像素）
#define GAME_TIME_LIMIT 120      // 每局游戏时间限制（秒）
#define MAX_CUSTOMERS 3          // 店铺最大容纳顾客数
#define MAX_INVENTORY 50         // 库存上限

// 烹饪时间常量（游戏帧）
#define COOK_TIME_PREP_MEAT 30   // 切肉时间（约1秒，30帧）
#define COOK_TIME_PREP_POTATO 20 // 切土豆时间（约0.67秒，20帧）
#define COOK_TIME_FRY_POTATO 60  // 炸薯条时间（约2秒，60帧）

// 游戏状态枚举
// 定义游戏的不同状态
typedef enum {
    GAME_STATE_MENU,      // 菜单状态
    GAME_STATE_PLAYING,   // 游戏中状态
    GAME_STATE_GAME_OVER, // 游戏结束状态
    GAME_STATE_UPGRADE    // 升级菜单状态
} GameState;

// 食材和耗材枚举
// 定义游戏中所有的食材和耗材类型
typedef enum {
    INGREDIENT_BREAD,      // 面包
    INGREDIENT_MEAT,       // 肉
    INGREDIENT_CUCUMBER,   // 黄瓜
    INGREDIENT_SAUCE,      // 酱料
    INGREDIENT_FRIES,      // 薯条（已炸好）
    INGREDIENT_KETCHUP,    // 番茄酱
    INGREDIENT_COKE,       // 可乐
    INGREDIENT_WRAPPER,    // 包装纸
    INGREDIENT_FRY_BOX,    // 薯条盒
    INGREDIENT_COKE_CUP,   // 可乐杯
    INGREDIENT_COUNT       // 食材总数
} Ingredient;

// 烹饪状态枚举
// 定义烹饪过程的不同状态
typedef enum {
    COOKING_STATE_IDLE,           // 空闲状态
    COOKING_STATE_PREP_MEAT,      // 切肉状态
    COOKING_STATE_PREP_POTATO,    // 切土豆状态
    COOKING_STATE_FRY_POTATO      // 炸薯条状态
} CookingState;

// 餐品类型枚举
// 定义游戏中可以制作的餐品类型
typedef enum {
    FOOD_TYPE_SHAWARMA,  // 卷饼
    FOOD_TYPE_FRIES,     // 薯条
    FOOD_TYPE_COKE       // 可乐
} FoodType;

// 卷饼结构体
// 定义卷饼的各个组成部分和状态
typedef struct {
    bool hasBread;     // 是否有面包
    bool hasMeat;      // 是否有肉
    bool hasCucumber;  // 是否有黄瓜
    bool hasSauce;     // 是否有酱料
    bool hasFries;     // 是否有薯条
    bool hasKetchup;   // 是否有番茄酱
    bool isWrapped;    // 是否已包装
    bool isDelivered;  // 是否已交付
} Shawarma;

// 薯条结构体
// 定义薯条的各个组成部分和状态
typedef struct {
    bool hasBox;      // 是否有包装盒
    bool hasFries;    // 是否有薯条
    bool isDelivered; // 是否已交付
} Fries;

// 可乐结构体
// 定义可乐的各个组成部分和状态
typedef struct {
    bool hasCup;      // 是否有杯子
    bool hasCoke;     // 是否有可乐
    bool isDelivered; // 是否已交付
} Coke;

// 顾客类型枚举
// 定义顾客的不同类型
typedef enum {
    CUSTOMER_TYPE_NORMAL,  // 普通顾客
    CUSTOMER_TYPE_BEGGAR   // 乞丐
} CustomerType;

// 顾客结构体
// 定义顾客的属性和需求
typedef struct {
    int patience;               // 当前耐心值
    int maxPatience;            // 最大耐心值
    bool needsShawarma;         // 是否需要卷饼
    bool needsFries;            // 是否需要薯条
    bool needsCoke;             // 是否需要可乐
    Shawarma requestedShawarma; // 请求的卷饼配置
    bool isSatisfied;           // 是否已满意
    CustomerType type;          // 顾客类型
    bool isRunningAway;         // 是否正在逃跑
    int timeSinceSatisfaction;  // 满意后的时间计数
} Customer;

// 游戏数据结构体
// 定义游戏的所有数据
typedef struct {
    GameState state;                       // 游戏状态
    int day;                               // 当前天数
    int gold;                              // 当前金币数
    int timeLeft;                          // 剩余时间
    int inventory[INGREDIENT_COUNT];       // 库存数量
    int maxInventory[INGREDIENT_COUNT];    // 最大库存数量
    Customer customers[MAX_CUSTOMERS];     // 顾客数组（C风格数组）
    int customerCount;                     // 当前顾客数量
    Shawarma currentShawarma;              // 当前制作的卷饼
    Fries currentFries;                    // 当前制作的薯条
    Coke currentCoke;                      // 当前制作的可乐
    bool autoMeatPrep;                     // 是否自动切肉
    bool goldPlate;                        // 是否有金牌
    int maxCustomers;                      // 最大顾客数量
    bool hasActiveBeggar;                  // 标记是否有活跃的乞丐
    int beggarEscapeReward;                // 抓住逃跑乞丐的奖励金币
    
    // 烹饪相关字段
    CookingState currentCookingState;      // 当前烹饪状态
    int cookingProgress;                   // 烹饪进度（0-100）
    int cookingTimer;                      // 烹饪计时器（游戏帧）
} GameData;

// 升级界面状态枚举
// 定义升级界面的不同状态
typedef enum {
    UPGRADE_STATE_MAIN,    // 主升级界面
    UPGRADE_STATE_BUY      // 购买升级界面
} UpgradeState;

// 升级数据结构体
// 定义升级界面的数据
typedef struct {
    UpgradeState state;     // 升级界面状态
} UpgradeData;

// 生成指定范围内的随机整数
// @param min 最小值（包含）
// @param max 最大值（包含）
// @return 生成的随机整数
int getRandomInt(int min, int max);

#endif // GAME_DEFINITIONS_H
