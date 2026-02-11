/* 模块 03：Input_Movement
   功能：实现键盘控制图片移动，理解“输入-更新-渲染”循环。
   底层知识：
   1. 事件队列 (Event Queue)：OS 记录所有操作，CPU 通过 while 循环一次性清空。
   2. 状态驱动渲染：渲染器不关心按键，它只关心那一刻坐标变量的数值。
   3. 帧率限制 (FPS Limiting)：通过控制循环速度，将逻辑与显示同步。
*/

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main (int argc, char* argv[]){
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    //初始化窗口
    SDL_Window* window = SDL_CreateWindow("PvZ Dev: Input & Move",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    //初始化渲染器
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    //将图片资源上传至内存
    SDL_Surface* tempSurface = IMG_Load("peashooter.png");

    //从内存长传至显存
    SDL_Texture* plantTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);

    //清空内存
    SDL_FreeSurface(tempSurface);

    int posX = 100;
    int posY = 100;
    int size = 50;
    int moveSpeed = 10;

    bool isRunning = true;
    SDL_Event event;

while (isRunning) {
    // A. 处理输入 (Input)
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) isRunning = false;
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:    posY -= moveSpeed; break;
                case SDLK_DOWN:  posY += moveSpeed; break;
                case SDLK_LEFT:  posX -= moveSpeed; break;
                case SDLK_RIGHT: posX += moveSpeed; break;
            }
        }
    }

    // B. 渲染阶段 (Render)
    // 第一步：清空全屏（背景设为深灰色）
    SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
    SDL_RenderClear(renderer);

    // 第二步：准备方块的“工程图纸”
    SDL_Rect playerRect = { posX, posY, size, size };

    // 第三步：给画笔蘸上“红色”
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    
    // 第四步：指挥 GPU 填充这个矩形
    SDL_RenderFillRect(renderer, &playerRect);

    // 第五步：刷新屏幕
    SDL_RenderPresent(renderer);

    // (记得加上之前说的 SDL_Delay 控制帧率)
}
    SDL_DestroyTexture(plantTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    IMG_Quit();
    SDL_Quit();

    return 0;
}