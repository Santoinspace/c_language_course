# C 语言程序设计基础 · 期末大作业统一工程模板

**平台：Windows 11 | GCC (MinGW-w64) | CMake | mingw32-make | VS Code | Git | raylib 6.0**

这是面向大一上学期的 **C99 图形程序工程模板**。打开程序后会出现一个可用方向键或 WASD 移动的蓝色方块；收集黄色方块得分，最高分保存到 `data/best_score.txt`。示例同时展示 **结构体、函数、指针、多文件编译、文件读写和图形交互**。

> 学生必读：[`docs/STUDENT_GUIDE.md`](docs/STUDENT_GUIDE.md)。操作核对用 [`docs/checklist.md`](docs/checklist.md)，常见问题见 [`docs/QA.md`](docs/QA.md)。

## 快速开始（在 Windows 11 的 PowerShell、CMD 或 VS Code 终端中）

**前提**：已正确安装 `gcc`、`mingw32-make`、`cmake`、`git`，均可在终端直接调用。`MinGW Makefiles` 会通过 `cmd.exe` 执行构建规则，请勿在 MSYS/Git Bash 里运行这些命令。

```powershell
# 建议先检查环境（在仓库根目录）
cmd /c tools\check-env.cmd

# 仅需首次配置；第一次会从 GitHub 下载 raylib 6.0
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug

# 编译（此命令内部调用 mingw32-make）
cmake --build build --parallel 4

# 单元测试（不打开图形窗口）
ctest --test-dir build --output-on-failure

# 运行：注意先处于仓库根目录，保证 data/ 相对路径正确
.\build\c_final_project.exe
```

也可以直接运行 `tools` 目录下的辅助脚本。这些脚本会自行切换到项目根目录，因此从任意当前目录调用都可以：

```powershell
cmd /c tools\configure.cmd
cmd /c tools\build.cmd
cmd /c tools\run.cmd
```

如希望直接调用 make：

```powershell
cd build
mingw32-make -j4
cd ..
```

## 学生真正要改哪些内容？

- **在工程中搜索 `TODO(STUDENT)`，即可定位需要你修改或新增代码的位置。**
- 编辑 `src/main.c`，完成你的游戏/应用；`src/score.c` 与 `include/score.h` 是模块化示例。
- 自己新增 `.c`、`.h` 文件，并把新 `.c` 文件写进 `CMakeLists.txt` 的 `add_executable` 列表。
- 每完成一个阶段，使用 `git add`、`git commit`、`git push` 管理提交历史。
- 使用 `ctest` 运行测试，并自行补充针对核心数据处理函数的测试。
- 在本 README 中写明：项目名称、功能、操作方法、模块分工、本人完成内容与已知不足。

## 项目结构

```text
raylib_project_template/
├─ CMakeLists.txt             # C99、raylib 6.0、源文件、测试的编译配置
├─ .gitignore                 # 忽略 build、生成文件和个人数据
├─ .vscode/                  # VS Code 任务、代码补全与可选 GDB 调试
├─ src/main.c                # 图形示例入口
├─ src/score.c               # 文件读写示例
├─ include/score.h           # 多文件头文件示例
├─ tests/test_score.c        # 不依赖 raylib 的 C 单元测试
├─ assets/                   # 图片和音效（本示例不用）
├─ data/                     # 运行时保存的分数等数据
├─ docs/STUDENT_GUIDE.md     # 学生从安装到首次提交教程
├─ docs/checklist.md         # 从环境检查到提交前的操作清单
├─ docs/ASSIGNMENT.md        # 期末大作业要求与题目
├─ docs/QA.md                # 常见错误、故障排查与 raylib 离线方案
├─ third_party/              # 可选离线依赖
└─ tools/                    # 课程辅助脚本（可在任意目录调用）
   ├─ check-env.cmd          # 检查 gcc、mingw32-make、cmake、git
   ├─ configure.cmd          # 首次配置，生成 build/
   ├─ build.cmd              # 编译
   └─ run.cmd                # 从项目根目录运行程序
```

## 依赖规则

正常联网时使用 CMake `FetchContent` 将 **Git 标签 6.0** 的 raylib 取到 `build/_deps/`。如果校园网无法访问 GitHub，助教可以把完整的、官方 **raylib 6.0 源代码**放到 `third_party/raylib/`，配置时会自动走离线路径。两种模式二选一，**不需要另外安装 raylib DLL**。

课程统一 `MinGW Makefiles`，不要将同一个 `build/` 混用 Visual Studio、Ninja、MSYS 等其他生成器。需要更换生成器或编译器时，请先删除 `build/` 再配置。

## 许可证和说明

该课程原创示例及文档采用 MIT 许可证（见 `LICENSE`）。raylib 是第三方开源项目，仍适用其自身的 zlib/libpng 许可证；如离线分发源码，应保留 raylib 原有 LICENSE。官方项目：https://github.com/raysan5/raylib 。本教学模板非 raylib 官方出品。
