# 模块 02： 纹理加载与显存管理

## 一.图片的三态转换
**图片是如何从硬盘加载到显示器上面的？**

*硬盘 内存 显存*

- **磁盘态** (`peashooter.png`): 存储在硬盘上的压缩数据。
- **内存态** (`SDL_Surface`): CPU 解压后的像素数组。
- **显存态** (`SDL_Texture`): 上传至 GPU 的渲染就绪数据。

## 二.相关知识

### 1.``` SDL_Surface* tempSurface = IMG_Load("peashooter.png");```
**将图片从文件系统提取到内存**
- ``IMG_Load("peashooter.png")``调用文件，解压缩

- ``SDL_Surface 结构体 ``在内存中开辟空间，存储像素数据

- 从硬盘提取到内存速度满（硬盘速度满）
- CPU解码PNG是一个计算密集型任务
### 2.核心概念：SDL_Texture
- **本质**: 它是 GPU 控制的一块显存区域。
- **优势**: 利用硬件加速，每秒可以渲染成千上万次而不会给 CPU 造成压力。
- **原则**: 
    - 它是“只读”的渲染原材料（通常情况下）。
    - 必须在程序退出前手动调用 `SDL_DestroyTexture` 释放，否则会造成显存泄漏。
### 3. 数据上传：SDL_CreateTextureFromSurface
- **底层动作**: 将像素从系统内存（RAM）通过 PCI-E 总线上传到显卡显存（VRAM）。
- **优化点**: 
  - 显存中的 Texture 是经过 GPU 硬件优化的，读取速度极快。
  - 上传完成后，应立即 `SDL_FreeSurface` 释放 CPU 侧的内存。
- **注意**: 纹理上传是一个相对昂贵的操作（受总线带宽限制），因此严禁放在 Render Loop（渲染循环）内重复执行。
### 4.内存管理：SDL_FreeSurface(tempSurface);
**核心矛盾**：一份图片在传输后有两份，内存有限，需要还给操作系统

### 5. 渲染指令：SDL_RenderCopy
- **本质**: 它是 GPU 的纹理映射过程。
- **Source Rect (NULL)**: 决定选取素材的哪一部分（用于裁剪或动画）。
- **Dest Rect (&destRect)**: 决定在屏幕上的位置和拉伸大小（控制缩放）。
- **底层特性**: 异步执行。CPU 只负责下令，真正的像素计算由 GPU 的纹理单元完成。
### 6. 资源释放与闭环 (Resource Deallocation)
- **原则**: 后创建的资源先销毁 (LIFO)。
- **物理意义**: 
  - `DestroyTexture`: 归还显存 (VRAM)。
  - `DestroyRenderer`: 关闭 GPU 通道。
  - `DestroyWindow`: 将图形控制权交还给操作系统。
- **底层警示**: 每一行 `Create` 或 `Load` 命令都必须对应一行 `Destroy` 或 `Free`，否则会造成内存/显存泄漏。



