# 模块01： SDL2窗口初始化

## 一.功能实现
- 使用C++标准流处理错误输出
- 初始化 SDL2 视频子系统
- 创建窗口800*600
- 完成硬件渲染
- 时间循环，支持的点击退出

## 二.相关知识积累
### 1. cerr 和 cout 的区别
  cerr无缓冲内容立即刷新 cout有缓冲存满内存再刷新

  在程序崩溃时，cout无法打印出来；cerr立即发送

### 2.``` SDL_Init(SDL_INIT_VIDEO)```
  SDL_INIT_VIDEO 程序向操作系统申请他图形操作权限

  SDL_Init 向操作系统申请这些硬件的控制权

### 3.```SDL_Window* SDL_CreateWindow(const char* title, int x, int y, int w, int h, Uint32 flags);```
创建窗口（标题，坐标，宽高，配置）
- const char* title (窗口标题)

- int x, int y (窗口坐标)

- int w, int h (窗口宽高)

- Uint32 flags (配置开关)

SDL_WINDOW_SHOWN：强制窗口立即显示。

SDL_WINDOW_FULLSCREEN：全屏模式。

SDL_WINDOW_RESIZABLE：允许用户拉伸窗口大小。

SDL_WINDOW_OPENGL：如果你打算配合 OpenGL 使用（SDL 会创建 OpenGL 上下文）。

### 4. ```SDL_Renderer* SDL_CreateRenderer(SDL_Window* window, int index, Uint32 flags);```
渲染器（窗口，驱动，渲染标志位）
  - SDL_RENDERER_ACCELERATED：强制硬件加速。
  - SDL_RENDERER_PRESENTVSYNC：开启垂直同步。

### 5.```SDL_Event SDL_PollEvent(&event)```
接收输入信号 取出最前面输入信号 return 1取得信号 return 0未取得

### 6.为什么通常用 while 而不是 if？

```cpp
while (SDL_PollEvent(&event)) {
    // 处理事件...
}
```
if 只能在一帧处理一个输入，存在输入延迟
while 瞬间清空

###  7.三大函数
```cpp
    cppSDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
```
1.cppSDL_SetRenderDrawColor(renderer, 0, 128, 128, 255);
预设renderer的全局变量，设定颜色

2.SDL_RenderClear(renderer);
清屏

3.SDL_RenderPresent(renderer);
提交渲染，显示画面

### 8.关闭函数
```cpp
SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
```
*先关闭渲染器，再关闭窗口*