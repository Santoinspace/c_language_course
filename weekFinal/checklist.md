# 期末项目 · raylib 图形库与项目实操 · 操作清单

> 配套正文：[raylib图形库与项目实操.md](raylib图形库与项目实操.md)
> 用法：按编号从上到下操作，每步先做「操作」，再对照「结果」。结果不符时看「避免」，不要跳步。
> 图号对应正文截图，点击可查看。

## A. 环境与模板确认

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 1 | 新开终端，依次执行 `gcc --version`、`mingw32-make --version`、`cmake --version`、`git --version` | 四条都输出版本信息；`cmake` 版本 ≥ 3.24 | 在 Git Bash/MSYS 里执行这些命令 |
| 2 | 把模板复制到 `D:\Code\c-final`；没有 D 盘改用 `C:\Code\c-final` 或其他纯英文目录 | 根目录能看到 `CMakeLists.txt`、`src`、`include`、`tools\configure.cmd` | 路径含中文或空格；放在中文用户名下 |
| 3 | VS Code 里 **文件 → 打开文件夹**，选择 `D:\Code\c-final` | 左侧资源管理器显示 `src/`、`include/`、`tests/`、`data/` | 只打开了单个 `.c` 文件，或打开了上一级目录 |
| 4 | 终端执行 `cmd /c tools\check-env.cmd` | 末尾出现 `[OK] Ready to configure.` | 看到 `[MISSING]` 仍继续往下做 |

## B. 首次配置

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 5 | 确认终端在项目根目录，执行 `cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug` | 出现 `Configuring done`、`Generating done`、`Build files have been written to`（[图 3](images/03-cmake-configure.png)） | 生成器名拼错、漏引号；不在项目根目录执行 |
| 6 | 首次配置：联网模式等待下载 raylib 6.0（约 1–3 分钟）；已放 `third_party/raylib/` 时直接走离线模式 | 联网模式输出 `raylib source: fixed Git tag 6.0`，生成 `build/_deps/raylib-src/`；离线模式输出 `raylib source: third_party/raylib (offline)`，生成 `build/raylib-local-build/` | 网络失败时反复重配；把 `GIT_TAG` 改成 6.2 |
| 7 | 查看 `build/` 目录大小 | 可能达到几百 MB，属正常现象 | 把 `build/` 提交进 Git |
| 8 | （选做）打开 `third_party/raylib/src/raylib.h`（离线）或 `build/_deps/raylib-src/src/raylib.h`（联网），搜索 `RAYLIB_VERSION` | 看到 `#define RAYLIB_VERSION "6.0"` | 以为课程用的是 6.2 |

## C. 编译与测试

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 9 | 执行 `cmake --build build --parallel 4` | 最后一行是 `[100%] Built target c_final_project` | 去改 `build/` 里的 Makefile 或缓存 |
| 10 | 查看产物 | `build\c_final_project.exe` 存在 | 把双击 exe 当作正式运行方式 |
| 11 | 执行 `ctest --test-dir build --output-on-failure` | `1/1 Test #1: score_storage ... Passed`，末尾 `100% tests passed` | 漏掉 `--test-dir build`，在错误目录运行 |
| 12 | 修改 `src/main.c` 里任意一行文字，再执行 `cmake --build build --parallel 4` | 只重编改动的文件并重新链接，几秒完成 | 每次改动都删掉整个 `build/` 重来 |

## D. 运行与验证

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 13 | 在项目根目录执行 `.\build\c_final_project.exe` | 窗口标题 `C Programming Final Project`，顶部 `Score: 0  Best: 0`（[图 4](images/04-game-window.png)） | 先 `cd build` 再运行，导致找不到 `data/` |
| 14 | 按方向键或 W/A/S/D 移动蓝色方块，去碰黄色方块 | 方块移动；碰到后 `Score` 加 1，金币换位置 | 把 R 当移动键；用鼠标拖方块 |
| 15 | 按 R，再按 Esc | 分数归零；窗口关闭、程序退出 | 点右上角 × 后以为分数一定已保存 |

## E. 读代码

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 16 | 打开 `src/main.c`，按顺序找到 `InitWindow`、`WindowShouldClose`、`BeginDrawing`、`EndDrawing`、`CloseWindow` | 能按执行顺序指出这 5 个调用 | 把 `DrawText` 写在 `BeginDrawing()` 之前 |
| 17 | 找到 `typedef struct GameState` 和 `ResetGame(&game)` | 能说出 `&game` 传的是地址、`game->score` 改的是原对象 | 函数参数写成 `GameState game` 却想修改原变量 |

## F. 新增模块

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 18 | 新建 `include/message.h`（粘贴正文 5.1）和 `src/message.c`（粘贴正文 5.2） | 两个文件出现在对应目录，文件名全小写 | 文件名大小写不一致，或建成了 `.txt` |
| 19 | 在 `src/main.c` 加 `#include "message.h"`，并在 `main` 开头加 `PrintCourseMessage();` | 代码与正文 5.3 的完整 `main` 一致 | 只加 `#include`，忘了调用函数 |
| 20 | 在 `CMakeLists.txt` 的 `add_executable(c_final_project ...)` 里加 `src/message.c` | 列表里现在有 `src/main.c`、`src/score.c`、`src/message.c` 三个 `.c` | 把 `message.h` 写进源文件列表 |
| 21 | 执行 `cmake --build build --parallel 4`，再从根目录运行 exe | 终端先打印 `This is my first multi-file C project!`，随后窗口正常打开 | 改完 CMakeLists 没有重新 build |
| 22 | 临时删掉 `CMakeLists.txt` 里的 `src/message.c`，重新 build；再把这一行加回并 build | 删掉时报 `undefined reference to 'PrintCourseMessage'`；加回后恢复正常 | 看到链接错误直接删调用代码 |

## G. 项目立项与提交

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 23 | 从正文 6.1 选题，按 6.2 写结构体和模块表 | 至少 2 个自己写的业务 `.c`，有结构体、数组、指针参数 | 所有代码都堆在 `main.c` |
| 24 | 用 Git 提交，按 6.4 的节奏写 commit message | `git log --oneline` 至少 5 条本人提交；`build/`、`.exe`、`data/best_score.txt` 不在提交里 | `git add .` 把 `build/` 一起提交 |
| 25 | 按 6.5 写 README，然后删掉 `build/`，照 README 从头做一遍 | 在干净目录能配置、编译、运行，`ctest` 通过 | README 只写一句「运行 main.c」 |

## H. 选做

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 26 | （选做）给游戏加计时或生命值 | 窗口里出现秒数或生命值，按 R 能重置 | 改了结构体字段，但函数仍用值传参，界面数字不变 |
