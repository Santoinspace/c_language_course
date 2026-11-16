# 学生操作手册：从工具检查到第一次 Git 提交

> 适用班级：大一上学期《C 语言程序设计基础》。课程环境：**Windows 11 + MinGW-w64 (GCC 16.2.0) + CMake 4.4.4 + VS Code + mingw32-make + Git**。raylib 固定为 **6.0**。本手册以 Windows **PowerShell / CMD / VS Code 内置 PowerShell 终端**为例。不要使用 Git Bash/MSYS 运行 `MinGW Makefiles`。
>
> 操作核对：[docs/checklist.md](checklist.md)；常见问题：[docs/QA.md](QA.md)。

## 01. 你将完成什么

本次实践完成后，你应该会：识别编译器/构建器/编辑器的不同职责；用 Git 克隆仓库；用 CMake 生成 Makefile；用 `mingw32-make` 构建多文件 C 项目；运行 raylib 程序；新增 `.c` 与 `.h` 文件；使用 Git 至少提交两次并推送远程仓库。

**概念对照：** GCC 把 C 源码编译成程序；CMake 根据 `CMakeLists.txt` 生成构建规则；`mingw32-make` 按规则执行编译；raylib 负责窗口、图形与输入；Git 负责版本历史；VS Code 是代码编辑器。

## 02. 安装或核对课程工具链

**如果已经安装了课程规定的 GCC 16.2.0、CMake 4.4.4 和 VS Code，就不要重复安装或覆盖原来的工具链**，直接执行本节后半部分的命令检查。如果是新电脑或工具缺失，推荐按以下顺序安装：

1. **MinGW-w64（GCC 和 mingw32-make）**：优先使用助教发放的、与教学机完全一致的压缩包。自行下载安装可参考 <https://winlibs.com/>，选 Windows 64 位（`x86_64`）、POSIX 线程、SEH 异常处理、GCC 16.2.0 的完整 MinGW-w64 包。WinLibs 同时有 **UCRT** 和 **MSVCRT** 运行库版本，按助教指定的一种统一选择，不要只看 GCC 大版本。解压后确保能在同一个 `bin` 目录下找到 `gcc.exe`、`mingw32-make.exe`；例如解压后路径可能为 `C:\DevTools\mingw64\bin`，**以电脑上的实际路径为准**。
2. **配置 Windows PATH**：在开始菜单搜索“编辑系统环境变量”→“环境变量”→选择用户 `Path` →“编辑”→“新建”，填写上一步的 **`bin` 目录**（例如 `C:\DevTools\mingw64\bin`）。不要填成 `mingw64` 根目录，也不要同时加入两套不同 MinGW 的 `bin`。保存后**彻底关闭并重新打开 VS Code/终端**。
3. **CMake**：从官方网站 <https://cmake.org/download/> 下载 Windows x64 安装包，按课程要求选 **4.4.4**。安装时勾选将 CMake 添加到 PATH 的选项（如安装程序提供此选项）。CMake 自带的其他生成器不用选；课程指定的是 `MinGW Makefiles`。
4. **Git for Windows**：从 <https://git-scm.com/downloads/win> 下载安装。一般采用安装程序默认设置即可；装完重启终端，确认 `git` 能运行。Git Bash 虽然可随 Git 安装，但本课程用 **VS Code 的 PowerShell 或 CMD 终端**构建。
5. **VS Code**：从 <https://code.visualstudio.com/> 安装，随后在扩展市场安装 **C/C++ (Microsoft)**。如需断点调试，确认你使用的 MinGW 工具链还包含 `gdb.exe`。

打开 VS Code → `终端` → `新建终端`（PowerShell 或 CMD），依次运行：

```powershell
gcc --version
mingw32-make --version
cmake --version
git --version
```

上述命令都需要输出版本信息。课程预期 GCC 16.2.0、CMake 4.4.4；小版本差异请按教师要求处理。`git` 是必须安装的工具，如果尚未安装，可访问 https://git-scm.com/downloads/win ，安装后关闭并重新打开终端。VS Code 可从 https://code.visualstudio.com/ 下载；GCC/CMake 由课堂统一发放或配置，不要同时安装多套 MinGW 以免 PATH 混乱。

确认每个可执行文件的路径（尤其防止调用到另一套 GCC）：

```powershell
where.exe gcc
where.exe mingw32-make
where.exe cmake
where.exe git
```

理想情况下，`gcc.exe` 与 `mingw32-make.exe` 位于同一 MinGW 工具链的 `bin` 目录中。**不要把 CMake 的版本号与 GCC 的版本号混淆。**

如已取得模板，在项目根目录还可以运行：

```powershell
cmd /c tools\check-env.cmd
```

推荐安装 VS Code 扩展 **C/C++ (Microsoft)**。如需用 F5 断点调试，另需 `gdb.exe` 并确保 `gdb --version` 能执行；未安装 GDB 不影响编译、测试与运行。`CMake Tools` 扩展可选，前两周请优先练习终端命令。

## 03. 第一次设置 Git 身份

在终端中设置个人显示名称及邮箱（替换为自己的信息）：

```powershell
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
git config --global --list
```

名称和邮箱将记录在未来的 commit 元信息中；**不要在仓库中提交密码、Token 或其他秘密**。GitHub 使用网页授权、凭据管理器或 SSH 进行远程身份验证，不需要把账号密码写进源文件。

## 04. 在 GitHub 创建个人作业仓库并克隆

1. 教师会发布模板仓库地址。打开 GitHub 模板仓库，单击 **Use this template → Create a new repository**（若老师采用其他分发方式，请以老师公布的指令为准）。
2. 给个人仓库命名，例如 `c-final-2026-student-id`；按教师要求设置仓库可见性。请勿在公开仓库中写真实身份证号、手机号。
3. 复制自己的仓库 HTTPS 地址（下方的 URL 仅为占位示例，不可照抄）。
4. 在准备存放项目的目录中运行：

```powershell
git clone https://github.com/YOUR_ACCOUNT/YOUR_REPO.git
cd YOUR_REPO
code .
```

`code .` 如果提示找不到命令，也可以通过 VS Code 的“文件 → 打开文件夹”打开仓库。**务必确认打开的是含 `CMakeLists.txt` 的根目录**。

```powershell
git status
git remote -v
```

`git status` 应显示你位于自己的 Git 仓库，`git remote -v` 应指向自己的远程仓库，不是教师的原始模板仓库。

## 05. 首次生成 Makefile（只需配置一次，改动 CMakeLists 后会自动重新配置）

在仓库根目录运行：

```powershell
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug
```

解释：`-S .` 是源代码根目录；`-B build` 表示把生成文件放进 `build/`；`-G "MinGW Makefiles"` 指定供 `mingw32-make` 使用的生成器；`-DCMAKE_C_COMPILER=gcc` 指定 GCC 编译器；`Debug` 用来保留调试信息。**首次联网配置会从 GitHub 下载 raylib 6.0**，速度取决于网络。

配置成功后，项目根目录出现 `build/`，你会看到 CMake 生成的文件。不要手动修改 `build/` 内的 Makefile；正确做法是编辑根目录的 `CMakeLists.txt`。

如教师分发了离线 raylib 源码，按 [`docs/QA.md`](QA.md) 中的离线方案放到指定位置后，使用相同命令配置，无需联网。

## 06. 编译、测试和运行

```powershell
# 根目录执行；CMake 会调用 mingw32-make
cmake --build build --parallel 4

# 也可以直接进入 build/ 调用 mingw32-make
cd build
mingw32-make -j4
cd ..

# 执行不需要图形界面的 C 语言测试
ctest --test-dir build --output-on-failure

# 在项目根目录启动程序
.\build\c_final_project.exe
```

窗口打开后，按**方向键或 WASD**移动蓝色方块，碰到黄色方块会加 1 分；按 `R` 重新开始，按 `Esc` 退出。最高分保存在 `data/best_score.txt`。如果文件还不存在是正常的，第一次获得新最高分后才会出现。**请从仓库根目录启动程序**，以便相对路径 `data/` 能正常使用。

也可以双击或执行 `tools\configure.cmd`、`tools\build.cmd`、`tools\run.cmd`（建议初学阶段先练命令；脚本会自动切换到项目根目录），或者在 VS Code 中 `终端 → 运行任务`，依次选择 `01 Configure`、`02 Build`、`03 Test`、`04 Run demo`。其中 **Ctrl+Shift+B** 默认执行构建（需先配置）。

## 07. 第一次修改源码：亲自新增一个模块

这一步是课堂检查项。不要只修改 `main.c`，你需要亲自给工程新增一个 `.c` 文件和 `.h` 文件。

创建 `include/message.h`：

```c
#ifndef COURSE_MESSAGE_H
#define COURSE_MESSAGE_H

void PrintCourseMessage(void);

#endif
```

创建 `src/message.c`：

```c
#include "message.h"
#include <stdio.h>

void PrintCourseMessage(void)
{
    puts("This is my first multi-file C project!");
}
```

修改 `src/main.c`：在文件开头增加 `#include "message.h"`；在 `int main(void)` 的函数体开始位置添加 `PrintCourseMessage();`。最后打开项目根目录的 `CMakeLists.txt`，在 `add_executable(c_final_project ...)` 中增加 **`src/message.c`**：

```cmake
add_executable(c_final_project
    src/main.c
    src/score.c
    src/message.c
)
```

现在重新编译：

```powershell
cmake --build build --parallel 4
.\build\c_final_project.exe
```

如果漏写 `src/message.c`，常见结果是链接错误 `undefined reference to PrintCourseMessage`。请先检查 `#include`、函数声明、源文件是否参与 CMake 编译，不要简单复制网络上的修复命令。

## 08. 使用 Git 完成第一次提交、第二次提交并推送

项目根目录执行：

```powershell
git status
git add CMakeLists.txt src/main.c src/message.c include/message.h
git commit -m "Add a custom C module and update CMake"
git log --oneline -5
git push -u origin main
```

> 如果教师使用的仓库默认分支不是 `main`，可用 `git branch --show-current` 查看，再将 `main` 替换为实际分支名。

继续做一次可见的小改动（例如修改窗口标题，或增加一条屏幕提示），再执行：

```powershell
git add src/main.c
git commit -m "Improve starter demo text"
git push
```

最后打开个人 GitHub 仓库网页，确认存在**至少两个自己完成的 commit**，并且 `src/message.c`、`include/message.h` 和 `CMakeLists.txt` 的改动都已推送。运行 `git status` 确认工作区干净。无需提交 `build/`、`.exe` 或 `data/best_score.txt`，模板已通过 `.gitignore` 排除。

如果老师要求保留开发阶段的提交记录，请不要频繁使用 `git push --force`、`git reset --hard` 等可能破坏历史的操作。

## 09. 第一阶段自检清单

- [ ] `gcc`、`mingw32-make`、`cmake`、`git` 能在 VS Code 终端执行。
- [ ] 能解释 GCC、CMake、mingw32-make、Git、VS Code 各自的作用。
- [ ] 使用自己的远程仓库（不是教师仓库）并成功克隆。
- [ ] 可以运行 `cmake -S . -B build -G "MinGW Makefiles"`。
- [ ] `cmake --build build` 成功，窗口可移动方块并计分。
- [ ] `ctest --test-dir build --output-on-failure` 测试通过。
- [ ] 新增 `message.c` 与 `message.h`，并更新 `CMakeLists.txt`。
- [ ] `git log --oneline` 中至少有两个本人完成的提交。
- [ ] GitHub 远程仓库已显示最新代码，`build/` 未被提交。

## 10. 进入正式大作业

完成第一阶段自检后，阅读 [`docs/ASSIGNMENT.md`](ASSIGNMENT.md)，选题并提交需求与模块分解。管理类项目推荐使用 **raylib 基础绘图**绘制简单列表/按钮，数据逻辑必须由标准 C 语言结构体及文件操作完成；本次教学仓库**不预装 raygui**，以减少学习负担。若项目确有输入框、表格等复杂 GUI 需求，须先与助教沟通是否统一增加 `raygui`，避免不同小组随意使用其他图形框架。

常见问题见 [`docs/QA.md`](QA.md)。

## 附录：首次实践记录（可打印填写）

| 检查项目 | 学生填写 / 助教确认 |
| --- | --- |
| 作业仓库 URL | ______________________________ |
| 首次个人提交简短哈希 | ______________________________ |
| 第二次个人提交简短哈希 | ______________________________ |
| CMake 构建和 CTest | □ 均成功  □ 需要复查 |
| 独立模块和 CMakeLists | □ 已检查  □ 需要复查 |
| 完成日期 | ____________ |

建议把这个表作为课堂检查的辅助记录，不替代仓库中的真实 Git 历史。
