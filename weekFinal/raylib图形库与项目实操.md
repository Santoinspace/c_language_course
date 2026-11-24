# 期末项目 · raylib 图形库与项目实操

> 从课程模板到你的第一个图形程序

> **参考资料**：raylib 官网、GitHub 仓库、6.0/6.2 发布页、官方示例与中文速查表（链接见 2.4）。
> **版本**：课程模板固定 raylib **6.0**；官方最新版为 **6.2**。模板中的 `GIT_TAG 6.0` 不要修改。
> **范围**：操作以课程模板 `raylib_project_template/` 为准，官方 Wiki 仅作参考。

---

## 0. 学习目标

- 说清 raylib 是什么、许可证是什么，以及它为什么适合 C 语言课程；
- 理解 raylib 的主循环骨架和七个核心模块；
- 在课程模板上完成 **配置 → 编译 → 测试 → 运行**；
- 读懂 `main.c`、`score.c`、`score.h` 的分工，能指出结构体、指针参数和文件读写；
- 自己新增一个 `.c` + `.h` 模块，并登记到 `CMakeLists.txt`；
- 完成选题、模块划分、Git 提交和 README。

---

## 1. 课前准备

| 需要的东西                                | 说明                                                        |
| ----------------------------------------- | ----------------------------------------------------------- |
| VS Code + MinGW-w64 GCC                   | 终端里 `gcc --version` 有输出                             |
| CMake                                     | 版本必须 **≥ 3.24**                                  |
| Git                                       | 用于版本管理和提交                                          |
| 课程工程模板 `raylib_project_template/` | 完整复制，不要拆散                                          |
| 纯英文、无空格的目录                      | 例如 `D:\Code\c-final`                                    |
| 网络                                      | 首次配置默认从 GitHub 下载 raylib 6.0；也可提前准备离线源码 |

> **路径**：不要使用中文、空格、网络共享盘或 OneDrive 同步目录。
> **终端**：使用 PowerShell、CMD 或 VS Code 内置终端；不要用 Git Bash/MSYS 运行 `MinGW Makefiles`。

---

## 2. 认识 raylib

### 2.1 它是什么

raylib 是一个简单易用的 C 语言游戏/图形库。它不提供编辑器和场景面板，只提供画图、播放声音、读取键盘鼠标的函数，剩下的逻辑由你写 C 代码完成。

| 项目          | 内容                                                                                                                     |
| ------------- | ------------------------------------------------------------------------------------------------------------------------ |
| 语言 / 许可证 | C99；zlib/libpng（允许静态链接）                                                                                         |
| 课程版本      | **6.0**，模板 `GIT_TAG` 固定                                                                                     |
| 官方最新版    | 6.2（有 API 变化，不要直接替换）                                                                                         |
| 外部依赖      | 无，GLFW、miniaudio 等已内置                                                                                             |
| 官方资源      | [https://www.raylib.com/](https://www.raylib.com/)、[https://github.com/raysan5/raylib](https://github.com/raysan5/raylib) |

模板采用**静态链接**，所以最终只需要 `c_final_project.exe`，不需要额外的 `raylib.dll`。

> **不要升级到 6.2**：6.2 调整了部分文件 API 和 Image 绘制 API，模板代码是按 6.0 写的。

### 2.2 七个核心模块

![raylib 6.0 模块架构](images/01-raylib-architecture.png)
*图 1：raylib 6.0 的七个核心模块*

| 模块                | 负责什么         | 常用函数                                                               |
| ------------------- | ---------------- | ---------------------------------------------------------------------- |
| **rcore**     | 窗口、输入、时间 | `InitWindow`、`WindowShouldClose`、`IsKeyDown`、`GetFrameTime` |
| **rshapes**   | 2D 形状与碰撞    | `DrawRectangle`、`DrawRectangleRec`、`CheckCollisionRecs`        |
| **rtextures** | 图片、纹理       | `LoadTexture`、`DrawTexture`、`UnloadTexture`                    |
| **rtext**     | 文字、字体       | `DrawText`、`TextFormat`、`MeasureText`                          |
| **rmodels**   | 3D 模型、相机    | `LoadModel`、`DrawModel`、`UpdateCamera`                         |
| **raudio**    | 音频             | `InitAudioDevice`、`LoadSound`、`PlaySound`                      |
| **rlgl**      | OpenGL 底层封装  | 一般不用直接调用                                                       |

另外两个常见扩展：**raymath**（向量/矩阵运算）和 **raygui**（简易 GUI）。本模板**没有预装 raygui**，期末不要求复杂输入框和表格。

### 2.3 一个最小 raylib 程序

```c
#include "raylib.h"

int main(void)
{
    InitWindow(800, 450, "raylib example - basic window");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
```

| 步骤 | 函数                              | 作用                     |
| ---- | --------------------------------- | ------------------------ |
| 1    | `InitWindow(宽, 高, 标题)`      | 创建窗口并初始化图形设备 |
| 2    | `while (!WindowShouldClose())`  | 主循环，每帧执行一次     |
| 3    | `BeginDrawing()`                | 开始绘制这一帧           |
| 4    | `ClearBackground` + `Draw...` | 清屏并绘制内容           |
| 5    | `EndDrawing()`                  | 提交画面并处理输入       |
| 6    | `CloseWindow()`                 | 释放窗口资源             |

> `BeginDrawing()` 和 `EndDrawing()` 必须成对出现，所有 `Draw...` 调用都要夹在它们中间。

### 2.4 学习资源与工程差异

![raylib 官方示例页](images/02-raylib-examples.png)
*图 2：raylib 官方示例页*

| 资源                                                                        | 用途                           |
| --------------------------------------------------------------------------- | ------------------------------ |
| [中文速查表](https://www.raylib.com/cheatsheet/cheatsheet_zh.html)           | 查函数名、参数和返回值         |
| [官方示例](https://www.raylib.com/examples.html)                             | 找现成效果，改参数学习         |
| [`raylib.h`](https://github.com/raysan5/raylib/blob/6.0/src/raylib.h)      | 确认函数原型                   |
| [CMake 集成 Wiki](https://github.com/raysan5/raylib/wiki/Working-with-CMake) | 理解 `target_link_libraries` |

官方 Wiki 推荐 `raylib-game-template` + `premake`；**本课程使用自己的 CMake 模板**，不要混用：

| 对比项      | 官方 Wiki                    | 本课程模板                                                    |
| ----------- | ---------------------------- | ------------------------------------------------------------- |
| 工程组织    | `raylib-game-template`     | 独立 CMake 工程                                               |
| 构建工具    | `premake-mingw.bat` + make | `MinGW Makefiles` + CMake                                   |
| raylib 位置 | 手动放进工程                 | 自动下载到 `build/_deps/`，或离线放 `third_party/raylib/` |
| 版本        | 跟随最新                     | 固定 6.0                                                      |

断网时，把 raylib 6.0 完整源码放到 `third_party/raylib/`（`CMakeLists.txt` 要直接在这一层），CMake 会自动走离线路径。详见 [`docs/QA.md`](../raylib_project_template/docs/QA.md)。

---

## 3. 运行课程模板

### 3.1 模板结构

把模板复制到 `D:\Code\c-final`。它自带一个可运行的小游戏：蓝色方块移动，碰到黄色方块加 1 分，最高分写入 `data/best_score.txt`。

```text
c-final/
├─ CMakeLists.txt
├─ .vscode/                 # VS Code 任务与调试配置
├─ src/
│  ├─ main.c                # 程序入口
│  └─ score.c               # 分数文件读写
├─ include/
│  └─ score.h               # score 模块接口
├─ tests/
│  └─ test_score.c          # 不依赖 raylib 的单元测试
├─ assets/                  # 图片、音效（默认空）
├─ data/                    # 运行时数据
├─ docs/                    # 学生手册、操作清单、项目要求、常见问题
├─ third_party/             # 离线 raylib 源码（默认空）
├─ tools/
│  ├─ check-env.cmd         # 检查工具链
│  ├─ configure.cmd         # 首次配置
│  ├─ build.cmd             # 编译
│  └─ run.cmd               # 运行
├─ .gitignore
└─ README.md
```

| 文件                                  | 作用                           | 是否需要改                 |
| ------------------------------------- | ------------------------------ | -------------------------- |
| `CMakeLists.txt`                    | 源文件、raylib、测试的构建配置 | 新增 `.c` 时要改         |
| `src/main.c`                        | 游戏/应用主逻辑                | **要改**             |
| `src/score.c` / `include/score.h` | 文件读写示例                   | 可复用或替换               |
| `tests/test_score.c`                | 自动化测试示例                 | 建议扩写                   |
| `docs/`                             | 课程文档                       | 只读                       |
| `build/`                            | 生成目录                       | **不要改、不要提交** |

> 代码中搜索 `TODO(STUDENT)`，可以快速定位需要你修改或新增代码的位置。
> 模板的 `.gitignore` 已排除 `build/`、`*.exe` 和 `data/best_score.txt`。

### 3.2 检查环境

```powershell
gcc --version
mingw32-make --version
cmake --version
git --version
```

重点确认：

- `gcc` 来自 MinGW-w64；
- `cmake` 版本 ≥ 3.24。

也可以直接运行模板检查脚本：

```powershell
cmd /c tools\check-env.cmd
```

最后出现 `[OK] Ready to configure.` 即可。如果提示 `[MISSING]`，先补齐对应工具。

### 3.3 第一次配置

在项目根目录执行：

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug
```

也可以运行：

```powershell
cmd /c tools\configure.cmd
```

| 参数                         | 含义                                                    |
| ---------------------------- | ------------------------------------------------------- |
| `-S .`                     | 源码目录是当前目录                                      |
| `-B build`                 | 构建文件放到 `build/`                                 |
| `-G "MinGW Makefiles"`     | 生成 `mingw32-make` 可读的 Makefile，名称和引号不能错 |
| `-DCMAKE_C_COMPILER=gcc`   | 使用 PATH 中的 `gcc`                                  |
| `-DCMAKE_BUILD_TYPE=Debug` | 保留调试信息                                            |

首次配置默认联网下载 raylib 6.0，输出类似：

```text
-- raylib source: fixed Git tag 6.0 (initial download requires network)
...
-- Configuring done
-- Generating done
-- Build files have been written to: .../build
```

如果 `third_party/raylib/CMakeLists.txt` 存在，则会输出：

```text
-- raylib source: third_party/raylib (offline)
```

![CMake 配置成功的终端输出](images/03-cmake-configure.png)
*图 3：CMake 配置成功的终端输出*

> `build/` 可能达到几百 MB，属于正常现象；它已被 `.gitignore` 排除。
> 修改 `CMakeLists.txt` 后不需要手动重配，下一次构建会自动重新运行 CMake。

### 3.4 编译

```powershell
cmake --build build --parallel 4
```

或：

```powershell
cmd /c tools\build.cmd
```

第一次编译会连 raylib 一起编译，通常需要 1～3 分钟。看到下面的输出即成功：

```text
[100%] Built target c_final_project
```

产物是 `build\c_final_project.exe`。之后只改自己的代码时，增量编译通常几秒完成。

> 模板开启了 `-Wall -Wextra -Wpedantic`。警告不阻止生成 exe，但应尽量做到零警告。

### 3.5 运行测试

```powershell
ctest --test-dir build --output-on-failure
```

正常输出：

```text
1/1 Test #1: score_storage ... Passed
100% tests passed out of 1
```

测试覆盖：

- 文件不存在或内容非法时返回 0；
- 保存后能读回相同的值；
- 拒绝保存负数；
- 被拒绝的保存不破坏原值。

测试只链接 `src/score.c`，不依赖 raylib，所以不需要图形窗口。

### 3.6 运行程序

在项目根目录执行：

```powershell
.\build\c_final_project.exe
```

或：

```powershell
cmd /c tools\run.cmd
```

![模板运行后的窗口](images/04-game-window.png)
*图 4：课程模板运行窗口*

| 操作             | 效果                |
| ---------------- | ------------------- |
| 方向键或 W/A/S/D | 移动蓝色方块        |
| 碰到黄色方块     | 分数 +1，金币换位置 |
| R                | 重新开始            |
| Esc 或点关闭按钮 | 退出                |

程序使用相对路径：

```c
#define DATA_PATH "data/best_score.txt"
```

因此必须从项目根目录运行。若先 `cd build` 再运行，程序会去找 `build\data\best_score.txt`，最高分无法保存。`tools\run.cmd` 已自动切回项目根目录。

---

## 4. 读代码

读代码的目标是能解释：**数据从哪来、谁修改它、最后画到哪里**。

### 4.1 主循环

`src/main.c` 的 `main` 函数：

```c
int main(void)
{
    GameState game = {0};
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "C Programming Final Project");
    SetTargetFPS(60);
    game.best_score = LoadBestScore(DATA_PATH);
    ResetGame(&game);

    while (!WindowShouldClose()) {
        UpdateGame(&game);
        DrawGame(&game);
    }

    CloseWindow();
    return 0;
}
```

| 阶段   | 代码                             | 说明                                       |
| ------ | -------------------------------- | ------------------------------------------ |
| 初始化 | `InitWindow(...)`              | 创建窗口                                   |
| 主循环 | `while (!WindowShouldClose())` | 每帧执行一次                               |
| 更新   | `UpdateGame(&game)`            | 输入、移动、碰撞、计分                     |
| 绘制   | `DrawGame(&game)`              | 内部包含 `BeginDrawing` / `EndDrawing` |
| 关闭   | `CloseWindow()`                | 释放资源                                   |

`SetTargetFPS(60)` 限制帧率；`LoadBestScore(DATA_PATH)` 启动时读取最高分。

> raylib 默认字体只包含 ASCII。`DrawText("得分", ...)` 会显示异常；中文界面需要额外加载字体，本课程不要求。

### 4.2 结构体与指针

```c
typedef struct GameState {
    Rectangle player;
    Rectangle coin;
    int score;
    int best_score;
} GameState;
```

`GameState` 把一局游戏需要的数据打包在一起，函数之间只传一个参数。

```c
ResetGame(&game);
```

| 写法                 | 含义                                   |
| -------------------- | -------------------------------------- |
| `game.score`       | 直接访问结构体成员                     |
| `game->score`      | 通过指针访问，等价于 `(*game).score` |
| `&game`            | 取地址，让函数能修改原变量             |
| `(Rectangle){...}` | C99 复合字面量，临时构造一个结构体     |

`ResetGame(GameState *game)` 通过指针修改原对象。如果写成 `GameState game`（不带 `*`），函数拿到的是副本，修改不会生效。

### 4.3 输入与帧率

```c
const float speed = 280.0f * GetFrameTime();

if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) game->player.x -= speed;
if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) game->player.x += speed;
if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) game->player.y -= speed;
if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) game->player.y += speed;
```

- `IsKeyDown`：按住期间每帧都返回 true，适合持续移动；
- `IsKeyPressed`：只在按下的那一帧返回 true，适合 R 重开这类一次性操作；
- `GetFrameTime()`：上一帧耗时（秒）。`280.0f * GetFrameTime()` 表示每秒移动 280 像素，与帧率无关。

边界限制防止方块跑出窗口；顶部从 `y = 80` 开始，是为了避开标题栏。

### 4.4 碰撞与计分

```c
if (CheckCollisionRecs(game->player, game->coin)) {
    game->score++;
    if (game->score > game->best_score) {
        game->best_score = game->score;
        (void)SaveBestScore(DATA_PATH, game->best_score);
    }
    PlaceCoin(game);
}
```

`CheckCollisionRecs` 判断两个矩形是否相交。相交时分数 +1；刷新最高分时立即写文件；然后重新放置金币。

`(void)` 表示故意忽略返回值。保存失败不会让游戏崩溃，但分数不会写入磁盘。

### 4.5 多文件与文件读写

`include/score.h` 只放接口：

```c
#ifndef COURSE_SCORE_H
#define COURSE_SCORE_H

/* 读取最高分；文件不存在或内容非法时返回 0。 */
int LoadBestScore(const char *file_path);

/* 保存最高分；成功返回 1，失败返回 0。 */
int SaveBestScore(const char *file_path, int best_score);

#endif
```

`src/score.c` 放实现，以保存函数为例：

```c
int SaveBestScore(const char *file_path, int best_score)
{
    FILE *fp;
    int ok;
    if (file_path == NULL || best_score < 0) return 0;

    fp = fopen(file_path, "w");
    if (fp == NULL) return 0;
    ok = (fprintf(fp, "%d\n", best_score) > 0);
    if (fclose(fp) != 0) ok = 0;
    return ok;
}
```

| 语句                         | 作用                       | 失败时             |
| ---------------------------- | -------------------------- | ------------------ |
| `fopen(file_path, "w")`    | 以写模式打开，不存在则创建 | 返回 `NULL`      |
| `fprintf(fp, "%d\n", ...)` | 写入整数                   | 返回负数或 0       |
| `fclose(fp)`               | 关闭文件并刷新缓冲区       | 返回非 0           |
| `return 1 / 0`             | 告诉调用者成功或失败       | 调用者决定如何处理 |

`LoadBestScore` 使用 `fopen(..., "r")` 和 `fscanf`；文件不存在、读不到整数或读到负数时返回 0。

> `tests/test_score.c` 只链接 `src/score.c`，不链接 raylib，因此可以在没有图形窗口的环境中运行。

### 4.6 数据流

```text
程序启动
  │
  ├─ LoadBestScore("data/best_score.txt") ──→ game.best_score
  │
  └─ while (窗口没关)：
        键盘/鼠标 ──→ UpdateGame(&game) ──→ 修改 player / score / best_score
                                              │
                                              ├─ 刷新最高分 → SaveBestScore() → 文件
                                              │
                                              └─ DrawGame(&game) ──→ 屏幕
```

---

## 5. 新增一个模块

这一节是动手练习：新增一个 `.c` 和一个 `.h`，让 CMake 认识它。

### 5.1 新建 `include/message.h`

```c
#ifndef COURSE_MESSAGE_H
#define COURSE_MESSAGE_H

void PrintCourseMessage(void);

#endif
```

### 5.2 新建 `src/message.c`

```c
#include "message.h"
#include <stdio.h>

void PrintCourseMessage(void)
{
    puts("This is my first multi-file C project!");
}
```

### 5.3 在 `main.c` 中调用

在 `#include "score.h"` 下面加：

```c
#include "message.h"
```

在 `main` 开头加：

```c
PrintCourseMessage();
```

### 5.4 登记到 `CMakeLists.txt`

找到 `add_executable`，在列表末尾加入 `src/message.c`：

```cmake
add_executable(c_final_project
    src/main.c
    src/score.c
    src/message.c   # 新增这一行
)
```

> 模板中相应位置有 `TODO(STUDENT)` 提示。每个参与编译的 `.c` 都必须出现在这个列表里；`.h` 不用写。

### 5.5 重新编译并验证

```powershell
cmake --build build --parallel 4
.\build\c_final_project.exe
```

终端应先打印：

```text
This is my first multi-file C project!
```

随后窗口正常打开。

### 5.6 故意制造一次链接错误

把 `src/message.c` 从 `CMakeLists.txt` 中临时删掉，重新编译：

```text
undefined reference to `PrintCourseMessage'
```

原因是：`main.c` 只看到头文件里的**声明**，能通过编译；链接时找不到函数体，于是报“未定义引用”。

排查顺序：

1. `message.c` 是否存在、文件名是否正确；
2. `CMakeLists.txt` 是否包含 `src/message.c`；
3. 函数名、参数、返回类型是否与头文件完全一致；
4. 修改 CMakeLists 后是否重新构建。

把这一行加回去，重新编译即可恢复。

---

## 6. 项目实操

### 6.1 选题

模板只是示例。从下面选择或自拟题目，先实现“最低功能”，再考虑扩展：

| 题目       | 最低功能                                        | 扩展功能           |
| ---------- | ----------------------------------------------- | ------------------ |
| 贪吃蛇     | 转向、增长、碰撞、计分、最高分保存              | 难度、暂停、障碍物 |
| 俄罗斯方块 | 下落、移动旋转、消行、计分、结束判断            | 预览下一个方块     |
| 五子棋     | 双人落子、胜负判断、重开、战绩保存              | 撤销一步           |
| 扫雷       | 随机布雷、揭格、输赢判断、计时                  | 标记、分难度       |
| 超市管理   | 增删改商品、库存查询、文件保存                  | 排序、销量图表     |
| 图书管理   | 录入、借还、查询、文件保存                      | 到期提醒           |
| 车牌统计   | 从文本文件导入车牌、分类统计、图形展示          | 多条件检索         |
| 数据统计   | 从文本文件导入数据、统计平均值/最大值、图形展示 | 排序和筛选         |

> “车牌统计”是文本统计，不是摄像头图像识别；管理类项目使用 CSV/TXT 即可，不要求数据库。
> 图形效果不是硬性要求，功能正确、代码清晰优先。

### 6.2 需求与模块划分

以贪吃蛇为例，先设计数据结构：

```c
#ifndef COURSE_SNAKE_H
#define COURSE_SNAKE_H

#define MAX_SNAKE_LEN 256

typedef struct Point {
    int x;
    int y;
} Point;

typedef struct Snake {
    Point body[MAX_SNAKE_LEN];
    int length;
    int direction;   /* 0=上 1=右 2=下 3=左 */
} Snake;

void SnakeInit(Snake *snake);
void SnakeMove(Snake *snake, Point next);
void SnakeGrow(Snake *snake);
int  SnakeHitSelf(const Snake *snake);

#endif
```

这里同时用到了**结构体**、**数组**和**指针参数**。

模块表写进 README：

| 文件             | 职责                         | 关键函数                                                      |
| ---------------- | ---------------------------- | ------------------------------------------------------------- |
| `src/main.c`   | 窗口、主循环、串联模块       | `main`                                                      |
| `src/snake.c`  | 蛇的初始化、移动、增长、自撞 | `SnakeInit`、`SnakeMove`、`SnakeGrow`、`SnakeHitSelf` |
| `src/food.c`   | 食物生成与碰撞               | `FoodSpawn`、`FoodCheck`                                  |
| `src/board.c`  | 边界判断、得分规则           | `BoardCheck`                                                |
| `src/render.c` | 所有绘制调用                 | `RenderGame`                                                |
| `src/score.c`  | 最高分读写                   | `LoadBestScore`、`SaveBestScore`                          |

> 至少编写 **2 个自己的业务 `.c` 文件**（`main.c` 不算），每个模块用 `.h` 声明接口。
> 不要把所有代码堆在 `main.c` 里。

### 6.3 开发节奏

| 阶段              | 交付物                                               | 重点              |
| ----------------- | ---------------------------------------------------- | ----------------- |
| 1. 环境与首次提交 | 能运行的模板、运行截图、两次 commit、独立模块、CTest | Git + CMake + GCC |
| 2. 需求与模块设计 | 一页需求说明、结构体定义、模块表                     | C 语言结构设计    |
| 3. 最小可用程序   | 核心逻辑可运行，文件读写可验证                       | 基础功能          |
| 4. 完整版与展示   | 源码、README、演示、提交历史                         | 稳定性与规范      |

先做“最小可用”：能画出方块、能按键移动、能保存一个数字，就已经跑通全链路。

### 6.4 Git 提交

项目要求**至少 5 次有实质内容、可解释的提交**，且至少一次涉及 CMake 多文件配置。

一个合理的提交序列：

```text
1. chore: 导入课程模板
2. feat: 新增 snake 模块并登记到 CMakeLists
3. feat: 实现蛇的移动与吃食物增长
4. fix: 修正自撞判断的边界错误
5. feat: 保存并读取最高分
6. docs: 补全 README 的功能与运行说明
```

每次提交前：

```powershell
git status
git add src/main.c src/snake.c include/snake.h CMakeLists.txt
git commit -m "feat: 实现蛇的移动与吃食物增长"
git push
```

> 不要提交 `build/`、`.exe`、`data/best_score.txt`。模板的 `.gitignore` 已排除它们。

### 6.5 README

README 至少包含：

| 部分           | 内容                             |
| -------------- | -------------------------------- |
| 项目名称与简介 | 一句话说明做什么                 |
| 功能列表       | 对应 6.1 的最低功能              |
| 运行方法       | 配置、编译、运行命令             |
| 源文件职责     | 每个 `.c` / `.h` 负责什么    |
| 操作说明       | 哪个键做什么                     |
| 测试方法       | 如何运行 `ctest`，测了哪些函数 |
| 已知问题       | 未完成的功能和已知 bug           |
| 外部资源       | 图片、音效、参考代码及来源       |

> README 的目标是让陌生人能从零跑起来。写完后删掉 `build/`，按 README 重新做一遍。

---

## 7. 常见问题

### 7.1 配置时无法下载 raylib / 报 TLS 错误

1. 确认浏览器能打开 [https://github.com/raysan5/raylib](https://github.com/raysan5/raylib)；
2. 删除不完整的 `build` 后重试；
3. 仍然失败时，找助教要 raylib 6.0 源码，放到 `third_party/raylib/`，删除 `build/`，再配置；
4. 不要为了绕过网络把 `GIT_TAG` 改成 6.2，版本不对会导致代码不兼容。

离线目录必须是：

```text
third_party/raylib/CMakeLists.txt
```

不能多套一层 `raylib-6.0/`。详见 [`docs/QA.md`](../raylib_project_template/docs/QA.md)。

### 7.2 生成器不匹配

报错：

```text
CMake Error: Generator ... does not match the generator used previously
```

删除整个 `build/`，重新配置。不要手动改 `CMakeCache.txt`。

### 7.3 找不到 `raylib.h`

1. 确认已经成功配置，看到 `Configuring done`；
2. 确认终端在项目根目录；
3. 不要绕过 CMake 手写 `gcc main.c -lraylib`。

### 7.4 `undefined reference`

通常是新增的 `.c` 没写进 `add_executable`。检查文件名、CMakeLists 源文件列表、函数签名，然后重新构建。

### 7.5 窗口打不开或找不到 `data/best_score.txt`

- 从项目根目录运行；
- 确认 `data/` 目录存在；
- 不要双击 `build\c_final_project.exe`，双击 `tools\run.cmd` 或从根目录终端运行；
- 如果程序直接退出，先在终端运行以查看报错。

### 7.6 新最高分没有写入文件

1. 确认从项目根目录运行；
2. 确认 `data/` 存在且文件没有被其他程序占用；
3. 临时把 `(void)SaveBestScore(...)` 改成带日志的写法，查看是否保存失败。

### 7.7 VS Code 里 `raylib.h` 有红线

这是 IntelliSense 没读到 `build/compile_commands.json`，不影响命令行编译。

1. 安装 **C/C++ (Microsoft)** 扩展；
2. 先成功配置一次；
3. 不行时执行 `C/C++: Reset IntelliSense Database`。

### 7.8 按 F5 提示 `gdb.exe not found`

GDB 是可选项。需要断点调试时，确认 MinGW 的 `bin` 里有 `gdb.exe` 并加入 PATH；不装也能编译、测试和运行。

### 7.9 CMake 版本过低

报错 `CMake 3.24 or higher is required` 时，安装 CMake ≥ 3.24，关闭所有终端和 VS Code 后重开，用 `where.exe cmake` 确认版本。

### 7.10 路径包含中文或空格

把项目移到纯英文、无空格路径，例如 `D:\Code\c-final`；移动后删除 `build/` 重新配置。

---

## 8. 相关文档

- 模板说明：[`raylib_project_template/README.md`](../raylib_project_template/README.md)
- 学生操作手册：[`docs/STUDENT_GUIDE.md`](../raylib_project_template/docs/STUDENT_GUIDE.md)
- 操作清单：[`docs/checklist.md`](../raylib_project_template/docs/checklist.md)
- 项目要求与题目：[`docs/ASSIGNMENT.md`](../raylib_project_template/docs/ASSIGNMENT.md)
- 常见问题与离线方案：[`docs/QA.md`](../raylib_project_template/docs/QA.md)
