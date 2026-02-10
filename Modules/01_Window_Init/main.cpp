/*模块01_Window_Init
    功能：创建窗口并且实现窗口贴图
*/
#include <iostream>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(int argc , char* argv[]){
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL 无法初始化！ 错误信息：" << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "PvZ Dev Journey: Moudle 01",
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
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
