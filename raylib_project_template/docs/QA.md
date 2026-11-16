# 常见错误与排查

| 现象                                          | 原因                                                | 处理                                                           |
| --------------------------------------------- | --------------------------------------------------- | -------------------------------------------------------------- |
| `gcc` 不是内部或外部命令                    | MinGW `bin` 不在 PATH                             | 配置 PATH，重启终端，执行 `where.exe gcc`                    |
| `mingw32-make` 找不到                       | 工具链不完整，或 PATH 错误                          | 确认 `mingw32-make.exe` 存在并与 `gcc.exe` 同一路径        |
| `git` 不是命令                              | Git for Windows 未安装或 PATH 未生效                | 安装 Git、重新打开终端                                         |
| CMake `Could not create named generator`    | 生成器名字错误                                      | 正确使用 `-G "MinGW Makefiles"`                              |
| `generator does not match previously used`  | build 里缓存了其他生成器                            | 删除整个 `build/` 再配置                                     |
| `CMAKE_C_COMPILER not set`                  | GCC 没在 PATH 或命中了错误工具链                    | 检查 `where.exe gcc` 并重新配置                              |
| raylib `git clone`/TLS/网络错误             | 无法从 GitHub 拉依赖                                | 采用本文下方的离线方案；不要在网络不通时反复配置              |
| 找不到 `raylib.h`                           | 依赖未成功配置，或没有使用本工程 CMake              | 先确认 `cmake -S ...` 成功，再用 `cmake --build build`     |
| `undefined reference to PrintCourseMessage` | 新增 `.c` 未进入 `add_executable`，或签名不匹配 | 检查 CMake 文件列表、头文件声明和函数实现                      |
| `gdb.exe` not found                         | 未装 GDB                                            | 终端运行程序不受影响；需要 F5 时配置 GDB                       |
| 无法保存分数                                  | 未从项目根目录运行，或目录不存在                    | 从根目录运行 `.\\build\\c_final_project.exe`，检查 `data/` |
| `git push` 权限或登录失败                   | 凭据未配置、仓库 URL 不是自己的                     | 查看 `git remote -v`；通过凭据管理器/SSH 正常登录            |
| `fatal: not a git repository`               | 当前目录不是仓库                                    | `cd` 进入真正含 `.git` 的仓库根目录                        |
| Git 里出现一堆 build 文件                     | 忽略规则加入前已追踪                                | 先确认 `.gitignore`，再谨慎运行 `git rm -r --cached build` |
| VS Code 代码提示红线但编译成功                | IntelliSense 没读取编译参数                         | 确保已运行 CMake 配置、安装 C/C++ 扩展                         |

**排障顺序**：确认工作目录 → 确认 `where.exe` 路径 → 复制第一条真正的编译错误 → 检查 CMake 生成器与源文件列表 → 排查网络。向助教求助时，请粘贴具体报错、`gcc --version`、`cmake --version`、`git status`，不要只发“编译不了”。

# 无法访问 GitHub 时：raylib 6.0 离线源代码方案

本模板使用**两种模式自动切换**，不需要手工编辑 CMakeLists.txt。

**默认联网模式：** 若 `third_party/raylib/CMakeLists.txt` 不存在，CMake `FetchContent` 会通过 Git 获取 `raylib` 固定标签 `6.0`，下载到 `build/_deps/`，第一次需要联网。

**离线模式：** 助教在网络可用的计算机上，从官方 https://github.com/raysan5/raylib/releases/tag/6.0 获取**完整源代码压缩包**并解压。将包含 `CMakeLists.txt`、`src/`、`cmake/` 等内容的 raylib 原始目录命名为 `raylib`，放到 `third_party/` 下：

```text
raylib_project_template/
  third_party/
    raylib/
      CMakeLists.txt
      src/
      cmake/
      ...
```

**必须是 raylib 的 CMakeLists.txt 直接位于 `third_party/raylib/` 中**，不要多一层 `raylib-6.0/`。保留第三方许可证文件 `LICENSE`，原样转交学生。

然后在项目根目录执行：

```powershell
# 若曾配置失败，可先移除旧 build 后重配
Remove-Item -Recurse -Force .\build
cmake -S . -B build -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel 4
```

注意：`Remove-Item` 只在 `build/` 已存在时使用；不存在时跳过。离线源码目录已在 `.gitignore` 中排除，**不会随学生 Git 提交自动上传**。
