/* * 模块 02：纹理渲染 (Texture Rendering)
 * 目标：学习如何将图片资源加载进显存并高效渲染
 * * 底层逻辑路径：
 * 1. IMG_Load: [磁盘文件] -> [内存 Surface] (由 CPU 处理)
 * 2. SDL_CreateTextureFromSurface: [内存 Surface] -> [显存 Texture] (数据上传至 GPU)
 * 3. SDL_RenderCopy: [显存 Texture] -> [渲染管线] (由 GPU 快速绘制)
 */
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc , char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        std::cerr << "SDL 无法初始化！ 错误信息：" << SDL_GetError() << std::endl;
        return 1;
    }
    if( IMG_Init(IMG_INIT_PNG) < 0 ) {
        std::cerr << "IMG 无法初始化！ 错误信息：" << IMG_GetError() << std::endl;
        SDL_Quit();
        return 1;
    } 

    SDL_Window* window = SDL_CreateWindow(
        "PvZ Dev Journey: Moudle 02",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if(window == nullptr){
        std::cerr << "窗口创建失败！ 错误信息：" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    
    if(renderer== nullptr){
        std::cerr << "渲染器创建失败！ 错误信息：" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Surface* tempSurface = IMG_Load("peashooter.png");

    if (tempSurface == nullptr) {
        std::cerr << "无法加载图片 peashooter.png! IMG_Error: " << IMG_GetError() << std::endl;
        // 这里不退出，后面会做空指针检查
    }

    SDL_Texture* plantTexture = nullptr;

    if (tempSurface != nullptr) {
        plantTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    
        SDL_FreeSurface(tempSurface);
    }

    bool isRunning = true;
    SDL_Event event;

    while(isRunning){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT){
                isRunning = false;
            }
        }
    

      
        SDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
        SDL_RenderClear(renderer);
        
        if (plantTexture != nullptr) {

            SDL_Rect destRect = { 100, 100, 100, 100 };
            
            SDL_RenderCopy(renderer, plantTexture, NULL, &destRect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyTexture(plantTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    
    SDL_Quit();
    IMG_Quit();
    
    return 0;
}
