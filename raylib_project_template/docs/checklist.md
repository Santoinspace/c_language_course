# 项目操作清单（Checklist）

> 配套文档：[STUDENT_GUIDE.md](STUDENT_GUIDE.md) · [ASSIGNMENT.md](ASSIGNMENT.md) · [QA.md](QA.md)
> 用法：从 A 到 I 按编号顺序操作。每一步先执行「操作」，再对照「结果」；结果不符时看「避免」，不要跳步。
> 所有命令都在 **PowerShell、CMD 或 VS Code 内置终端**中执行，并确保当前目录是含 `CMakeLists.txt` 的项目根目录。不要使用 Git Bash 或 MSYS。

## A. 环境与工程确认

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 1 | 新开终端，依次执行 `gcc --version`、`mingw32-make --version`、`cmake --version`、`git --version` | 四条命令都输出版本信息，`cmake` 版本不低于 3.24 | 在 Git Bash/MSYS 里执行；调用了另一套 MinGW |
| 2 | 把 `raylib_project_template` 整个目录复制到纯英文、无空格的路径，例如 `D:\Code\c-final` | 根目录能看到 `CMakeLists.txt`、`src`、`include`、`tests`、`tools` | 路径含中文或空格；只复制了部分文件 |
| 3 | 在 VS Code 中 **文件 → 打开文件夹**，选择 `D:\Code\c-final` | 资源管理器显示 `src/`、`include/`、`tests/`、`docs/`、`tools/` | 只打开单个 `.c` 文件，或打开了上一级目录 |
| 4 | 在项目根目录执行 `cmd /c tools\check-env.cmd` | 末尾输出 `[OK] Ready to configure.` | 看到 `[MISSING]` 仍继续；在错误目录执行 |

## B. 首次配置

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 5 | 执行 `cmd /c tools\configure.cmd`；也可直接执行 `cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug` | 输出 `Configuring done`、`Generating done`，并生成 `build/` | 生成器名拼错或漏引号；不在项目根目录执行 |
| 6 | 首次配置时等待自动下载 raylib 6.0（约 1～3 分钟） | 输出含 `raylib source: fixed Git tag 6.0`，生成 `build/_deps/raylib-src/` | 网络失败时反复配置；把 `GIT_TAG` 改成其他版本 |
| 7 | 查看 `build/` 目录 | 体积达到几百 MB 属正常，内容全部是生成文件 | 把 `build/` 提交进 Git |
| 8 | （选做）打开 `build/_deps/raylib-src/src/raylib.h`，搜索 `RAYLIB_VERSION` | 看到 `#define RAYLIB_VERSION "6.0"` | 以为模板会自动使用最新版 raylib |

## C. 编译与测试

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 9 | 执行 `cmd /c tools\build.cmd`；也可直接执行 `cmake --build build --parallel 4` | 最后出现 `[100%] Built target c_final_project` | 手动修改 `build/` 内的 Makefile 或缓存 |
| 10 | 查看构建产物 | `build\c_final_project.exe` 存在 | 把双击 exe 当作唯一运行方式 |
| 11 | 执行 `ctest --test-dir build --output-on-failure` | 显示 `1/1 Test #1: score_storage ... Passed` 和 `100% tests passed out of 1` | 漏掉 `--test-dir build`，在错误目录运行 |
| 12 | 修改 `src/main.c` 中任意一行文字，再执行 `cmake --build build --parallel 4` | 只重新编译改动的文件并链接，几秒完成 | 每次改动都删除整个 `build/` 重来 |

## D. 运行与验证

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 13 | 在项目根目录执行 `cmd /c tools\run.cmd`，或执行 `.\build\c_final_project.exe` | 窗口打开，标题为 `C Programming Final Project`，顶部显示 `Score` 和 `Best`；没有 `data/best_score.txt` 时 `Best` 为 0 | 先 `cd build` 再运行，导致找不到 `data/` |
| 14 | 按方向键或 W/A/S/D 移动蓝色方块，去碰黄色方块 | 方块移动；碰到金币后 `Score` 加 1，金币换位置 | 把 R 当移动键；用鼠标拖动方块 |
| 15 | 按 R，再按 Esc | 当前分数归零；窗口关闭、程序退出 | 点窗口右上角关闭后，以为所有状态都已保存 |
| 16 | 刷新个人最高分后检查 `data/best_score.txt` | 文件内容为新的最高分 | 从 `build/` 目录运行，导致保存失败或写到别处 |

## E. 读懂示例代码

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 17 | 打开 `src/main.c`，按执行顺序找到 `InitWindow`、`WindowShouldClose`、`BeginDrawing`、`EndDrawing`、`CloseWindow` | 能指出主循环骨架：初始化 → 循环处理输入并绘制 → 关闭 | 把 `DrawText` 写在 `BeginDrawing()` 之前 |
| 18 | 找到 `typedef struct GameState`、`ResetGame(&game)` 和函数里的 `game->score` | 能说明 `&game` 传的是地址，函数通过指针修改原对象 | 函数参数写成 `GameState game`，却想修改原变量 |
| 19 | 打开 `src/score.c`、`include/score.h`、`tests/test_score.c` | 能说明 `LoadBestScore` 在文件不存在或内容非法时返回 0，测试覆盖了这些情况 | 只写 `fopen` 不判断返回值 |
| 20 | 打开 `CMakeLists.txt` 中的 `add_executable(c_final_project ...)` | 能指出 `src/main.c`、`src/score.c` 都在源文件列表里 | 以为文件放进 `src/` 就会自动参与编译 |

## F. 新增一个模块（课堂检查）

> 完整代码见 [STUDENT_GUIDE.md](STUDENT_GUIDE.md) 第 07 节。

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 21 | 新建 `include/message.h`，声明 `void PrintCourseMessage(void);` | 文件位于 `include/`，文件名全小写 | 文件名大小写不一致，或建成了 `.txt` |
| 22 | 新建 `src/message.c`，包含 `message.h` 和 `<stdio.h>`，实现该函数 | 文件位于 `src/` | 把函数实现写进头文件，导致重复定义 |
| 23 | 在 `src/main.c` 增加 `#include "message.h"`，并在 `main` 开头调用 `PrintCourseMessage();` | 代码能通过编译 | 只加 `#include`，忘了调用函数 |
| 24 | 在 `CMakeLists.txt` 的 `add_executable` 列表中加入 `src/message.c`，重新构建并运行 | 终端先打印 `This is my first multi-file C project!`，随后窗口正常打开 | 把 `message.h` 写进源文件列表；改完 CMakeLists 没有重新构建 |
| 25 | 临时删除列表里的 `src/message.c`，重新构建；再把这一行加回并构建 | 删除时报 `undefined reference to 'PrintCourseMessage'`；加回后恢复正常 | 看到链接错误就删掉调用代码，而不是检查源文件列表 |

## G. 从模板到期末项目

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 26 | 从 [ASSIGNMENT.md](ASSIGNMENT.md) 的题目表中选择一个方向，写一页需求说明和模块表 | 明确要解决的问题、核心数据、输入输出和模块划分 | 先写大量代码，最后才发现功能不完整 |
| 27 | 至少编写 2 个自己的业务 `.c` 文件，并为每个模块准备 `.h`；全部登记到 `CMakeLists.txt` | `src/` 中除 `main.c` 外有至少 2 个业务源文件，构建成功 | 所有代码都堆在 `main.c`；新增 `.c` 忘记登记 |
| 28 | 用结构体组织至少一种实体数据，用数组保存多条数据或状态，至少一个函数通过指针参数修改数据 | 能在代码中明确指出这三处 | 只用全局变量；函数全部按值传参 |
| 29 | 实现至少一种标准 C 文件读写，并处理文件不存在、格式错误或写入失败 | 数据能跨程序运行保存；删除数据文件后程序不崩溃 | 不检查 `fopen`、`fscanf` 等函数的返回值 |
| 30 | 用 raylib 实现基本图形界面和键盘/鼠标交互 | 窗口能响应输入并显示项目状态 | 把业务逻辑与 raylib 绑死，导致核心数据无法单独测试 |
| 31 | 更新根目录 `README.md`：项目名称、功能、操作方式、源文件职责、构建与测试方法、已知不足 | 按 README 从头能做一遍 | README 只写一句「运行 main.c」 |

## H. 提交前自检

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 32 | 执行 `git status` | `build/`、`*.exe`、`data/best_score.txt` 不在待提交列表中 | `git add .` 把生成文件和本地数据一起提交 |
| 33 | 执行 `git log --oneline` | 至少有 5 条本人编写、能解释的提交，其中至少一次包含 `CMakeLists.txt` 的多文件改动 | 最后一次性把所有文件塞进一个 commit |
| 34 | 执行 `git push`，再打开远程仓库网页 | 远程仓库显示最新代码；本地 `git status` 干净 | 只提交到本地，忘记推送 |
| 35 | 把项目复制到干净目录（或不含 `build/` 的新克隆），按 README 从配置开始重做一遍 | 配置、编译、测试、运行全部成功 | 依赖残留的 `build/` 缓存；离线时未准备 `third_party/raylib/` |

## I. 选做扩展

| # | 操作 | 结果 | 避免 |
|---|---|---|---|
| 36 | 按项目需要增加计时、生命值、暂停、难度或关卡 | 界面上能看到新状态，按 R 或相应按键能重置 | 改了结构体字段，但函数仍按值传参，界面数字不更新 |
| 37 | 为新增的核心数据处理函数补一条 CTest 测试 | `ctest` 显示新增测试并通过 | 只测正常输入，不测空文件、非法内容或边界值 |
