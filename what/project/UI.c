#include<SDL2/SDL.h>
#include<SDL2/SDL_ttf.h>
#include<SDL2/SDL_image.h>
#include<SDL2/SDL_surface.h>
#include<stdbool.h>
#include<stdio.h>

const int WIDTH=1000;
const int HIGHT=750;

typedef struct color{
    int r;
    int g;
    int b;
    int a;
}color;

//初始化和创建窗口
SDL_Window* init_creat(){
    if(SDL_Init(SDL_INIT_VIDEO)!=0){
        SDL_Log("INIT UI FAILED:%s",SDL_GetError());
    }
    SDL_Window *win=SDL_CreateWindow("game",
                                    SDL_WINDOWPOS_CENTERED,//x轴居中
                                    SDL_WINDOWPOS_CENTERED,//y轴居中
                                    WIDTH,                 //宽
                                    HIGHT,                 //高
                                    SDL_WINDOW_RESIZABLE   //大小可变
                                );
    if(win==NULL){
        SDL_Log("CREATE UI FAILED:%s",SDL_GetError());
    }
    return win;
}

//创建渲染器
SDL_Renderer *create_renderer(SDL_Window *win){
    SDL_Renderer *ren=SDL_CreateRenderer(win,                   //创建渲染器的窗口
                                        -1,                     //自动寻找
                                        SDL_RENDERER_ACCELERATED//使用硬件加速
                                    );
    if(ren==NULL){
        SDL_Log("CREATE RENDERER FAILED:%s",SDL_GetError());
    }
    //设置混合模式
    SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND);
    return ren;
}

//下载图片
SDL_Surface *load_image(char *position){
    SDL_Surface *ima=IMG_Load(position);
    if(ima==NULL){
        SDL_Log("LOAD JPG FAILED:%s",SDL_GetError());
    }
    return ima;
}

//导入图片至渲染器
 void into_image(SDL_Window *win,SDL_Renderer *ren,SDL_Surface *ima){
    IMG_Init(IMG_INIT_JPG);
    SDL_Texture *text=SDL_CreateTextureFromSurface(ren,ima);
    SDL_FreeSurface(ima);
    if(text==NULL){
        SDL_Log("CREATE TEXTURE FAILED:%s",SDL_GetError());
    }
    //导入渲染器
    SDL_RenderCopy(ren,
                text,
                NULL,//复制图片的区域
                NULL //目标区域
                );
    SDL_DestroyTexture(text);
}

//绘制矩形
SDL_Renderer *draw_rectangle(SDL_Renderer *ren,SDL_Rect *rect,color *col){
    SDL_SetRenderDrawColor(ren,col->r,col->g,col->b,col->a);
    SDL_RenderFillRect(ren,rect);
}

//使矩形沿x轴移动（需搭配循环使用）
void move_rect(SDL_Renderer *ren,SDL_Rect *rect,color *col,int speed){
    draw_rectangle(ren,rect,col);
    rect->x+=speed;
    SDL_Delay(100);
    SDL_RenderPresent(ren);
}

//退出
void quit(SDL_Window *win,SDL_Renderer *ren){
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    IMG_Quit();
    SDL_Quit();
}

//绘制界面
void draw_ui(SDL_Renderer *ren){
    SDL_RenderPresent(ren);
}

//监听行为
void action(char *position,SDL_Rect *rect,color *col,int speed){
    SDL_Window *win=init_creat();
    SDL_Renderer *ren=create_renderer(win);
    SDL_Surface *ima=load_image(position);
    SDL_Event event;
    into_image(win,ren,ima);
    draw_rectangle(ren,&rect[0],&col[0]);
    draw_ui(ren);
    bool run=true;
    while(run){
        while(SDL_PollEvent(&event)!=0){
            switch(event.type){
                case SDL_QUIT://退出事件
                    run=false;
                    break;
                case SDL_WINDOWEVENT://窗口事件
                    switch(event.window.event){
                        case SDL_WINDOWEVENT_SIZE_CHANGED://窗口大小变化
                            //窗口大小变化后，原有纹理失效
                            SDL_Log("changed");
                            ima=load_image(position);
                            into_image(win,ren,ima);
                            draw_rectangle(ren,&rect[0],&col[0]);
                            draw_ui(ren);
                            break;
                    }break;
            }
        }
    }
    //quit必须放在事件循环外
    quit(win,ren);
}