# C 语言程序设计基础 · 课程实践资料

**简体中文** | [English](README.en.md)

面向大一上学期初学者的 C 语言课程实践教程。每周一个主题，围绕一件真实会用到的开发工具展开：从在 VS Code 里跑通第一个程序，到用 Git 管理版本、用 raylib 完成期末图形项目。每篇正文都按「课前准备 → 操作步骤 → 常见问题 → 课后作业 → 自检清单」组织，并配有截图和一份可逐条打勾的 `checklist.md`。

> 仓库随课程进度更新，目前包含第 1–5 周与期末项目六份材料。

## 目的

初学编程时，真正卡住人的往往不是语法，而是环境：`gcc 不是内部或外部命令`、路径里带了中文、CMake 找不到编译器……本仓库把这门课要用的工具链拆成六周，每周解决一类问题：

- 把 **编辑 → 编译 → 运行 → 调试** 这条链路彻底打通；
- 学会用 **AI 编程助手** 辅助学习和排查问题；
- 用 **CMake** 管理多文件工程，用 **Git** 管理代码版本；
- 认识另一款适合初学者的 IDE，并完成一个可运行的 **raylib 图形项目**。

每周内容独立成篇，可单独查阅；按顺序学习则前后衔接——后一周默认你已经完成前一周的环境配置。

## 课程内容一览

| 周次 | 主题 | 你将完成 |
| --- | --- | --- |
| 第 1 周 | [基本工具安装](week1/基本工具安装.md) | 安装 VS Code 与 MinGW-w64 GCC，配置 PATH、扩展和调试，跑通第一个 C 程序 |
| 第 2 周 | [Claude Code 安装与配置](week2/ClaudeCode安装与配置.md) | 安装 Claude Code 插件与 CC Switch，接入 ModelScope 令牌，在 VS Code 里用上 AI 助手 |
| 第 3 周 | [CMake 安装与使用](week3/CMake安装与使用.md) | 写 `CMakeLists.txt`，用外部构建编译单文件、多文件与分目录工程，选做生成静态库 |
| 第 4 周 | [Git 安装与使用](week4/Git安装与使用.md) | 完成安装配置、提交、回退、忽略文件，把代码推送到 Gitee，选做 GitHub 与分支 |
| 第 5 周 | [RedPandaIDE 安装与使用](week5/RedPandaIDE安装与使用.md) | 配置小熊猫 C++ 的 GCC，用快捷键编译、运行、调试，并运行试题集 |
| 期末 | [raylib 图形库与项目实操](weekFinal/raylib图形库与项目实操.md) | 在课程工程模板上完成配置、编译、测试与运行，着手期末图形大作业 |

## 快速开始

```powershell
git clone https://github.com/Santoinspace/c_language_course.git
```

1. 打开 `week1/基本工具安装.md`，从「课前准备」开始按步骤操作；
2. 每做完一步，对照 `week1/checklist.md` 的「结果」自检，不符时看「避免」；
3. 按 第 1 周 → 第 5 周 → 期末 的顺序推进。

> 文档中的命令默认在 **PowerShell / CMD / VS Code 内置终端** 中执行，安装与工程路径一律使用纯英文、无空格的目录（如 `D:\Code`）。个别步骤必须用 Git Bash 时会在正文中单独说明。

## 目录结构说明

```text
c_language_course/
├─ week1/                      # 第 1 周：基本工具安装
│  ├─ 基本工具安装.md           # 本周正文
│  ├─ checklist.md             # 配套操作清单
│  └─ images/                  # 正文截图（01、02… 编号）
├─ week2/                      # 第 2 周：Claude Code 安装与配置
├─ week3/                      # 第 3 周：CMake 安装与使用
├─ week4/                      # 第 4 周：Git 安装与使用
├─ week5/                      # 第 5 周：RedPandaIDE 安装与使用
├─ weekFinal/                  # 期末：raylib 图形库与项目实操
├─ README.md                   # 中文说明（本文件）
└─ README.en.md                # English README
```

约定：

- 每周一个 `weekN/` 目录，只有一份以中文主题命名的正文，外加一份 `checklist.md`；
- 截图统一放在当周 `images/`，正文用相对路径引用，克隆后离线也能查看；
- 正文固定包含：本节目标、课前准备、操作步骤、常见问题（FAQ）、课后作业、自检清单、图片来源；
- 期末大作业使用的工程模板（raylib 6.0 + CMake）由课程另行下发，不在本仓库中。

## 环境与阅读建议

| 项目 | 要求 |
| --- | --- |
| 操作系统 | Windows 11（课程实际环境；Windows 10 部分菜单与截图会有差异） |
| 磁盘路径 | 安装、解压、建工程均使用纯英文、无空格的路径 |
| 解压工具 | 7-Zip 或 Bandizip（Windows 11 23H2 起系统自带 7z 支持） |
| 网络 | 首次配置 raylib 等步骤需要联网 |

阅读建议：先看「本节目标」确认学完能做到什么；「常见问题」可当作排错手册单独查阅；每篇末尾的「自检清单」用于自测验收。

## 版权与图片来源

- 课程原创的正文、清单与助教实拍截图，版权归本课程所有，供教学使用。
- 部分截图与操作思路整理自公开教程（CSDN、GitHub、GitHub Docs、廖雪峰教程、raylib 官网等），每篇开头的「参考文献」与文末的「图片来源」均已注明出处，版权归原作者所有。
- 文中涉及的 VS Code、MinGW-w64、Claude Code、CC Switch、ModelScope、CMake、Git、RedPandaIDE、raylib 等均为各自项目或公司的产品，本仓库与它们没有隶属关系。

## 反馈

发现步骤与你的环境不符、图片缺失或命令有误，欢迎提交 [Issue](https://github.com/Santoinspace/c_language_course/issues) 指正，或直接在对应周的文档上提出修改建议。
